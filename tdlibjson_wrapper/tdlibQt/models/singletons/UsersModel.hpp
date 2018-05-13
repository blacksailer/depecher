#ifndef USERSMODEL_HPP
#define USERSMODEL_HPP

#include <QObject>
#include "tdlibQt/items/TdApi.hpp"

namespace tdlibQt {
class TdlibJsonWrapper;
class UsersModel : public QObject
{
    Q_OBJECT
    TdlibJsonWrapper *m_client;
    QMap<qint64, QSharedPointer<chat>> m_chats;
    QMap<qint64, QSharedPointer<user>> m_users;
    UsersModel(QObject *parent = 0);
public:
    static UsersModel *instance();
    UsersModel(UsersModel const &) = delete;
    void operator=(UsersModel const &)  = delete;

    int getChatMuteFor(const quint64 chatId);
    QString getChatTitle(const quint64 chatId);
    QSharedPointer<profilePhoto> getUserPhoto(const quint64 userId);
    QString getUserFullName(const quint64 userId);
    void setSmallAvatar(quint64 id, QSharedPointer<file> small);

public slots:
    void getUpdateNewChat(const QJsonObject &updateNewChatObject);
    void getUpdateNewUser(const QJsonObject &updateNewUserObject);
};
} //tdlibQt

#endif // USERSMODEL_HPP
