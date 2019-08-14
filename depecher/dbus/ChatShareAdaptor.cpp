#include "ChatShareAdaptor.hpp"
#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/ParseObject.hpp"
#include <QDebug>
#include <QFile>
#include <QDBusServer>
#include <QDBusConnection>

static const QString c_dbusObjectPath = QStringLiteral("/org/blacksailer/depecher/share");
static const QString c_dbusInterface = QStringLiteral("org.blacksailer.depecher.share");
static const QString c_extraName = QStringLiteral("dbus");

ChatShareAdaptor::ChatShareAdaptor(QObject *parent) : QObject(parent)
{
    m_dbusServer = new QDBusServer("unix:path=/tmp/depecher", this);
    connect(m_dbusServer, &QDBusServer::newConnection,
    [this](const QDBusConnection & dbus) {
        qDebug() << "New Connection";
        m_dbusConnection = new QDBusConnection(dbus);
        m_dbusConnection->registerObject(c_dbusObjectPath, c_dbusInterface, this, QDBusConnection::RegisterOption::ExportAllSlots);
    });
    m_tdlibJson = tdlibQt::TdlibJsonWrapper::instance();

    connect(m_tdlibJson, &tdlibQt::TdlibJsonWrapper::chatReceived,
            this, &ChatShareAdaptor::addChatItem);
    connect(m_tdlibJson, &tdlibQt::TdlibJsonWrapper::chatsReceived,
    [this](const QJsonObject & chatsObject) {
        if (chatsObject.keys().contains("@extra")) {
            if (chatsObject["@extra"].toString() == c_extraName) {
                foreach (auto item, chatsObject["chat_ids"].toArray()) {
                    qDebug() << m_chatIds.size();
                    switch (item.type()) {
                    case QJsonValue::Double:
                        m_chatIds.append((qint64)item.toDouble());
                        break;
                    case QJsonValue::String:
                        m_chatIds.append((qint64)item.toString().toLongLong());
                        break;
                    default:
                        break;
                    }
                }
            }
            foreach (qint64 item, m_chatIds) {
                m_tdlibJson->getChat(item, c_extraName);
            }
        }

    });

}
void ChatShareAdaptor::addChatItem(const QJsonObject &chatObject)
{

    if (chatObject.keys().contains("@extra")) {
        if (chatObject["@extra"].toString() == c_extraName) {
            m_chats.append(chatObject.toVariantMap());
            qDebug() << m_chats.size() << m_chatIds.size();
            if (m_chats.size() == m_chatIds.size())
                sendChatList();
        }
    }
}
void ChatShareAdaptor::sendChatList()
{
    QDBusMessage reply = m_delayedList.last().reply;
    reply << m_chats;
    m_dbusConnection->send(reply);
    m_delayedList.removeLast();
    m_chatIds.clear();
    m_chats.clear();
}

QDBusVariant ChatShareAdaptor::getChatList(const qint64 lastChatId, const qint64 order, const QDBusMessage &message)
{
    m_delayedList.append(RequestData());
    message.setDelayedReply(true);
    m_delayedList.last().reply = message.createReply();
    qDebug() << "Received dbus chat" << lastChatId << order;
    m_tdlibJson->getChats(lastChatId,
                          order,
                          5,
                          c_extraName);

    return QDBusVariant(QVariant());
}

ChatShareAdaptor::~ChatShareAdaptor()
{
    delete m_dbusConnection;
}
