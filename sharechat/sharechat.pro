TEMPLATE = lib
QT += quick core dbus
CONFIG += qt plugin link_pkgconfig

PKGCONFIG += tdlibjson

LIBS += -L$$OUT_PWD/../tdlibjson_wrapper -ltdlibjson_wrapper

TARGET = $$qtLibraryTarget(sharechat)
target.path = /usr/share/depecher/qml/org/blacksailer/depecher/sharechat

qmldir.files = qmldir
qmldir.path = /usr/share/depecher/qml/org/blacksailer/depecher/sharechat

INSTALLS += target qmldir

INCLUDEPATH = $$PWD/../tdlibjson_wrapper

HEADERS += \
    ShareChatPlugin.hpp \
    ChatShareModel.hpp

SOURCES += \
    ShareChatPlugin.cpp \
    ChatShareModel.cpp

DISTFILES += \
    qmldir
