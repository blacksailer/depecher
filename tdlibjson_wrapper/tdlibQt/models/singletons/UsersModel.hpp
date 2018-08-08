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
    QMap<qint64, QSharedPointer<supergroup>> m_supergroups;
    QMap<qint64, QSharedPointer<user>> m_users;
    UsersModel(QObject *parent = 0);
public:
    static UsersModel *instance();
    UsersModel(UsersModel const &) = delete;
    void operator=(UsersModel const &)  = delete;

    int getChatMuteFor(const qint64 chatId);
    QString getChatTitle(const qint64 chatId);
    qint64 getLastMessageInbox(const qint64 chatId);
    qint64 getLastMessageOutbox(const qint64 chatId);
    qint64 getLastMessageId(const qint64 chatId);
    QVariantMap getChatType(const qint64 chatId);
    QSharedPointer<profilePhoto> getUserPhoto(const qint64 userId);
    QString getUserFullName(const qint64 userId);
    void setSmallAvatar(qint64 id, QSharedPointer<file> small);
    QSharedPointer<ChatMemberStatus> getGroupStatus(qint64 group_id);
private slots:
    void updateChatLastMessage(const QJsonObject &chatLastMessageObject);
    void updateChatReadInbox(const QJsonObject &chatReadInboxObject);
    void updateChatReadOutbox(const QJsonObject &chatReadOutboxObject);
public slots:
    void getUpdateNewChat(const QJsonObject &updateNewChatObject);
    void getUpdateNewUser(const QJsonObject &updateNewUserObject);
    void getUpdateNewSupergroup(const QJsonObject &updateNewSupergroupObject);

};
} //tdlibQt

#endif // USERSMODEL_HPP
