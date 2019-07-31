#include "UsersModel.hpp"
#include <QDebug>
#include "tdlibQt/ParseObject.hpp"
#include "tdlibQt/TdlibJsonWrapper.hpp"
namespace tdlibQt {
UsersModel::UsersModel(QObject *parent) : QObject(parent),
    m_client(TdlibJsonWrapper::instance())
{
    connect(m_client, &TdlibJsonWrapper::updateNewUser,
            this, &UsersModel::getUpdateNewUser);
    connect(m_client, &TdlibJsonWrapper::updateNewChat,
            this, &UsersModel::getUpdateNewChat);
    connect(m_client, &TdlibJsonWrapper::updateSupergroup,
            this, &UsersModel::getUpdateNewSupergroup);
    connect(m_client, &tdlibQt::TdlibJsonWrapper::updateChatLastMessage,
            this, &tdlibQt::UsersModel::updateChatLastMessage);
    connect(m_client, &tdlibQt::TdlibJsonWrapper::updateChatReadInbox,
            this, &tdlibQt::UsersModel::updateChatReadInbox);
    connect(m_client, &tdlibQt::TdlibJsonWrapper::updateChatReadOutbox,
            this, &tdlibQt::UsersModel::updateChatReadOutbox);
    connect(m_client, &tdlibQt::TdlibJsonWrapper::updateUserStatusReceived,
            this, &tdlibQt::UsersModel::updateUserStatus);

}

UsersModel *UsersModel::instance()
{
    static UsersModel  instance;
    return &instance;

}

QString UsersModel::getChatTitle(const qint64 chatId)
{
    if (!m_chats.contains(chatId))
        return tr("Uknown chat");

    return QString::fromStdString(m_chats[chatId]->title_);
}

qint64 UsersModel::getLastMessageInbox(const qint64 chatId)
{
    if (!m_chats.contains(chatId))
        return 0;

    return m_chats[chatId]->last_read_inbox_message_id_;
}

qint64 UsersModel::getLastMessageOutbox(const qint64 chatId)
{
    if (!m_chats.contains(chatId))
        return 0;

    return m_chats[chatId]->last_read_outbox_message_id_;
}

qint64 UsersModel::getLastMessageId(const qint64 chatId)
{
    if (!m_chats.contains(chatId))
        return 0;

    return m_chats[chatId]->last_message_->id_;
}

QVariantMap UsersModel::getChatType(const qint64 chatId)
{
    if (!m_chats.contains(chatId))
        return QVariantMap();

    switch (m_chats[chatId]->type_->get_id()) {
    case chatTypeBasicGroup::ID: {
        QVariantMap resultType;
        resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::BasicGroup);
        return resultType;
    }
    case chatTypePrivate::ID: {
        QVariantMap resultType;
        resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Private);
        return resultType;
    }
    case chatTypeSecret::ID: {
        QVariantMap resultType;
        resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Secret);
        return resultType;
    }
    case chatTypeSupergroup::ID: {
        chatTypeSupergroup *superGroupMetaInfo   = static_cast<chatTypeSupergroup *>
                (m_chats[chatId]->type_.data());
        QVariantMap resultType;
        resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Supergroup);
        resultType["is_channel"] = superGroupMetaInfo->is_channel_;
        resultType["supergroup_id"] = superGroupMetaInfo->supergroup_id_;
        return resultType;
    }
    }

}

QSharedPointer<profilePhoto> UsersModel::getUserPhoto(const qint64 userId)
{
    if (!m_users.contains(userId))
        return QSharedPointer<profilePhoto>(nullptr);

    return m_users[userId]->profile_photo_;
}

QString UsersModel::getUserFullName(const int userId)
{
    if (!m_users.contains(userId))
        return tr("Unknown user");

    return QString::fromStdString(m_users[userId]->first_name_) + " " + QString::fromStdString(
               m_users[userId]->last_name_);
}

int UsersModel::getChatMuteFor(const qint64 chatId)
{
    if (!m_chats.contains(chatId))
        return 0;

    return m_chats[chatId]->notification_settings_->mute_for_;
}

void UsersModel::getUpdateNewChat(const QJsonObject &updateNewChatObject)
{
    auto chatItem = ParseObject::parseChat(updateNewChatObject);
    if (chatItem->id_ != 0) {
        m_chats[chatItem->id_] = chatItem;
    }

}

void UsersModel::getUpdateNewUser(const QJsonObject &updateNewUserObject)
{
    auto userItem = ParseObject::parseUser(updateNewUserObject);
    if (userItem->id_ != 0) {
        m_users[userItem->id_] = userItem;
    }
}

void UsersModel::getUpdateNewSupergroup(const QJsonObject &updateNewSupergroupObject)
{
    auto supergroupItem = ParseObject::parseSupergroup(
                              updateNewSupergroupObject["supergroup"].toObject());
    if (supergroupItem->id_ != 0) {
        m_supergroups[supergroupItem->id_] = supergroupItem;
    }

}

