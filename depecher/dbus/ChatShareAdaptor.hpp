#ifndef CHATSHAREADAPTOR_HPP
#define CHATSHAREADAPTOR_HPP

#include <QObject>
#include <QDBusMessage>
#include <QDBusVariant>
class QDBusServer;
class QDBusConnection;
namespace tdlibQt {
class TdlibJsonWrapper;
}
class ChatShareAdaptor : public QObject
{
    Q_OBJECT
    struct RequestData {
        QVariant chatList;
        QDBusMessage reply;
    };
    QDBusConnection *m_dbusConnection;
    tdlibQt::TdlibJsonWrapper *m_tdlibJson;

    QDBusServer *m_dbusServer;
    QList<RequestData> m_delayedList;

    QList<qint64> m_chatIds;
    QList<QVariant> m_chats;
public:
    explicit ChatShareAdaptor(QObject *parent = nullptr);
    ~ChatShareAdaptor();
    void sendChatList();

signals:

private slots:
    void addChatItem(const QJsonObject &chatObject);

public slots:
    QDBusVariant getChatList(const qint64 lastChatId, const qint64 order, const QDBusMessage &message);

};

#endif // CHATSHAREADAPTOR_HPP
