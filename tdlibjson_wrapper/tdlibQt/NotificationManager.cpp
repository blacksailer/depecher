#include "NotificationManager.hpp"
#include <QDebug>
#include <QGuiApplication>
#include "../tdlibjson_wrapper/tdlibQt/TdlibJsonWrapper.hpp"
#include "../tdlibjson_wrapper/tdlibQt/models/singletons/UsersModel.hpp"
#include "../tdlibjson_wrapper/tdlibQt/ParseObject.hpp"
#include <QJsonObject>
namespace tdlibQt {

constexpr int cWaitTimerSeconds = 1000;

NotificationManager::NotificationManager(QObject *parent) : QObject(parent),
    m_client(TdlibJsonWrapper::instance())
{

    m_PublishTimer.setInterval(cWaitTimerSeconds);
    m_PublishTimer.setSingleShot(true);
    connect(&m_PublishTimer, &QTimer::timeout, this, &NotificationManager::publishNotifications);
    //План Б. Получать список уведомлений по updateChatReadInbox и notifications
    connect(m_client, &TdlibJsonWrapper::connectionStateChanged,
    [this](Enums::ConnectionState connectionState) {
        if (m_connectionState == connectionState)
            return;
        m_connectionState = connectionState;
        if (isAtFirstLoaded) {
            publishNotifications();
            isAtFirstLoaded = false;
        }
    });
    connect(m_client, &TdlibJsonWrapper::newMessageFromUpdate,
            this, &NotificationManager::gotNewMessage);
    //Not working. Before get Ready, do not emit updateChatReadInbox.
    connect(m_client, &TdlibJsonWrapper::updateChatReadInbox,
    [this](const QJsonObject & object) {
        qint64 chat_id = ParseObject::getInt64(object["chat_id"]);
        int unread_count = object["unread_count"].toInt();
        //        qint64 last_message_id = ParseObject::getInt64(object["last_read_inbox_message_id"]);

        // Notify on first start app
        if (m_connectionState != Enums::ConnectionState::ConnectionStateReady) {
            if (UsersModel::instance()->getChatMuteFor(chat_id) <= 0 && unread_count > 0) {
                if (m_chatIdsPublished.contains(chat_id))
                    m_chatIdsPublished[chat_id]->setItemCount(unread_count);
                else {
                    notifySummary(QDateTime::currentMSecsSinceEpoch(), UsersModel::instance()->getChatTitle(chat_id),
                                  QString::number(unread_count) + " " + tr("new messages"), chat_id,
                                  unread_count);
                }
            } else {
                removeNotification(chat_id);
            }
        } else {
            // Workaround for chatting via different computer
            if (UsersModel::instance()->getChatMuteFor(chat_id) <= 0 && unread_count == 0) {
                removeNotification(chat_id);
                if (m_chatIdsToPublish.contains(chat_id)) {
                    m_chatIdsToPublish[chat_id]->close();
                    m_chatIdsToPublish.remove(chat_id);
                }
            }
        }
    });

    connect(m_client, &TdlibJsonWrapper::updateChatReadOutbox,
            this, &NotificationManager::getUpdateChatOutbox);
}

void NotificationManager::publishNotifications()
{
    if (m_connectionState == Enums::ConnectionState::ConnectionStateReady) {
        for (auto itr = m_chatIdsToPublish.begin(); itr != m_chatIdsToPublish.end(); ++itr) {
            m_chatIdsPublished[itr.key()] = itr.value();
            itr.value()->publish();
        }
        m_chatIdsToPublish.clear();
    }
}

NotificationManager *NotificationManager::instance()
{
    static NotificationManager  instance;
    return &instance;

}

void NotificationManager::removeNotification(qint64 chatId)
{
    if (m_chatIdsPublished.contains(chatId)) {
        m_chatIdsPublished[chatId]->close();
        m_chatIdsPublished.remove(chatId);
    }
}

void NotificationManager::getUpdateChatOutbox(const QJsonObject &chatReadOutbox)
{
    qint64 chat_id = ParseObject::getInt64(chatReadOutbox["chat_id"]);
    //qint64 last_message_id = ParseObject::getInt64(chatReadOutbox["last_read_outbox_message_id"]);
    removeNotification(chat_id);
}

void NotificationManager::gotNewMessage(const QJsonObject &updateNewMessage)
{
    bool disableNotification  = updateNewMessage["disable_notification"].toBool();
    qDebug() << disableNotification;
    if (!disableNotification) {
        auto messageObject = updateNewMessage["message"].toObject();
        qDebug() << "Publishing...";
        auto notificationTimestamp = qint64(messageObject["date"].toInt());
        QString notificationSummary;
        QString notificationBody;
        qint64 chatId = ParseObject::getInt64(messageObject["chat_id"]);
        auto chatIt = m_client->parseObject->chat_title_.find(chatId);
        if (chatIt == m_client->parseObject->chat_title_.end())
            notificationSummary = tr("unknown chat");
        else
            notificationSummary = chatIt->second;

        auto userIt = m_client->parseObject->users_.find(messageObject["sender_user_id"].toInt());

        if (userIt == m_client->parseObject->users_.end())
            notificationBody = tr("unknown user") + ":";
        else
            notificationBody = userIt.value() + ":";


        if (messageObject["content"].toObject()["@type"] == "messageText")
            notificationBody.append(" " +
                                    messageObject["content"].toObject()["text"].toObject()["text"].toString());

        if (qApp->applicationState() != Qt::ApplicationActive)
            notifySummary(notificationTimestamp, notificationSummary,
                          notificationBody,
                          chatId, 1);
        else
            notifyPreview(notificationTimestamp, notificationSummary,
                          notificationBody,
                          chatId, 1);
    }

}

void NotificationManager::onViewMessages(const qint64 peerId)
{
    removeNotification(peerId);
}

void NotificationManager::notifySummary(const qint64 timestamp, const QString &summary,
                                        const QString &body, const qint64 chatId,  const qint64 unreadCount)
{
    QSharedPointer<Notification> notificationPtr = QSharedPointer<Notification>(new Notification);
    notificationPtr->setAppName("Depecher");
    notificationPtr->setCategory("x-depecher.im");
    notificationPtr->setExpireTimeout(m_expireTimeout);
    notificationPtr->setItemCount(unreadCount);
    if (m_chatIdsPublished.contains(chatId)) {
        notificationPtr->setItemCount(m_chatIdsPublished[chatId]->itemCount() + 1);
        notificationPtr->setReplacesId(m_chatIdsPublished[chatId]->replacesId());
    }
    notificationPtr->setTimestamp(QDateTime::fromMSecsSinceEpoch(timestamp *
                                  1000 /* timestamp have secs , not msecs*/));
    notificationPtr->setSummary(summary);
    notificationPtr->setBody(body);

    QVariantList arguments;
    arguments.append(chatId);
    QVariantList actions;
    actions.append(Notification::remoteAction("default", "openConversation", "org.blacksailer.depecher", "/org/blacksailer/depecher", "org.blacksailer.depecher", "openConversation", arguments));
    notificationPtr->setRemoteActions(actions);

    connect(notificationPtr.data(), &Notification::closed, [this]() {
        auto ptr = QSharedPointer<Notification>((Notification *)sender());
        m_chatIdsPublished.remove(m_chatIdsPublished.key(ptr)) ;
    });
    m_chatIdsToPublish[chatId] = notificationPtr;

    if (!m_PublishTimer.isActive())
        m_PublishTimer.start();

//    if (isAtFirstLoaded)
//        publishNotifications();
//    else
//        notificationPtr->publish();
}

void NotificationManager::notifyPreview(const qint64 timestamp, const QString &summary,
                                        const QString &body, const qint64 chatId, const qint64 unreadCount)
{

    QSharedPointer<Notification> notificationPtr = QSharedPointer<Notification>(new Notification);
    notificationPtr->setAppName("Depecher");
    notificationPtr->setCategory("x-depecher.im.fg");
    notificationPtr->setExpireTimeout(m_expireTimeout);
    notificationPtr->setItemCount(unreadCount);
    if (m_chatIdsPublished.contains(chatId)) {
        notificationPtr->setItemCount(m_chatIdsPublished[chatId]->itemCount() + 1);
        notificationPtr->setReplacesId(m_chatIdsPublished[chatId]->replacesId());
    }
    notificationPtr->setTimestamp(QDateTime::fromMSecsSinceEpoch(timestamp *
                                  1000 /* timestamp have secs , not msecs*/));
    notificationPtr->setPreviewBody(body);
//https://git.merproject.org/mer-core/lipstick/blob/master/doc/src/notifications.dox#L41
    //    notificationPtr->setPreviewSummary(summary);
    //    QVariantList arguments;
//    arguments.append(chatId);
//    QVariantList actions;
//    actions.append(Notification::remoteAction("default", "openConversation", "org.blacksailer.depecher", "/org/blacksailer/depecher", "org.blacksailer.depecher", "openConversation", arguments));
//    notificationPtr->setRemoteActions(actions);

    connect(notificationPtr.data(), &Notification::closed, [this]() {
        auto ptr = QSharedPointer<Notification>((Notification *)sender());
        m_chatIdsPublished.remove(m_chatIdsPublished.key(ptr));
    });
    m_chatIdsToPublish[chatId] = notificationPtr;

    if (!m_PublishTimer.isActive())
        m_PublishTimer.start();

//    if (isAtFirstLoaded)
//        publishNotifications();
//    else
//        notificationPtr->publish();
}
}// tdlibQt
