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
    QVector<qint64> messageIds;
    QMap<qint64, QSharedPointer<updateUserChatAction>> chatActionUserMap;
    QTimer chatActionTimer;
    const int MESSAGE_LIMIT = 20;
    TdlibJsonWrapper *tdlibJson;
    bool isUpdateConnected = false;
    enum MessageRole {
        ID,
        SENDER_USER_ID,
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
        PHOTO_CAPTION,
        REPLY_MARKUP,
        MESSAGE_TYPE //Custom
    };
    enum MessageType {
        TEXT,
        PHOTO,
        STICKER,
        SYSTEM_NEW_MESSAGE,
        UNDEFINED
    };
    void appendMessage(const QJsonObject &messageObject);
private slots:
    void chatActionCleanUp();
    void getFile(const int fileId, const int priority, const int indexItem);
    void updateChatReadInbox(const QJsonObject &outboxObject);
public slots:
    void appendMessages(const QJsonObject &messagesObject);
    void prependMessage(const QJsonObject &messageObject);
    void addMessageFromUpdate(const QJsonObject &messageUpdateObject);
    void updateFile(const QJsonObject &fileObject);
    //If total count from getChatHistory == zero, then end of chat.
    void updateTotalCount(int totalCount);
    void updateChatAction(const QJsonObject &chatActionObject);
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
    void viewMessages(const QVariantList &ids);
    void getNewMessages();

    void setChatType(tdlibQt::Enums::ChatType chatType)
    {
        if (m_chatType == chatType)
            return;

        m_chatType = chatType;
        emit chatTypeChanged(chatType);
    }

    void setAction(QString action)
    {
        if (m_action == action)
            return;

        m_action = action;
        emit actionChanged(action);
    }

    void setCurrentMessage(QString currentMessage)
    {
        if (m_currentMessage == currentMessage)
            return;

        m_currentMessage = currentMessage;
        emit currentMessageChanged(currentMessage);
    }

    void setLastMessage(QString lastMessage)
    {
        if (m_lastMessage == lastMessage)
            return;

        m_lastMessage = lastMessage;
        emit lastMessageChanged(lastMessage);
    }

    void setAtYEnd(bool atYEnd);

signals:
    void userNameChanged(QString userName);
    void peerIdChanged(QString peerId);
    void downloadFileStart(int file_id_, int priority_, int indexItem) const;

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
    tdlibQt::Enums::ChatType chatType() const
    {
        return m_chatType;
    }
    QString action() const
    {
        return m_action;
    }
    QString currentMessage() const
    {
        return m_currentMessage;
    }
    QString lastMessage() const
    {
        return m_lastMessage;
    }
    bool atYEnd() const
    {
        return m_atYEnd;
    }
};
} //namespace tdlibQt
#endif // MESSAGINGMODEL_HPP
