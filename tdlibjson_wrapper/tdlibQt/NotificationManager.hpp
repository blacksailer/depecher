#ifndef NOTIFICATIONMANAGER_HPP
#define NOTIFICATIONMANAGER_HPP

#include <QObject>
#include <QMap>
#include <nemonotifications-qt5/notification.h>
#include "include/TdlibNamespace.hpp"
#include <QSharedPointer>
namespace tdlibQt {
class TdlibJsonWrapper;

class NotificationManager : public QObject
{
    Q_OBJECT

    TdlibJsonWrapper *m_client;
    static const int m_expireTimeout = 60 * 60 * 1000;
    QMap<qint64, QSharedPointer<Notification>> m_chatIdsPublished;
    Enums::ConnectionState m_connectionState;
    explicit NotificationManager(QObject *parent = 0);
    void publishNotifications();
public:
    qint64 currentViewableChatId = 0; //Setted by MessageModel
    static NotificationManager *instance();
    NotificationManager(NotificationManager const &) = delete;
    void operator=(NotificationManager const &)  = delete;
    void removeNotification(qint64 chatId);

signals:

private slots:
    void getUpdateChatOutbox(const QJsonObject &chatReadOutbox);
    void gotNewMessage(const QJsonObject &updateNewMessage);

public slots:
    void notifySummary(const qint64 timestamp, const QString &summary, const QString &body,
                       const qint64 chatId, const qint64 unreadCount = 0);
    void notifyPreview(const qint64 timestamp, const QString &summary, const QString &body,
                       const qint64 chatId, const qint64 unreadCount = 0);

};
}// tdlibQt

#endif // NOTIFICATIONMANAGER_HPP
