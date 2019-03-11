
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
    void sendToTelegram(void *Client, const char *str);

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

    void checkPassword(const QString &password);
signals:
    void updateNewChat(const QJsonObject &updateNewChatObject);
    void updateNewUser(const QJsonObject &updateNewUserObject);


    void isCredentialsEmptyChanged(bool isCredentialsEmpty);
    void authorizationStateChanged(tdlibQt::Enums::AuthorizationState authorizationState);
    void newAuthorizationState(const QSharedPointer<AuthorizationState> authState);
    void connectionStateChanged(tdlibQt::Enums::ConnectionState connectionState);
    void newChatGenerated(const QJsonObject &chatObject);
    void proxiesReceived(const QJsonObject &proxiesObject);
    void proxyReceived(const QJsonObject &proxyObject);
    void updateFile(const QJsonObject &fileObject);
    void updateSupergroup(const QJsonObject &updateSupergroupObject);
    void callbackQueryAnswerReceived(const QJsonObject &callbackQueryAnswerObject);
    void newMessages(const QJsonObject &messageObject);
    void newMessageFromUpdate(const QJsonObject &messageUpdateObject);
    void updateTotalCount(int totalCount);
    void updateChatOrder(const QJsonObject &chatOrderObject);
    void updateChatLastMessage(const QJsonObject &chatLastMessage);
    void updateChatReadInbox(const QJsonObject &chatReadInbox);
    void updateChatReadOutbox(const QJsonObject &chatReadOutbox);
    void updateMessageSendSucceeded(const QJsonObject &updateMessageSendObject);
    void updateMessageSendFailed(const QJsonObject &updateMessageSendObject);
    void updateMessageEdited(const QJsonObject &updateNewMessageObject);
    void updateMessageContent(const QJsonObject &updateMessageContentObject);
    void updateDeleteMessages(const QJsonObject &updateDeleteMessagesObject);
    void updateNotificationSettingsReceived(const QJsonObject &updateNotificationSettingsObject);
    void updateUserChatAction(const QJsonObject &chatAction);
    void updateChatMention(const QJsonObject &chatAction);
    void updateChatIsMarkedAsUnread(const QJsonObject &chatOrderObject);
    void updateMentionRead(const QJsonObject &messageMentionReadObject);
    void meReceived(const QJsonObject &meObject);
    void errorReceived(const QJsonObject &errorObject);
    void okReceived(const QJsonObject &okObject);
    void fileReceived(const QJsonObject &fileObject);
    void messageReceived(const QJsonObject &messageObject);
    void getChatByLink(const QString &title, const QString &chat_id, const QVariant &chatType,
                       const QString &last_message_inbox_id, const QString &last_message_outbox_id,
                       const QString &last_message_id);
    void stickerSetsReceived(const QJsonObject &stickerSetsObject);
    void stickerSetReceived(const QJsonObject &stickerSetObject);
    void stickersReceived(const QJsonObject &stickersObject);
    void secondsReceived(const QJsonObject &secondsObject);
    void textReceived(const QJsonObject &textObject);

    void errorReceivedMap(const QVariantMap &errorObject);
    void totalUnreadCountChanged(int totalUnreadCount);

public slots:
    void openChat(const QString &chat_id);
    void closeChat(const QString &chat_id);
    void getProxies();
    void addProxy(const QString &address, const int port,
                  const bool &enabled, const QVariantMap &type);
    void editProxy(const int id, const QString &address, const int port,
                   const bool &enabled, const QVariantMap &type);

    void disableProxy();
    void enableProxy(const int id);
    void removeProxy(const int id);
    void pingProxy(const int id);
    void getProxyLink(const int id);

    void setEncryptionKey(const QString &key = "");
    void setPhoneNumber(const QString &phone);
    void checkCode(const QString &code); /*TODO check for numbers only*/
    void setCodeIfNewUser(const QString &code, const QString &firstName,
                          const QString &lastName); /*TODO check for numbers only and escape characters*/
    void getChats(const qint64 offset_chat_id = 0,
                  const qint64 offset_order = std::numeric_limits<std::int64_t>::max(), const int limit = 100);
    void getChat(const qint64 chatId);
    void markChatUnread(const qint64 chatId, const bool flag);
    void downloadFile(int fileId, int priority = 1, const QString &extra = "");
    void getChatHistory(qint64 chat_id = 0, qint64 from_message_id = 0, int offset = 0, int limit = 20,
                        bool only_local = false, const QString &extra = "");
    void getAttachedStickerSets(const int file_id);
    void getStickerSet(const qint64 set_id);
    void getInstalledStickerSets(const bool is_masks = false);
    void getFavoriteStickers();
    void getTrendingStickerSets();
    void getRecentStickers(const bool is_attached = false);
    void logOut();

    void sendMessage(const QString &json);
    void forwardMessage(const qint64 chat_id,
                        const qint64 from_chat_id,
                        const QVector<qint64> message_ids,
                        const bool disable_notification,
                        const bool from_background = false,
                        const bool as_album = false);
    void getMessage(const qint64 chat_id, const qint64 message_id, const QString extra = "");
    void getMessages(const qint64 chat_id, QVector<qint64> message_ids, const QString &extra);
    void viewMessages(const QString &chat_id, const QVariantList &messageIds, const bool force_read);
    void deleteMessages(const qint64 chat_id, const QVector<qint64> message_ids,
                        const bool revoke = false);
    void setChatMemberStatus(const qint64 chat_id, const int user_id,
                             const QString &status);
    void setIsCredentialsEmpty(bool isCredentialsEmpty);
    void setAuthorizationState(tdlibQt::Enums::AuthorizationState &authorizationState);
    void setConnectionState(tdlibQt::Enums::ConnectionState &connState);
    void getMe();
    void requestAuthenticationPasswordRecovery();
    void recoverAuthenticationPassword(const QString &recoveryCode);
    void cancelDownloadFile(int fileId, bool only_if_pending = false);
    void cancelUploadFile(int fileId);
    void joinChatByInviteLink(const QString &link, const QString &extra = "");
    void setTotalUnreadCount(int totalUnreadCount);
    void changeStickerSet(const qint64 set_id, const bool is_installed = false, const bool is_archived = false);
};
} //namespace tdlibQt
#endif // TDLIBJSONWRAPPER_HPP
