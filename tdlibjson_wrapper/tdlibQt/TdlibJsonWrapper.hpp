#ifndef TDLIBJSONWRAPPER_HPP
#define TDLIBJSONWRAPPER_HPP

#include <QObject>
#include <QJsonObject>
#include <QDebug>
#include "items/TdApi.hpp"
#include "include/TdlibNamespace.hpp"
#include <td/telegram/td_json_client.h>
#include "ListenScheduler.hpp"
class QThread;

namespace tdlibQt {
class ListenObject;
class ParseObject;

class TdlibJsonWrapper : public QObject
{

    Q_OBJECT
    Q_PROPERTY(bool isCredentialsEmpty READ isCredentialsEmpty WRITE setIsCredentialsEmpty NOTIFY
               isCredentialsEmptyChanged)
    Q_PROPERTY(tdlibQt::Enums::AuthorizationState authorizationState READ authorizationState WRITE
               setAuthorizationState
               NOTIFY authorizationStateChanged)
    Q_PROPERTY(tdlibQt::Enums::ConnectionState connectionState READ connectionState WRITE
               setConnectionState
               NOTIFY
               connectionStateChanged)
    Q_PROPERTY(int totalUnreadCount READ totalUnreadCount WRITE setTotalUnreadCount NOTIFY
               totalUnreadCountChanged)

    QThread *listenThread;
    QThread *listenSchedulerThread;
    QThread *parseThread;
    ListenScheduler *listenScheduler;
    ListenObject *listenObject;
    void *client;

    bool m_isCredentialsEmpty;
    tdlibQt::Enums::AuthorizationState m_authorizationState;
    tdlibQt::Enums::ConnectionState m_connectionState;
    explicit TdlibJsonWrapper(QObject *parent = 0);

    int m_totalUnreadCount;

public:
    ParseObject *parseObject;
    static TdlibJsonWrapper *instance();
    TdlibJsonWrapper(TdlibJsonWrapper const &) = delete;
    void operator=(TdlibJsonWrapper const &)  = delete;
    ~TdlibJsonWrapper();

    void startListen();
    void stopListen();
    bool isCredentialsEmpty() const;

    tdlibQt::Enums::AuthorizationState authorizationState() const;

    tdlibQt::Enums::ConnectionState connectionState() const;

    int totalUnreadCount() const
    {
        return m_totalUnreadCount;
    }

signals:
    void updateNewChat(const QJsonObject &updateNewChatObject);
    void updateNewUser(const QJsonObject &updateNewUserObject);


    void isCredentialsEmptyChanged(bool isCredentialsEmpty);
    void authorizationStateChanged(tdlibQt::Enums::AuthorizationState authorizationState);
    void newAuthorizationState(const QSharedPointer<AuthorizationState> authState);
    void connectionStateChanged(tdlibQt::Enums::ConnectionState connectionState);
    void newChatGenerated(const QJsonObject &chatObject);
    void proxyReceived(const QJsonObject &proxyObject);
    void updateFile(const QJsonObject &fileObject);

    void newMessages(const QJsonObject &messageObject);
    void newMessageFromUpdate(const QJsonObject &messageUpdateObject);
    void updateTotalCount(int totalCount);
    void updateChatOrder(const QJsonObject &chatOrderObject);
    void updateChatLastMessage(const QJsonObject &chatLastMessage);
    void updateChatReadInbox(const QJsonObject &chatReadInbox);
    void updateChatReadOutbox(const QJsonObject &chatReadOutbox);
    void updateMessageSendSucceeded(const QJsonObject &updateMessageSendObject);
    void updateUserChatAction(const QJsonObject &chatAction);
    void updateChatMention(const QJsonObject &chatAction);
    void updateMentionRead(const QJsonObject &messageMentionReadObject);
    void meReceived(const QJsonObject &meObject);

    void totalUnreadCountChanged(int totalUnreadCount);

public slots:
    void openChat(const QString &chat_id);
    void closeChat(const QString &chat_id);
    void getProxy();
    void setProxy(const QString &type = "proxyEmpty", const QString &address = "",
                  const int port = 0, const QString &username = "",
                  const QString &password = "");


    void setEncryptionKey(const QString &key = "");
    void setPhoneNumber(const QString &phone);
    void setCode(const QString &code); /*TODO check for numbers only*/
    void setCodeIfNewUser(const QString &code, const QString &firstName,
                          const QString &lastName); /*TODO check for numbers only and escape characters*/
    void getChats(const qint64 offset_chat_id = 0,
                  const qint64 offset_order = std::numeric_limits<std::int64_t>::max(), const int limit = 100);
    void getChat(const qint64 chatId);
    void downloadFile(int fileId, int priority = 1, const QString &extra = "");
    void getChatHistory(qint64 chat_id = 0, qint64 from_message_id = 0, int offset = 0, int limit = 20,
                        bool only_local = false, const QString &extra = "");
    void logOut();
    void sendTextMessage(const QString &json);
    void viewMessages(const QString &chat_id, const QVariantList &messageIds, bool force_read);
    void setIsCredentialsEmpty(bool isCredentialsEmpty);
    void setAuthorizationState(tdlibQt::Enums::AuthorizationState &authorizationState);
    void setConnectionState(tdlibQt::Enums::ConnectionState &connState);
    void getMe();
    void setTotalUnreadCount(int totalUnreadCount)
    {
        if (m_totalUnreadCount == totalUnreadCount)
            return;

        m_totalUnreadCount = totalUnreadCount;
        emit totalUnreadCountChanged(totalUnreadCount);
    }
};
} //namespace tdlibQt
#endif // TDLIBJSONWRAPPER_HPP
