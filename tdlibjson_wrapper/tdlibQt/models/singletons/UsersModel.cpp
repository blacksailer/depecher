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
}

UsersModel *UsersModel::instance()
{
    static UsersModel  instance;
    return &instance;

}

QString UsersModel::getChatTitle(const quint64 chatId)
{
    if (!m_chats.contains(chatId))
        return tr("Uknown chat");

    return QString::fromStdString(m_chats[chatId]->title_);
}

QSharedPointer<profilePhoto> UsersModel::getUserPhoto(const quint64 userId)
{
    if (!m_users.contains(userId))
        return QSharedPointer<profilePhoto>(nullptr);

    return m_users[userId]->profile_photo_;
}

QString UsersModel::getUserFullName(const quint64 userId)
{
    if (!m_users.contains(userId))
        return tr("Uknown user");

    return QString::fromStdString(m_users[userId]->first_name_) + " " + QString::fromStdString(
               m_users[userId]->last_name_);
}

int UsersModel::getChatMuteFor(const quint64 chatId)
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

void UsersModel::setSmallAvatar(quint64 id, QSharedPointer<file> small)
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
} //tdlibQt
