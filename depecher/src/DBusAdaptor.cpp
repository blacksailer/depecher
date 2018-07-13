#include "DBusAdaptor.hpp"
#include "FileWorker.hpp"

#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/models/StickerModel.hpp"
#include "tdlibQt/models/ChatsModel.hpp"
#include "tdlibQt/models/MessagingModel.hpp"
#include "tdlibQt/models/StickerModel.hpp"
#include "tdlibQt/TelegramProfileProvider.hpp"
#include "tdlibQt/include/AuthenticationHandler.hpp"
#include "tdlibQt/items/ProxyDAO.hpp"
#include "tdlibQt/items/AboutMeDAO.hpp"

#include <QDebug>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>
#include "sailfishapp.h"

DBusAdaptor::DBusAdaptor(QGuiApplication *parent) : app(parent)
{
//    connect(app, &QGuiApplication::destroyed, this, &DBusAdaptor::stopDaemon);

    new DepecherAdaptor(this);
    QDBusConnection dbus = QDBusConnection::sessionBus();

    bool ready = dbus.registerService("org.blacksailer.depecher");
    qDebug() << "Register service" << ready;
    qDebug() << "Register object" << dbus.registerObject("/org/blacksailer/depecher", this); //object path

    if (!ready) {
        qWarning() << "Service already registered, exiting...";
        app->quit();
    }
}
DBusAdaptor::~DBusAdaptor()
{
    QDBusConnection dbus = QDBusConnection::sessionBus();

    dbus.unregisterObject("/org/blacksailer/depecher"); //object path
    bool ready = dbus.unregisterService("org.blacksailer.depecher");
    qDebug() << "Unregister service" << ready; //object path

}

void DBusAdaptor::ShowApp(const QStringList &cmd)
{
    qDebug() << "Parameters" << cmd;
    if (!view) {
        qDebug() << "Construct view";
        view = SailfishApp::createView();

        connect(view, &QQuickView::destroyed, this, &DBusAdaptor::onViewDestroyed);
        connect(view, SIGNAL(closing(QQuickCloseEvent *)), this,  SLOT(onViewClosing(QQuickCloseEvent *)));

        qmlRegisterUncreatableType<tdlibQt::Enums>("tdlibQtEnums", 1, 0, "TdlibState",
                "Error class uncreatable");
        qmlRegisterType<FileWorker>("depecherUtils", 1, 0, "FileWorker");
        qmlRegisterType<tdlibQt::AboutMeDAO>("TelegramItems", 1, 0, "AboutMeDAO");
        qmlRegisterType<tdlibQt::ProxyDAO>("TelegramItems", 1, 0, "ProxyDAO");
        qmlRegisterType<tdlibQt::MessagingModel>("TelegramModels", 1, 0, "MessagingModel");
        qmlRegisterType<tdlibQt::ChatsModel>("TelegramModels", 1, 0, "ChatsModel");
        qmlRegisterType<tdlibQt::StickerModel>("TelegramModels", 1, 0, "StickerModel");

        qmlRegisterType<tdlibQt::AuthenticationHandler>("TelegramAuthentication", 1, 0,
                "TelegramAuthenticationHandler");
        view->setTitle("Depecher");
        view->rootContext()->setContextProperty("c_telegramWrapper", tdlibQt::TdlibJsonWrapper::instance());

        view->engine()->addImageProvider(QLatin1String("depecherDb"), new tdlibQt::TelegramProfileProvider);
        view->setSource(QUrl("qrc:///qml/app.qml"));
        view->show();
    } else if (view->windowState() == Qt::WindowNoState) {
        view->create();
        view->showFullScreen();
    } else {
        view->raise();
        view->requestActivate();
    }
}

void DBusAdaptor::openConversation(const qlonglong &chatId)
{

}

void DBusAdaptor::onViewDestroyed()
{
    view = nullptr;
}

void DBusAdaptor::onViewClosing(QQuickCloseEvent *v)
{
    Q_UNUSED(v)
    view->destroy();
    view->deleteLater();
}
