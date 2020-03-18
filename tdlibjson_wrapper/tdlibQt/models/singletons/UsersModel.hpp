#ifndef USERSMODEL_HPP
#define USERSMODEL_HPP

#include <QObject>
#include "tdlibQt/items/TdApi.hpp"

namespace tdlibQt {
class TdlibJsonWrapper;
class UsersModel : public QObject
{
    Q_OBJECT
    TdlibJsonWrapper *m_tdlibJson;
    QMap<qint64, QSharedPointer<chat>> m_chats;
    QMap<int, QSharedPointer<supergroup>> m_supergroups;
    QMap<int, QSharedPointer<basicGroup>> m_groups;
    QMap<int, QSharedPointer<user>> m_users;
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
    QString getUserFirstName(const int userId);
    QString getUserFullName(const int userId);
    QString getUsername(const int userId);
    void setSmallAvatar(qint64 id, QSharedPointer<file> small);
    QSharedPointer<UserType> getUserType(const int userId);
    QSharedPointer<profilePhoto> getUserPhoto(const int userId);
    QSharedPointer<ChatMemberStatus> getGroupStatus(int group_id);
    QSharedPointer<user> getUser(const int userId);
    QSharedPointer<basicGroup> getGroup(const int groupId);

    QSharedPointer<supergroup> getSupergroup(const int supergroupId);
    QSharedPointer<chat> getChat(const qint64 chatId);
    QSharedPointer<UserStatus> getUserStatus(const int userId);
    static QString getUserStatusAsString(const QSharedPointer<UserStatus> &userStatus);

signals:
    void userStatusChanged(const int userId);
private slots:
    void updateChatLastMessage(const QJsonObject &chatLastMessageObject);
    void updateChatReadInbox(const QJsonObject &chatReadInboxObject);
    void updateChatReadOutbox(const QJsonObject &chatReadOutboxObject);
    void updateUserStatus(const QJsonObject &updateUserStatusObject);
    void getUpdateNewChat(const QJsonObject &updateNewChatObject);
    void getUpdateUser(const QJsonObject &updateNewUserObject);
    void parseUser(const QJsonObject &userObject);

    void getUpdateNewSupergroup(const QJsonObject &updateNewSupergroupObject);
    void getUpdateGroup(const QJsonObject &updateGroupObject);
};
} //tdlibQt

#endif // USERSMODEL_HPP
