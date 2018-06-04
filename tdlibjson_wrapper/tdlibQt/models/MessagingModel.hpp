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
    Q_PROPERTY(tdlibQt::Enums::ChatType chatType READ chatType WRITE setChatType NOTIFY chatTypeChanged)
    Q_PROPERTY(QString action READ action WRITE setAction NOTIFY actionChanged)
    Q_PROPERTY(QString currentMessage READ currentMessage WRITE setCurrentMessage NOTIFY
               currentMessageChanged)

    Q_PROPERTY(QString lastMessage READ lastMessage WRITE setLastMessage NOTIFY lastMessageChanged)
    Q_PROPERTY(double lastOutboxId READ lastOutboxId WRITE setLastOutboxId NOTIFY lastOutboxIdChanged)
    Q_PROPERTY(bool atYEnd READ atYEnd WRITE setAtYEnd NOTIFY atYEndChanged)

    QList<QSharedPointer<message>> messages;
    QSharedPointer<ChatMemberStatus> m_UserStatus;
    QMap<int, int> messagePhotoQueue;
    QMap<qint64, QVector<int>> avatarPhotoQueue;
    QVector<qint64> messageIds;
    QMap<qint64, QSharedPointer<updateUserChatAction>> chatActionUserMap;
    QTimer chatActionTimer;
    const int MESSAGE_LIMIT = 20;
    TdlibJsonWrapper *tdlibJson;
    NotificationManager *m_NotificationsManager;
    bool isUpdateConnected = false;
    enum MessageRole {
        ID,
        SENDER_USER_ID,
        SENDER_PHOTO,
        AUTHOR,
        ACTION,
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
        MESSAGE_TYPE //Custom
    };


    void appendMessage(const QJsonObject &messageObject);
    QVariant dataContent(const int rowIndex) const;
    QVariant dataFileMeta(const int rowIndex, int role) const;
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
    void sendTextMessage(const QString &text, const QString &reply_id);
    void sendPhotoMessage(const QString &filepath, const QString &reply_id,
                          const QString &caption = "");
    void sendDocumentMessage(const QString &filepath, const QString &reply_id,
                             const QString &caption = "");
    void sendStickerMessage(const int &fileId, const QString &reply_id
                           );

    void downloadDocument(const int rowIndex);
    void cancelDownload(const int rowIndex);
    void cancelUpload(const int rowIndex);
    void deleteMessages(QList<int> rowIndices, const bool revoke = false);
    void deleteMessage(const int rowIndex, const bool revoke = false);

    void joinChat();
    void getNewMessages();
    void setChatType(const tdlibQt::Enums::ChatType chatType);
    void setCurrentMessage(const QString &currentMessage);
    void setLastMessage(QString lastMessage);
    void setAtYEnd(bool atYEnd);

    void setLastOutboxId(double lastOutboxId)
    {
        if (m_lastOutboxId == lastOutboxId)
            return;

        m_lastOutboxId = lastOutboxId;
        emit lastOutboxIdChanged(lastOutboxId);
    }

signals:
    void userNameChanged(QString userName);
    void peerIdChanged(QString peerId);
    void downloadFileStart(int file_id_, int priority_, int indexItem) const;
    void downloadAvatarStart(qint64 file_id_, int priority_, int indexItem) const;
    void errorReceived(int error_code, const QString &error_message);
    void firstIdChanged();
    void viewMessagesChanged(const qint64 peerId);

    void chatTypeChanged(tdlibQt::Enums::ChatType chatType);

    void actionChanged(QString action);

    void currentMessageChanged(QString currentMessage);

    void lastMessageChanged(QString lastMessage);

    void atYEndChanged(bool atYEnd);

    void lastOutboxIdChanged(double lastOutboxId);

private:
    bool fetchPending = false;
    QString m_userName;
    QString m_peerId;
    int m_totalCount = 1;

    // QAbstractItemModel interface
    tdlibQt::Enums::ChatType m_chatType;

    QString m_action;

    QString m_currentMessage = "";

    QString m_lastMessage = "";

    bool m_atYEnd = 0;

    qint64 m_lastOutboxId;

public:
    void fetchMore(const QModelIndex &parent) override;
    bool canFetchMore(const QModelIndex &parent) const override;
    tdlibQt::Enums::ChatType chatType() const;
    QString action() const;
    QString currentMessage() const;
    QString lastMessage() const;
    bool atYEnd() const;
    enum MessageType {
        TEXT,
        PHOTO,
        STICKER,
        DOCUMENT,
        ANIMATION,
        SYSTEM_NEW_MESSAGE,
        UNDEFINED
    };
    enum MessageState {
        Sending_Failed,
        Sending_Pending,
        Sending_Not_Read,
        Sending_Read
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
    Q_ENUM(MessageState)
    Q_ENUM(ChatMemberStatuses)
    double lastOutboxId() const
    {
        return m_lastOutboxId;
    }
};
} //namespace tdlibQt
Q_DECLARE_METATYPE(tdlibQt::MessagingModel::MessageType)
Q_DECLARE_METATYPE(tdlibQt::MessagingModel::MessageState)
Q_DECLARE_METATYPE(tdlibQt::MessagingModel::ChatMemberStatuses)
#endif // MESSAGINGMODEL_HPP
