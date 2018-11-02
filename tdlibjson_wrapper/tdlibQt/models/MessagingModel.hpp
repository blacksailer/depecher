#ifndef MESSAGINGMODEL_HPP
#define MESSAGINGMODEL_HPP
#include <QAbstractListModel>
#include "tdlibQt/items/TdApi.hpp"
#include "tdlibQt/include/TdlibNamespace.hpp"
namespace tdlibQt {
class TdlibJsonWrapper;
class NotificationManager;
class MessagingModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString peerId READ peerId WRITE setPeerId NOTIFY peerIdChanged)
    Q_PROPERTY(QVariant memberStatus READ memberStatus NOTIFY memberStatusChanged)
    Q_PROPERTY(QVariantMap chatType READ chatType WRITE setChatType NOTIFY chatTypeChanged)
    Q_PROPERTY(QString action READ action WRITE setAction NOTIFY actionChanged)
    Q_PROPERTY(QString lastInbox READ lastInbox WRITE setLastInbox NOTIFY
               lastInboxChanged)

    Q_PROPERTY(QString lastMessage READ lastMessage WRITE setLastMessage NOTIFY lastMessageChanged)
    Q_PROPERTY(double lastOutboxId READ lastOutboxId WRITE setLastOutboxId NOTIFY lastOutboxIdChanged)
    Q_PROPERTY(bool atYEnd READ atYEnd WRITE setAtYEnd NOTIFY atYEndChanged)
    Q_PROPERTY(bool isActive READ isActive WRITE setIsActive NOTIFY isActiveChanged)
    Q_PROPERTY(int lastMessageIndex READ lastMessageIndex NOTIFY lastMessageIndexChanged)
    Q_PROPERTY(bool fetchOlderPending READ fetchOlderPending WRITE setFetchOlderPending NOTIFY fetchOlderPendingChanged)
    Q_PROPERTY(bool reachedHistoryEnd READ reachedHistoryEnd WRITE setReachedHistoryEnd NOTIFY reachedHistoryEndChanged)
    QList<QSharedPointer<message>> messages;
    QSharedPointer<ChatMemberStatus> m_UserStatus;
    QMap<int, int> messagePhotoQueue;
    QMap<qint64, QVector<int>> avatarPhotoQueue;
    QVariantList unseenMessageIds;
    QMap<qint64, QSharedPointer<updateUserChatAction>> chatActionUserMap;
    QMap<qint64, QSharedPointer<message>> replyMessagesMap;
    QTimer chatActionTimer;
    TdlibJsonWrapper *tdlibJson;
    NotificationManager *m_NotificationsManager;
    bool isUpdateConnected = false;
    bool isAllOldMessages = false;
    enum MessageRole {
        ID,
        SENDER_USER_ID,
        SENDER_PHOTO,
        AUTHOR,
        ACTION,
        MEMBER_STATUS,
        CHAT_ID,
        SENDING_STATE,
        IS_OUTGOING,
        CAN_BE_EDITED,
        CAN_BE_FORWARDED,
        CAN_BE_DELETED_ONLY_FOR_YOURSELF,
        CAN_BE_DELETED_FOR_ALL_USERS,
        IS_CHANNEL_POST,
        CONTAINS_UNREAD_MENTION,
        DATE,
        EDIT_DATE,
        FORWARD_INFO,
        REPLY_TO_MESSAGE_ID,
        REPLY_AUTHOR,
        REPLY_MESSAGE,
        TTL,
        TTL_EXPIRES_IN,
        VIA_BOT_USER_ID,
        AUTHOR_SIGNATURE,
        VIEWS,
        MEDIA_ALBUM_ID,
        MEDIA_PREVIEW,
        CONTENT,
        FILE_CAPTION,
        PHOTO_ASPECT,
        DOCUMENT_NAME,
        REPLY_MARKUP,
        FILE_IS_DOWNLOADING,
        FILE_IS_UPLOADING,
        FILE_DOWNLOADING_COMPLETED,
        FILE_UPLOADING_COMPLETED,
        FILE_DOWNLOADED_SIZE,
        FILE_UPLOADED_SIZE,
        FILE_TYPE,
        STICKER_SET_ID,
        SECTION, //Custom
        MESSAGE_TYPE //Custom
    };

    QString messageTypeToString(MessageContent *messageContent) const;
    void appendMessage(const QJsonObject &messageObject);
    QVariant dataContent(const int rowIndex) const;
    QVariant dataFileMeta(const int rowIndex, int role) const;
    QSharedPointer<message> findMessageById(const qint64 messageId) const;
    bool canFetchOlder();
private slots:
    void chatActionCleanUp();
    void getFile(const int fileId, const int priority, const int indexItem);
    void getAvatar(const qint64 fileId, const int priority, const int indexItem);
    void processFile(const QJsonObject &fileObject);
    void updateChatReadInbox(const QJsonObject &inboxObject);
    void updateChatReadOutbox(const QJsonObject &outboxObject);
    void appendMessages(const QJsonObject &messagesObject);
    void prependMessage(const QJsonObject &messageObject);
    void addMessageFromUpdate(const QJsonObject &messageUpdateObject);
    void updateFile(const QJsonObject &fileObject);
    //If total count from getChatHistory == zero, then end of chat.
    void updateTotalCount(int totalCount);
    void updateChatAction(const QJsonObject &chatActionObject);
    void viewMessages(const QVariantList &ids);
    void setAction(const QString &action);
    void updateMessageSend(const QJsonObject &updateMessageSendObject);
    void onActiveChanged(const bool isActive);
    void onMessageContentEdited(const QJsonObject &updateMessageContentObject);
    void onMessageEdited(const QJsonObject &updateMessageEditedObject);
    void onMessageDeleted(const QJsonObject &updateDeleteMessagesObject);
    void onCallbackAnswerReceived(const QJsonObject &callbackAnswerObject);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    QString userName() const;
    QString peerId() const;

    MessagingModel();
    ~MessagingModel();
