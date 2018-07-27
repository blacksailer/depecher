#ifndef DBUSADAPTOR_HPP
#define DBUSADAPTOR_HPP

#include <QObject>
#include <QGuiApplication>
#include <QQuickView>
#include "dbus/DepecherAdaptor.hpp"
class PageAppStarter;
class DBusAdaptor : public QObject
{
    Q_OBJECT
    QGuiApplication *app = nullptr;
    QQuickView *view = nullptr;
    PageAppStarter *pagesStarter;

public:
    explicit DBusAdaptor(QGuiApplication *parent = nullptr);
    ~DBusAdaptor();
    static bool isRegistered();
    static bool raiseApp();
signals:

public slots:
    void showApp(const QStringList &cmd);
    void openConversation(const qlonglong &chatId);
private slots:
    void onViewDestroyed();
    void onViewClosing(QQuickCloseEvent *v);
};

#endif // DBUSADAPTOR_HPP
