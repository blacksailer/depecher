APPID = $$fromfile(api_secret.pri,APPID)#To build you have to create file api_secret.pri with app_id, or replace with your app_id
APP_HASH = $$fromfile(api_secret.pri,APP_HASH)#To build you have to create file api_secret.pri app_hash, or replace with your app_hash


VERSION =  0.7.3
DEFINES += APP_VERSION=\"\\\"$${VERSION}\\\"\"

TEMPLATE = lib
TARGET = tdlibjson_wrapper
CONFIG += staticlib
QT += dbus quick

CONFIG += c++11 link_pkgconfig
PKGCONFIG +=  tdlibjson
PKGCONFIG += mlite5

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
    tdlibQt/infoProviders/BasicGroupInfoProvider.hpp \
    tdlibQt/infoProviders/ChannelInfoProvider.hpp \
    tdlibQt/infoProviders/InfoProvider.hpp \
    tdlibQt/infoProviders/UserInfoProvider.hpp \
    tdlibQt/infoProviders/UsernameResolver.hpp \
    tdlibQt/items/TdApi.hpp \
    tdlibQt/items/TdLibDependencies.hpp \
    tdlibQt/include/TdlibNamespace.hpp \
    tdlibQt/models/ChatMembersModel.hpp \
    tdlibQt/models/ChatsModel.hpp \
    tdlibQt/TelegramProfileProvider.hpp \
    tdlibQt/models/FilterChatMembersModel.hpp \
    tdlibQt/models/MessagingModel.hpp \
    tdlibQt/FileWriter.hpp \
    tdlibQt/ListenScheduler.hpp \
    tdlibQt/include/AppApiInfo.hpp \
    tdlibQt/include/AuthenticationHandler.hpp \
    tdlibQt/items/ProxyDAO.hpp \
    tdlibQt/items/AboutMeDAO.hpp \
    tdlibQt/models/SearchChatMessagesModel.hpp \
    tdlibQt/models/singletons/UsersModel.hpp \
    tdlibQt/models/StickerModel.hpp \
    tdlibQt/NotificationManager.hpp \
    tdlibQt/models/SearchChatsModel.hpp \
    tdlibQt/models/ContactsModel.hpp \
    tdlibQt/models/FilterContactsModel.hpp

SOURCES += \
    tdlibQt/TdlibJsonWrapper.cpp \
    tdlibQt/ListenObject.cpp \
    tdlibQt/ParseObject.cpp \
    tdlibQt/infoProviders/BasicGroupInfoProvider.cpp \
    tdlibQt/infoProviders/ChannelInfoProvider.cpp \
    tdlibQt/infoProviders/InfoProvider.cpp \
    tdlibQt/infoProviders/UserInfoProvider.cpp \
    tdlibQt/infoProviders/UsernameResolver.cpp \
    tdlibQt/items/TdApi.cpp \
    tdlibQt/models/ChatMembersModel.cpp \
    tdlibQt/models/ChatsModel.cpp \
    tdlibQt/TelegramProfileProvider.cpp \
    tdlibQt/models/FilterChatMembersModel.cpp \
    tdlibQt/models/MessagingModel.cpp \
    tdlibQt/FileWriter.cpp \
    tdlibQt/ListenScheduler.cpp \
    tdlibQt/include/AuthenticationHandler.cpp \
    tdlibQt/items/ProxyDAO.cpp \
    tdlibQt/items/AboutMeDAO.cpp \
    tdlibQt/models/SearchChatMessagesModel.cpp \
    tdlibQt/models/singletons/UsersModel.cpp \
    tdlibQt/models/StickerModel.cpp \
    tdlibQt/NotificationManager.cpp \
    tdlibQt/models/SearchChatsModel.cpp \
    tdlibQt/models/ContactsModel.cpp \
    tdlibQt/models/FilterContactsModel.cpp

info_file.input = $$PWD/tdlibQt/include/AppApiInfo.hpp.in
info_file.output = $$PWD/tdlibQt/include/AppApiInfo.hpp

QMAKE_SUBSTITUTES += info_file

OTHER_FILES += \
    tdlibQt/include/AppApiInfo.hpp.in

DISTFILES += \
    api_secret.pri \
    api_secret.pri
