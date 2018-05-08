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
        qDebug() << QString::fromStdString(userItem->first_name_) <<
                 QString::fromStdString( userItem->last_name_) <<
                 QString::fromStdString( userItem->username_)  << m_users.size();
    }
}
} //tdlibQt
