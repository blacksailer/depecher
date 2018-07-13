#ifndef DBUSADAPTOR_HPP
#define DBUSADAPTOR_HPP

#include <QObject>
#include <QGuiApplication>
#include <QQuickView>
#include "dbus/DepecherAdaptor.hpp"
class DBusAdaptor : public QObject
{
    Q_OBJECT
    QGuiApplication *app = nullptr;
    QQuickView *view = nullptr;

public:
    explicit DBusAdaptor(QGuiApplication *parent = nullptr);
    ~DBusAdaptor();

signals:

public slots:
    void ShowApp(const QStringList &cmd);
    void openConversation(const qlonglong &chatId);
private slots:
    void onViewDestroyed();
    void onViewClosing(QQuickCloseEvent *v);
};

#endif // DBUSADAPTOR_HPP
