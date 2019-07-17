#ifndef CHATSHAREPROXYMODEL_HPP
#define CHATSHAREPROXYMODEL_HPP

#include <QAbstractListModel>
#include "../tdlibjson_wrapper/tdlibQt/items/TdApi.hpp"
class QDBusInterface;
class QDBusPendingCallWatcher;
class ChatShareModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QVariant answer READ answer WRITE setAnswer NOTIFY answerChanged)

    QAbstractListModel *m_model;
    QDBusInterface *remoteAppIface;
    QList<QSharedPointer<tdlibQt::chat>> m_chats;
    bool m_fetchPending = false;
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
        IS_SPONSORED,
        IS_MARKED_UNREAD,
        UNREAD_COUNT,
        UNREAD_MENTION_COUNT,
        NOTIFICATION_SETTINGS,
        REPLY_MARKUP_MESSAGE_ID,
        DRAFT_MESSAGE,
        CLIENT_DATA,
        SENDING_STATE
    };

public:
    ChatShareModel(QObject *parent = 0);
    ~ChatShareModel();
    QVariant answer() const;
public slots:
    void setAnswer(QVariant answer);
    void addItems(QDBusPendingCallWatcher *call);
signals:
    void answerChanged(QVariant answer);
private:
    QVariant m_answer;
    QVariantMap parseDBusArgument(QMap<QString, QVariant> value);
    // QAbstractItemModel interface
    QVariantList parseDBusArgumentArray(QVariantList srcArray);
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const override;

    // QAbstractItemModel interface
public:
    void fetchMore(const QModelIndex &parent) override;

    // QAbstractItemModel interface
public:
    bool canFetchMore(const QModelIndex &parent) const override;
};

#endif // CHATSHAREPROXYMODEL_HPP
