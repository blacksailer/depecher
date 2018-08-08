#ifndef CHATSMODEL_HPP
#define CHATSMODEL_HPP

#include <QAbstractListModel>
#include <QJsonObject>
#include <memory>
#include "tdlibQt/items/TdApi.hpp"

namespace tdlibQt {
class TdlibJsonWrapper;
class ChatsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int totalUnreadCount READ totalUnreadCount NOTIFY
               totalUnreadCountChanged)
    QList<QSharedPointer<chat>> chats;
    QMap<qint64, QSharedPointer<updateUserChatAction>> chatActionMap;
    QVector<int> chatActionIndices;
    QTimer chatActionTimer;
    enum Roles {
        ID,
        TYPE,
        TITLE,
        DATE,
        PHOTO,
        MUTE_FOR,
        CHAT_ACTION,
        LAST_MESSAGE,
        LAST_MESSAGE_ID,
        LAST_MESSAGE_AUTHOR,
        LAST_MESSAGE_INBOX_ID,
        LAST_MESSAGE_OUTBOX_ID,
        ORDER,
        IS_PINNED,
        UNREAD_COUNT,
        UNREAD_MENTION_COUNT,
        NOTIFICATION_SETTINGS,
        REPLY_MARKUP_MESSAGE_ID,
        DRAFT_MESSAGE,
        CLIENT_DATA,
        SENDING_STATE
    };
    TdlibJsonWrapper *tdlibJson;
    void changeChatOrder(qint64 chatId, qint64 order);
    bool fetchPending = false;
public:
    explicit ChatsModel(QObject *parent = 0);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
//    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild);
    void fetchMore(const QModelIndex &parent) override;
    QHash<int, QByteArray> roleNames() const override;
    bool canFetchMore(const QModelIndex &parent) const override;
    int getIndex(const qint64 chatId);

    int totalUnreadCount() const
    {
        int result = 0;
        for (auto item : chats) {
            result += item->unread_mention_count_;
            if (item->notification_settings_->mute_for_ == 0)
                result += item->unread_count_;
        }
        return result;
    }
private slots:
    void chatActionCleanUp();
    void addChat(const QJsonObject &chatObject);
    void updateChatPhoto(const QJsonObject &chatObject);
    void updateChatOrder(const QJsonObject &chatOrderObject);
    void updateChatLastMessage(const QJsonObject &chatLastMessageObject);
    void updateChatReadInbox(const QJsonObject &chatReadInboxObject);
    void updateChatReadOutbox(const QJsonObject &chatReadOutboxObject);

    void updateChatAction(const QJsonObject &chatActionObject);
    void sortByOrder();
    void updateChatMentionCount(const QJsonObject &chatMentionCountObject);
    void updateMentionRead(const QJsonObject &messageMentionReadObject);
    void updateNotificationSettings(const QJsonObject &updateNotificationSettingsObject);
signals:

    void totalUnreadCountChanged(int totalUnreadCount);

public slots:
    void changeNotificationSettings(const QString &chatId, bool mute);
    void reset();
};
} // namespace tdlibQt
#endif // CHATSMODEL_HPP
