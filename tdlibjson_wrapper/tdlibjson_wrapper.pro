APPID = $$fromfile(api_secret.pri,APPID)#To build you have to create file api_secret.pri with app_id, or replace with your app_id
APP_HASH = $$fromfile(api_secret.pri,APP_HASH)#To build you have to create file api_secret.pri app_hash, or replace with your app_hash

TEMPLATE = lib
TARGET = tdlibjson_wrapper
CONFIG += staticlib
QT += dbus quick

CONFIG += c++11
CONFIG += link_pkgconfig
PKGCONFIG +=  nemonotifications-qt5 tdlibjson
CONFIG (debug, debug|release) {
        OBJECTS_DIR = build/debug
} else {
        OBJECTS_DIR = build/release
}
MOC_DIR = build/mocs

HEADERS += \
    tdlibQt/TdlibJsonWrapper.hpp \
    tdlibQt/ListenObject.hpp \
    tdlibQt/ParseObject.hpp \
    tdlibQt/items/TdApi.hpp \
    tdlibQt/items/TdLibDependencies.hpp \
    tdlibQt/include/TdlibNamespace.hpp \
    tdlibQt/models/ChatsModel.hpp \
    tdlibQt/TelegramProfileProvider.hpp \
    tdlibQt/models/MessagingModel.hpp \
    tdlibQt/FileWriter.hpp \
    tdlibQt/NotificationManager.hpp \
    tdlibQt/ListenScheduler.hpp \
    tdlibQt/include/AppApiInfo.hpp \
    tdlibQt/include/AuthenticationHandler.hpp \
    tdlibQt/items/ProxyDAO.hpp \
    tdlibQt/items/AboutMeDAO.hpp \
    tdlibQt/models/singletons/UsersModel.hpp \
    tdlibQt/models/singletons/FileManager.hpp \
    tdlibQt/models/StickerModel.hpp

SOURCES += \
    tdlibQt/TdlibJsonWrapper.cpp \
    tdlibQt/ListenObject.cpp \
    tdlibQt/ParseObject.cpp \
    tdlibQt/items/TdApi.cpp \
    tdlibQt/models/ChatsModel.cpp \
    tdlibQt/TelegramProfileProvider.cpp \
    tdlibQt/models/MessagingModel.cpp \
    tdlibQt/FileWriter.cpp \
    tdlibQt/NotificationManager.cpp \
    tdlibQt/ListenScheduler.cpp \
    tdlibQt/include/AuthenticationHandler.cpp \
    tdlibQt/items/ProxyDAO.cpp \
    tdlibQt/items/AboutMeDAO.cpp \
    tdlibQt/models/singletons/UsersModel.cpp \
    tdlibQt/models/singletons/FileManager.cpp \
    tdlibQt/models/StickerModel.cpp

info_file.input = $$PWD/tdlibQt/include/AppApiInfo.hpp.in
info_file.output = $$PWD/tdlibQt/include/AppApiInfo.hpp

QMAKE_SUBSTITUTES += info_file

OTHER_FILES += \
    tdlibQt/include/AppApiInfo.hpp.in

DISTFILES += \
    api_secret.pri \
    api_secret.pri
