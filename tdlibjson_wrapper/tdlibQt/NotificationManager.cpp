#include "NotificationManager.hpp"
#include <QDebug>
#include <QGuiApplication>
#include "TdlibJsonWrapper.hpp"
#include "models/singletons/UsersModel.hpp"
#include "ParseObject.hpp"
#include <QJsonObject>
namespace tdlibQt {

NotificationManager::NotificationManager(QObject *parent) : QObject(parent),
    m_client(TdlibJsonWrapper::instance())
{

    //План Б. Получать список уведомлений по updateChatReadInbox и notifications
    connect(m_client, &TdlibJsonWrapper::connectionStateChanged,
    [this](Enums::ConnectionState connectionState) {
        m_connectionState = connectionState;
        if (m_connectionState == Enums::ConnectionState::ConnectionStateReady)
            publishNotifications();
    });
    connect(m_client, &TdlibJsonWrapper::newMessageFromUpdate,
            this, &NotificationManager::gotNewMessage);
    //Not working. Before get Ready, do not emit updateChatReadInbox.
    connect(m_client, &TdlibJsonWrapper::updateChatReadInbox,
    [this](const QJsonObject & object) {
        qint64 chat_id = ParseObject::getInt64(object["chat_id"]);
        int unread_count = object["unread_count"].toInt();
        //        qint64 last_message_id = ParseObject::getInt64(object["last_read_inbox_message_id"]);
        if (m_connectionState != Enums::ConnectionState::ConnectionStateReady) {
            if (UsersModel::instance()->getChatMuteFor(chat_id) <= 0 && unread_count > 0) {
                if (m_chatIdsPublished.contains(chat_id))
                    m_chatIdsPublished[chat_id]->setItemCount(unread_count);
                else {
                    notifySummary(0, UsersModel::instance()->getChatTitle(chat_id),
                                  QString::number(unread_count) + " " + tr("new messages"), chat_id,
                                  unread_count);
                }
            } else {
                if (m_chatIdsPublished.contains(chat_id))
                    removeNotification(chat_id);
            }
        }
    });

    connect(m_client, &TdlibJsonWrapper::updateChatReadOutbox,
            this, &NotificationManager::getUpdateChatOutbox);
}

void NotificationManager::publishNotifications()
{
    if (m_connectionState == Enums::ConnectionState::ConnectionStateReady)
        for (auto itr = m_chatIdsPublished.begin(); itr != m_chatIdsPublished.end(); ++itr)
            itr.value()->publish();
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
    qint64 last_message_id = ParseObject::getInt64(chatReadOutbox["last_read_outbox_message_id"]);
    if (m_chatIdsPublished.contains(chat_id)) {
        qDebug() << m_chatIdsPublished[chat_id]->remoteActions() <<
                 m_chatIdsPublished[chat_id]->hintValue("message_id").toString() <<
                 m_chatIdsPublished[chat_id]->hintValue("message_id").toString().toLongLong()
                 << last_message_id;
        int i = 0;
        for (; i < m_chatIdsPublished[chat_id]->remoteActions().size(); i++) {
            QVariantMap item = m_chatIdsPublished[chat_id]->remoteActions().at(i).toMap();
            if (item["name"].toString() == "telegram_message_id")
                break;
        }

        if (m_chatIdsPublished[chat_id]->remoteActions().at(
                    i).toMap()["displayName"].toString().toLongLong() <
                last_message_id)
            removeNotification(chat_id);
    }
}

void NotificationManager::gotNewMessage(const QJsonObject &updateNewMessage)
{
    if (updateNewMessage["disable_notification"].toBool() != true
            && m_connectionState == Enums::ConnectionState::ConnectionStateReady) {
        auto messageObject = updateNewMessage["message"].toObject();

        auto notificationTimestamp = qint64(messageObject["date"].toInt());
        QString notificationSummary;
        QString notificationBody;
        qint64 chatId = ParseObject::getInt64(messageObject["chat_id"]);
        auto chatIt = m_client->parseObject->chat_title_.find(chatId);
        if (chatIt == m_client->parseObject->chat_title_.end())
            notificationSummary = "unknown chat";
        else
            notificationSummary = chatIt->second;

        auto userIt = m_client->parseObject->users_.find(messageObject["sender_user_id"].toInt());

        if (userIt == m_client->parseObject->users_.end())
            notificationBody = "unknown user:";
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

void NotificationManager::notifySummary(const qint64 timestamp, const QString &summary,
                                        const QString &body, const qint64 chatId,  const qint64 unreadCount)
{
    if (currentViewableChatId != chatId || qApp->applicationState() != Qt::ApplicationActive) {
        QSharedPointer<Notification> notificationPtr = QSharedPointer<Notification>(new Notification);

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

        //Too lazy to create another map. saving message id in hint value
        notificationPtr->setRemoteAction(Notification::remoteAction("telegram_message_id",
                                                                    QString::number(unreadCount), "org.freedesktop.Notifications", "/depecher", "Utility",
                                                                    "getId"));
        connect(notificationPtr.data(), &Notification::closed, [this]() {
            auto ptr = QSharedPointer<Notification>((Notification *)sender());
            m_chatIdsPublished.remove(m_chatIdsPublished.key(ptr)) ;
        });
        m_chatIdsPublished[chatId] = notificationPtr;
        publishNotifications();
    }
}

void NotificationManager::notifyPreview(const qint64 timestamp, const QString &summary,
                                        const QString &body, const qint64 chatId, const qint64 unreadCount)
{
    if (currentViewableChatId != chatId || qApp->applicationState() != Qt::ApplicationActive) {

        QSharedPointer<Notification> notificationPtr = QSharedPointer<Notification>(new Notification);
        notificationPtr->setCategory("x-depecher.im.fg");
        notificationPtr->setExpireTimeout(m_expireTimeout);
        notificationPtr->setItemCount(unreadCount);
        if (m_chatIdsPublished.contains(chatId)) {
            notificationPtr->setItemCount(m_chatIdsPublished[chatId]->itemCount() + 1);
            notificationPtr->setReplacesId(m_chatIdsPublished[chatId]->replacesId());
        }
        notificationPtr->setTimestamp(QDateTime::fromMSecsSinceEpoch(timestamp *
                                                                     1000 /* timestamp have secs , not msecs*/));
        notificationPtr->setPreviewSummary(summary);
        notificationPtr->setPreviewBody(body);
        //Too lazy to create another map. saving message id in hint value
        notificationPtr->setRemoteAction(Notification::remoteAction("telegram_message_id",
                                                                    QString::number(unreadCount), "org.freedesktop.Notifications", "/depecher", "Utility",
                                                                    "getId"));
        connect(notificationPtr.data(), &Notification::closed, [this]() {
            auto ptr = QSharedPointer<Notification>((Notification *)sender());
            m_chatIdsPublished.remove(m_chatIdsPublished.key(ptr));
        });
        m_chatIdsPublished[chatId] = notificationPtr;
        publishNotifications();
    }
}
}// tdlibQt
