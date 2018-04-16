#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QQmlContext>
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>

#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/models/ChatsModel.hpp"
#include "tdlibQt/models/MessagingModel.hpp"
#include "tdlibQt/TelegramProfileProvider.hpp"
#include "tdlibQt/include/AuthenticationHandler.hpp"
#include "tdlibQt/items/ProxyDAO.hpp"
#include "tdlibQt/items/AboutMeDAO.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication *app = SailfishApp::application(argc, argv);
    app->addLibraryPath(QString("%1/../share/%2/lib").arg(qApp->applicationDirPath(),
                                                          qApp->applicationName()));

    auto view = SailfishApp::createView();
    auto tdlib = tdlibQt::TdlibJsonWrapper::instance();
    tdlib->startListen();
    tdlib->setEncryptionKey();
    qmlRegisterUncreatableType<tdlibQt::Enums>("tdlibQtEnums", 1, 0, "TdlibState",
                                               "Error class uncreatable");
    qmlRegisterType<tdlibQt::AboutMeDAO>("TelegramItems", 1, 0, "AboutMeDAO");
    qmlRegisterType<tdlibQt::ProxyDAO>("TelegramItems", 1, 0, "ProxyDAO");
    qmlRegisterType<tdlibQt::MessagingModel>("TelegramModels", 1, 0, "MessagingModel");
    qmlRegisterType<tdlibQt::ChatsModel>("TelegramModels", 1, 0, "ChatsModel");
    qmlRegisterType<tdlibQt::AuthenticationHandler>("TelegramAuthentication", 1, 0,
                                                    "TelegramAuthenticationHandler");
    view->setTitle("Depecher");
    view->rootContext()->setContextProperty("c_telegramWrapper", tdlib);
    view->engine()->addImageProvider(QLatin1String("depecherDb"), new tdlibQt::TelegramProfileProvider);
    view->setSource(QUrl("qrc:///qml/app.qml"));
    view->show();

    return app->exec();
}