public slots:

    void setUserName(QString userName);
    void setPeerId(QString peerId);
    void sendTextMessage(const QString &text = "", const QString &reply_id = "0");
    void sendPhotoMessage(const QString &filepath, const QString &reply_id,
                          const QString &caption = "");
    void sendDocumentMessage(const QString &filepath, const QString &reply_id,
                             const QString &caption = "");
    void sendStickerMessage(const int &fileId, const QString &reply_id
                           );
    void getCallbackQueryAnswerFunc(const QString &messageId, const QString &payloadType,
                                    const QString &payloadData);

    void downloadDocument(const int rowIndex);
    void cancelDownload(const int rowIndex);
    void cancelUpload(const int rowIndex);
    void deleteMessages(QList<int> rowIndices, const bool revoke = false);
    void deleteMessage(const int rowIndex, const bool revoke = false);

    void joinChat();
    void fetchOlder();
    void setChatType(const QVariantMap &chatType);
    void setLastInbox(const QString &lastInbox);
    void setLastMessage(QString lastMessage);
    void setAtYEnd(bool atYEnd);

    void setLastOutboxId(double lastOutboxId);

    void setIsActive(bool isActive);

    void setLastMessageIndex(int lastMessageIndex)
    {
        if (m_lastMessageIndex == lastMessageIndex)
            return;

        m_lastMessageIndex = lastMessageIndex;
        emit lastMessageIndexChanged(m_lastMessageIndex);
    }

    void setFetchOlderPending(bool fetchOlderPending)
    {
        if (m_fetchOlderPending == fetchOlderPending)
            return;

        m_fetchOlderPending = fetchOlderPending;
        emit fetchOlderPendingChanged(m_fetchOlderPending);
    }

    void setReachedHistoryEnd(bool reachedHistoryEnd)
    {
        if (m_reachedHistoryEnd == reachedHistoryEnd)
            return;

        m_reachedHistoryEnd = reachedHistoryEnd;
        emit reachedHistoryEndChanged(m_reachedHistoryEnd);
    }

signals:
    void userNameChanged(QString userName);
    void peerIdChanged(QString peerId);
    void downloadFileStart(int file_id_, int priority_, int indexItem) const;
    void downloadAvatarStart(qint64 file_id_, int priority_, int indexItem) const;
    void fetchOldMessages() const;
    void errorReceived(int error_code, const QString &error_message);
    void firstIdChanged();
    void viewMessagesChanged(const qint64 peerId);

    void chatTypeChanged(const QVariantMap &chatType);
    void callbackQueryAnswerShow(const QString &text, const bool show_alert);

    void actionChanged(QString action);

    void lastInboxChanged(QString lastInbox);

    void lastMessageChanged(QString lastMessage);

    void atYEndChanged(bool atYEnd);

    void lastOutboxIdChanged(double lastOutboxId);

    void memberStatusChanged(const QVariant &memberStatus);

    void isActiveChanged(bool isActive);

    void lastMessageIndexChanged(int lastMessageIndex);

    void fetchOlderPendingChanged(bool fetchOlderPending);

    void reachedHistoryEndChanged(bool reachedHistoryEnd);

private:
    bool fetchPending = false;
    QString m_userName;
    QString m_peerId;
    int m_totalCount = 1;

    QVariantMap m_chatType;

    QString m_action;

    QString m_lastMessageInbox = "";

    QString m_lastMessage = "";

    bool m_atYEnd = false;

    qint64 m_lastOutboxId;
    bool m_isActive;

    int m_lastMessageIndex;

    bool m_fetchOlderPending = false;

    bool m_reachedHistoryEnd = false;

public:
    void fetchMore(const QModelIndex &parent) override;
    bool canFetchMore(const QModelIndex &parent) const override;
    QVariantMap chatType() const;
    QString action() const;
    QString lastInbox() const;
    QString lastMessage() const;
    bool atYEnd() const;
    enum MessageType {
        TEXT,
        PHOTO,
        STICKER,
        DOCUMENT,
        ANIMATION,
        SYSTEM_NEW_MESSAGE,
        CONTACT,
        JOINBYLINK,
        CONTACT_REGISTERED,
        CHAT_CREATED,
        UNDEFINED
    };

    enum ChatMemberStatuses {
        Administrator,
        Banned,
        Restricted,
        Left,
        Member,
        Creator
    };
    Q_ENUM(MessageType)
    Q_ENUM(ChatMemberStatuses)
    double lastOutboxId() const;
    QVariant memberStatus() const;
    bool isActive() const
    {
        return m_isActive;
    }
    int lastMessageIndex() const
    {
        return m_lastMessageIndex;
    }
    bool fetchOlderPending() const
    {
        return m_fetchOlderPending;
    }
    bool reachedHistoryEnd() const
    {
        return m_reachedHistoryEnd;
    }
};
} //namespace tdlibQt
Q_DECLARE_METATYPE(tdlibQt::MessagingModel::MessageType)
Q_DECLARE_METATYPE(tdlibQt::MessagingModel::ChatMemberStatuses)
#endif // MESSAGINGMODEL_HPP
