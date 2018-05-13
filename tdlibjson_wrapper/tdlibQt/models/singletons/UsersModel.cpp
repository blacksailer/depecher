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
        return "Uknown user";

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
        qDebug() << QString::fromStdString(chatItem->title_) << m_chats.size();
    }

}

void UsersModel::getUpdateNewUser(const QJsonObject &updateNewUserObject)
{
    auto userItem = ParseObject::parseUser(updateNewUserObject);
    if (userItem->id_ != 0) {
        m_users[userItem->id_] = userItem;
        if (userItem->profile_photo_.data()) {
            if (userItem->profile_photo_->small_.data())
                qDebug() << QString::fromStdString(userItem->first_name_) <<
                         QString::fromStdString( userItem->last_name_) <<
                         userItem->profile_photo_->id_
                         << QString::fromStdString( userItem->username_)  << m_users.size() ;
        }
    }
}

void UsersModel::setSmallAvatar(quint64 id, QSharedPointer<file> small)
{
    if (!m_users.contains(id))
        return;

    m_users[id]->profile_photo_->small_ = small;
}
} //tdlibQt
