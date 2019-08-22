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
    connect(m_client, &TdlibJsonWrapper::updateNotificationGroupReceived,
            this, &NotificationManager::gotNotificationGroup);
    connect(m_client, &TdlibJsonWrapper::updateActiveNotificationReceived,
            this, &NotificationManager::gotActiveNotification);

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

void NotificationManager::processNotificationGroup(QSharedPointer<notificationGroup> &group)
{
    foreach (auto notification, group->notifications_) {
        switch (notification->type_->get_id()) {
        case notificationTypeNewMessage::ID:
            QSharedPointer<message> messageItem = static_cast<notificationTypeNewMessage *>(notification->type_.data())->message_;
            auto notificationTimestamp = qint64(messageItem->date_);
            QString notificationSummary;
            QString notificationBody;
            qint64 chatId = messageItem->chat_id_;
            QString chatTitle = UsersModel::instance()->getChatTitle(chatId);
            notificationSummary = chatTitle;
            QString userName = UsersModel::instance()->getUserFullName(messageItem->sender_user_id_);
            notificationBody = userName + ":";

            if (messageItem->content_->get_id() == messageText::ID) {
                auto one = static_cast<messageText *>(messageItem->content_.data());
                auto two = static_cast<formattedText *>(one->text_.data());
                notificationBody.append(" " +
                                        QString::fromStdString(two->text_));
            } else
                notificationBody.append(" " +
                                        ParseObject::messageTypeToString(messageItem->content_->get_id()));

            if (qApp->applicationState() != Qt::ApplicationActive)
                notifySummary(notificationTimestamp, notificationSummary,
                              notificationBody,
                              chatId, 1);
            else
                notifyPreview(notificationTimestamp, notificationSummary,
                              notificationBody,
                              chatId, 1);
            break;
        }
    }

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

void NotificationManager::removeAll()
{
    foreach (auto key, m_chatIdsPublished.keys()) {
        m_chatIdsPublished[key]->close();
        m_chatIdsPublished.remove(key);
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
#warning parse notifiocation
    bool disableNotification  = true;//updateNewMessage["disable_notification"].toBool();
    if (!disableNotification) {
        auto messageObject = updateNewMessage["message"].toObject();
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

void NotificationManager::gotNotificationGroup(const QJsonObject &updateNotificationGroupObject)
{
    auto updateNotificationGroupObj = ParseObject::parseUpdateNotificationGroup(updateNotificationGroupObject);
    if (updateNotificationGroupObj->type_->get_id() == notificationGroupTypeMessages::ID ||
            updateNotificationGroupObj->type_->get_id() == notificationGroupTypeMentions::ID) {
        auto tmpNotifGroup = QSharedPointer<notificationGroup>(new notificationGroup);
        tmpNotifGroup->chat_id_ = updateNotificationGroupObj->chat_id_;
        tmpNotifGroup->id_  = updateNotificationGroupObj->notification_group_id_;
        tmpNotifGroup->notifications_  = updateNotificationGroupObj->added_notifications_;
        tmpNotifGroup->total_count_  = updateNotificationGroupObj->total_count_;
        tmpNotifGroup->type_ =  updateNotificationGroupObj->type_;
        processNotificationGroup(tmpNotifGroup);
    }
}

void NotificationManager::gotActiveNotification(const QJsonObject &updateActiveNotificationObject)
{
    std::vector<object_ptr<notificationGroup>> groups_;
    foreach (auto itm, updateActiveNotificationObject["groups"].toArray()) {
        auto notificationGroup = ParseObject::parseNotificationGroup(itm.toObject());
        if (notificationGroup->type_->get_id() == notificationGroupTypeMessages::ID ||
                notificationGroup->type_->get_id() == notificationGroupTypeMentions::ID)
            processNotificationGroup(notificationGroup);
        groups_.push_back(notificationGroup);
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
