#ifndef NOTIFICATIONMANAGER_HPP
#define NOTIFICATIONMANAGER_HPP

#include <QObject>
#include <QMap>
#include <nemonotifications-qt5/notification.h>
#include <QSharedPointer>
class NotificationManager : public QObject
{
    Q_OBJECT

    static const int m_ExpireTimeout = 60 * 60 * 1000;
    QMap<qint64, QSharedPointer<Notification>> chatIdsPublished;
    explicit NotificationManager(QObject *parent = 0);
public:
    qint64 currentViewableChatId = 0; //Setted by MessageModel
    static NotificationManager *instance();
    NotificationManager(NotificationManager const &) = delete;
    void operator=(NotificationManager const &)  = delete;
    void removeNotification(qint64 chatId);

signals:

public slots:
    void notifySummary(qint64 timestamp, const QString &summary, const QString &body,
                       qint64 chatId);
    void notifyPreview(qint64 timestamp, const QString &summary, const QString &body,
                       const qint64 chatId);

};

#endif // NOTIFICATIONMANAGER_HPP