void UsersModel::setSmallAvatar(qint64 id, QSharedPointer<file> small)
{
    if (!m_users.contains(id))
        return;

    m_users[id]->profile_photo_->small_ = small;
}

QSharedPointer<ChatMemberStatus> UsersModel::getGroupStatus(qint64 group_id)
{
    if (!m_supergroups.contains(group_id))
        return QSharedPointer<ChatMemberStatus>(nullptr);
    return m_supergroups[group_id]->status_;

}

QSharedPointer<user> UsersModel::getUser(const int userId)
{
    if (!m_users.contains(userId))
        return QSharedPointer<user>(nullptr);
    return m_users[userId];
}

QSharedPointer<UserStatus> UsersModel::getUserStatus(const int userId)
{
    if (!m_users.contains(userId))
        return QSharedPointer<UserStatus>(new userStatusEmpty);
    return m_users[userId]->status_;
}

QString UsersModel::getUserStatusAsString(const QSharedPointer<UserStatus> &userStatus)
{
    switch (userStatus->get_id()) {
    case userStatusLastMonth::ID:
        return tr("last seen within a month");
    case userStatusLastWeek::ID:
        return tr("last seen a week ago");
    case userStatusRecently::ID:
        return tr("last seen recently");
    case userStatusOffline::ID: {
        QDateTime currentDate = QDateTime::currentDateTime();
        qint64 timestamp = static_cast<userStatusOffline *>(userStatus.data())-> was_online_;
        QDateTime lastSeen =  QDateTime::fromMSecsSinceEpoch(timestamp * 1000);
        qint64 diff = currentDate.toMSecsSinceEpoch() - timestamp * 1000;
        QDateTime diffDateTime = QDateTime::fromMSecsSinceEpoch(diff).toUTC();
        qint64 diffDays = QDateTime::fromMSecsSinceEpoch(0).toUTC().daysTo(diffDateTime);
        int hour = diffDateTime.time().hour();
        int minute = diffDateTime.time().minute();
        if (diffDays >= 7)
            return tr("last seen") + " " + lastSeen.toString(Qt::DateFormat::DefaultLocaleShortDate);
        else if (diffDays >= 1 && diffDays < 7)
            return tr("last seen %1 days ago").arg(diffDays);
        else {
            if (hour > 1)
                return tr("last seen %1 hours ago").arg(hour);
            else if (hour == 1)
                return tr("last seen %1 hour ago").arg(hour);
            else {
                if (minute > 1)
                    return tr("last seen %1 minutes ago").arg(minute);
                else
                    return tr("last seen %1 minute ago").arg(minute);
            }
        }
    }
    case userStatusOnline::ID:
        return tr("online");
        break;
    case userStatusEmpty::ID:
    default:
        return "";
    }

}

void UsersModel::updateChatLastMessage(const QJsonObject &chatLastMessageObject)
{
    qint64 chatId = chatLastMessageObject["chat_id"].toVariant().toString().toLongLong();
    qint64 order =  chatLastMessageObject["order"].toString().toLongLong();
    auto lastMessage = ParseObject::parseMessage(chatLastMessageObject["last_message"].toObject());
    if (!m_chats.contains(chatId))
        return;
    m_chats[chatId]->last_message_ = lastMessage;
    m_chats[chatId]->order_ = order;
}

void UsersModel::updateChatReadInbox(const QJsonObject &chatReadInboxObject)
{
    qint64 chatId = ParseObject::getInt64(chatReadInboxObject["chat_id"]);
    qint64 lastReadId = ParseObject::getInt64(chatReadInboxObject["last_read_inbox_message_id"]);
    int unreadCount = chatReadInboxObject["unread_count"].toInt();
    if (!m_chats.contains(chatId))
        return;
    m_chats[chatId]->last_read_inbox_message_id_ = lastReadId;
    m_chats[chatId]->unread_count_ = unreadCount;
}

void UsersModel::updateChatReadOutbox(const QJsonObject &chatReadOutboxObject)
{
    qint64 chatId = ParseObject::getInt64(chatReadOutboxObject["chat_id"]);
    qint64 lastOutboxId = ParseObject::getInt64(chatReadOutboxObject["last_read_outbox_message_id"]);
    if (!m_chats.contains(chatId))
        return;
    m_chats[chatId]->last_read_outbox_message_id_ = lastOutboxId;
}

void UsersModel::updateUserStatus(const QJsonObject &updateUserStatusObject)
{
    int userId = updateUserStatusObject["user_id"].toInt();
    if (m_users.contains(userId)) {
        m_users[userId]->status_ = ParseObject::parseUserStatus(updateUserStatusObject["status"].toObject());
        emit userStatusChanged(userId);
    }
}
} //tdlibQt
