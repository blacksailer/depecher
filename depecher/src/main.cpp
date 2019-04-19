#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QGuiApplication>
#include <MGConfItem>

#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/NotificationManager.hpp"
#include "tdlibQt/models/singletons/UsersModel.hpp"
#include "DBusAdaptor.hpp"
#include "src/fileGeneratedHandlers/FileGeneratedHandler.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication *app = SailfishApp::application(argc, argv);
    MGConfItem quitOnCloseUi("/apps/depecher/tdlib/quit_on_close_ui");

    if (DBusAdaptor::isRegistered()) {
        if (DBusAdaptor::raiseApp()) {
            return 0;
        } else {
            return 1;
        }
    }


    QScopedPointer<DBusAdaptor> dbusWatcher(new DBusAdaptor(app));

    app->addLibraryPath(QString("%1/../share/%2/lib").arg(qApp->applicationDirPath(),
                        qApp->applicationName()));
    app->setApplicationVersion(APP_VERSION);


    QTranslator translator;

    QString locale = QLocale::system().name();
    //locale="de"; // for testing purposes only
    if (!translator.load("depecher-" + locale, SailfishApp::pathTo("translations").toLocalFile())) {
        qDebug() << "Couldn't load translation for locale " + locale + " from " +
                 SailfishApp::pathTo("translations").toLocalFile();
    }
    app->installTranslator(&translator);


    //Need to create at first launch. Bad design maybe, should change

    auto tdlib = tdlibQt::TdlibJsonWrapper::instance();
    auto NotificationManager = tdlibQt::NotificationManager::instance();
    auto usersmodel = tdlibQt::UsersModel::instance();
    tdlib->startListen();
    //used in authenticationhandler too.
    tdlib->setEncryptionKey();
    FileGeneratedHandler generationHandler(app);

    if (quitOnCloseUi.value(false).toBool()) {
        app->setQuitOnLastWindowClosed(true);
        DBusAdaptor::raiseApp();
    } else {
        app->setQuitOnLastWindowClosed(false);
        QObject::connect(app, &QGuiApplication::aboutToQuit,
                         NotificationManager, &tdlibQt::NotificationManager::removeAll);
    }

    return app->exec();
}
