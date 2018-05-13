#ifndef MESSAGINGMODEL_HPP
#define MESSAGINGMODEL_HPP
#include <QAbstractListModel>
#include "tdlibQt/items/TdApi.hpp"
#include "tdlibQt/include/TdlibNamespace.hpp"
namespace tdlibQt {
class TdlibJsonWrapper;
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
    Q_PROPERTY(bool atYEnd READ atYEnd WRITE setAtYEnd NOTIFY atYEndChanged)

    QList<QSharedPointer<message>> messages;
    QMap<int, int> messagePhotoQueue;
    QMap<qint64, QVector<int>> avatarPhotoQueue;
    QVector<qint64> messageIds;
    QMap<qint64, QSharedPointer<updateUserChatAction>> chatActionUserMap;
    QTimer chatActionTimer;
    const int MESSAGE_LIMIT = 20;
    TdlibJsonWrapper *tdlibJson;
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
    void updateChatReadInbox(const QJsonObject &outboxObject);
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    QString userName() const;
    QString peerId() const;

    MessagingModel();
    ~MessagingModel();
private slots:
    void appendMessages(const QJsonObject &messagesObject);
    void prependMessage(const QJsonObject &messageObject);
    void addMessageFromUpdate(const QJsonObject &messageUpdateObject);
    void updateFile(const QJsonObject &fileObject);
    //If total count from getChatHistory == zero, then end of chat.
    void updateTotalCount(int totalCount);
    void updateChatAction(const QJsonObject &chatActionObject);
    void viewMessages(const QVariantList &ids);
    void setAction(const QString &action);

public slots:

    void setUserName(QString userName);
    void setPeerId(QString peerId);
    void sendTextMessage(const QString &text, const QString &reply_id);
    void sendPhotoMessage(const QString &filepath, const QString &reply_id,
                          const QString &caption = "");
    void sendDocumentMessage(const QString &filepath, const QString &reply_id,
                             const QString &caption = "");

    void downloadDocument(const int rowIndex);
    void cancelDownload(const int rowIndex);
    void cancelUpload(const int rowIndex);
    void getNewMessages();
    void setChatType(const tdlibQt::Enums::ChatType chatType);
    void setCurrentMessage(const QString &currentMessage);
    void setLastMessage(QString lastMessage);
    void setAtYEnd(bool atYEnd);

signals:
    void userNameChanged(QString userName);
    void peerIdChanged(QString peerId);
    void downloadFileStart(int file_id_, int priority_, int indexItem) const;
    void downloadAvatarStart(qint64 file_id_, int priority_, int indexItem) const;
    void firstIdChanged();

    void chatTypeChanged(tdlibQt::Enums::ChatType chatType);

    void actionChanged(QString action);

    void currentMessageChanged(QString currentMessage);

    void lastMessageChanged(QString lastMessage);

    void atYEndChanged(bool atYEnd);

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
    Q_ENUM(MessageType)

};
} //namespace tdlibQt
Q_DECLARE_METATYPE(tdlibQt::MessagingModel::MessageType)

#endif // MESSAGINGMODEL_HPP
