#include "NotificationManager.hpp"
#include <QDebug>
#include <QGuiApplication>
NotificationManager::NotificationManager(QObject *parent) : QObject(parent)
{

}

NotificationManager *NotificationManager::instance()
{
    static NotificationManager  instance;
    return &instance;

}

void NotificationManager::removeNotification(qint64 chatId)
{
    if (chatIdsPublished.contains(chatId)) {
        chatIdsPublished[chatId]->close();
        chatIdsPublished.remove(chatId);
    }
}

void NotificationManager::notifySummary(qint64 timestamp, const QString &summary,
                                        const QString &body, qint64 chatId)
{
    if (currentViewableChatId != chatId || qApp->applicationState() != Qt::ApplicationActive) {
        QSharedPointer<Notification> notification = QSharedPointer<Notification>(new Notification);

        notification->setCategory("x-nemo.messaging.sms");
        notification->setExpireTimeout(m_ExpireTimeout);
        notification->setItemCount(1);
        if (chatIdsPublished.contains(chatId)) {
            notification->setItemCount(chatIdsPublished[chatId]->itemCount() + 1);
            notification->setReplacesId(chatIdsPublished[chatId]->replacesId());
        }
        notification->setTimestamp(QDateTime::fromMSecsSinceEpoch(timestamp *
                                                                  1000 /* timestamp have secs , not msecs*/));
        notification->setSummary(summary);
        notification->setBody(body);
        notification->publish();
        connect(notification.data(), &Notification::closed, [this]() {
            auto ptr = QSharedPointer<Notification>((Notification *)sender());
            chatIdsPublished.remove(chatIdsPublished.key(ptr)) ;
        });
        chatIdsPublished[chatId] = notification;
    }
}

void NotificationManager::notifyPreview(qint64 timestamp, const QString &summary,
                                        const QString &body, const qint64 chatId)
{
    if (currentViewableChatId != chatId || qApp->applicationState() != Qt::ApplicationActive) {

        QSharedPointer<Notification> notification = QSharedPointer<Notification>(new Notification);
        notification->setCategory("x-nemo.messaging.sms");
        notification->setExpireTimeout(m_ExpireTimeout);
        notification->setItemCount(1);
        if (chatIdsPublished.contains(chatId)) {
            notification->setItemCount(chatIdsPublished[chatId]->itemCount() + 1);
            notification->setReplacesId(chatIdsPublished[chatId]->replacesId());
        }
        notification->setTimestamp(QDateTime::fromMSecsSinceEpoch(timestamp *
                                                                  1000 /* timestamp have secs , not msecs*/));
        notification->setPreviewSummary(summary);
        notification->setPreviewBody(body);
        notification->publish();
        connect(notification.data(), &Notification::closed, [this]() {
            auto ptr = QSharedPointer<Notification>((Notification *)sender());
            chatIdsPublished.remove(chatIdsPublished.key(ptr)) ;
        });
        chatIdsPublished[chatId] = notification;
    }
}
