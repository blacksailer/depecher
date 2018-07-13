#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QGuiApplication>


#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/NotificationManager.hpp"
#include "tdlibQt/models/singletons/UsersModel.hpp"
#include "DBusAdaptor.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication *app = SailfishApp::application(argc, argv);
    app->addLibraryPath(QString("%1/../share/%2/lib").arg(qApp->applicationDirPath(),
                        qApp->applicationName()));
    app->setQuitOnLastWindowClosed(false);


    QTranslator translator;

    QString locale = QLocale::system().name();
    //locale="de"; // for testing purposes only
    if (!translator.load("depecher-" + locale, SailfishApp::pathTo("translations").toLocalFile())) {
        qDebug() << "Couldn't load translation for locale " + locale + " from " +
                 SailfishApp::pathTo("translations").toLocalFile();
    }
    app->installTranslator(&translator);

    auto tdlib = tdlibQt::TdlibJsonWrapper::instance();

    //Need to create at first launch. Bad design maybe, should change
    auto NotificationManager = tdlibQt::NotificationManager::instance();
    auto usersmodel = tdlibQt::UsersModel::instance();
    tdlib->startListen();
    tdlib->setEncryptionKey();
    tdlib->getInstalledStickerSets();
    QScopedPointer<DBusAdaptor> dbusWatcher(new DBusAdaptor(app));


    return app->exec();
}
