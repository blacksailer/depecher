#ifndef DBUSADAPTOR_HPP
#define DBUSADAPTOR_HPP

#include <QObject>
#include <QGuiApplication>
#include <QQuickView>
#include "dbus/DepecherAdaptor.hpp"
class PageAppStarter;
namespace tdlibQt {
class TdlibJsonWrapper;
}


class DBusAdaptor : public QObject
{
    Q_OBJECT
    QGuiApplication *app = nullptr;
    QQuickView *view = nullptr;
    PageAppStarter *pagesStarter;
    tdlibQt::TdlibJsonWrapper *tdlibJson;
public:
    explicit DBusAdaptor(QGuiApplication *parent = nullptr);
    ~DBusAdaptor();
    static bool isRegistered();
    static bool raiseApp();
public slots:
    void showApp(const QStringList &cmd);
    void openConversation(const qlonglong &chatId);
private slots:
    void onViewDestroyed();
    void onViewClosing(QQuickCloseEvent *v);
};

#endif // DBUSADAPTOR_HPP
