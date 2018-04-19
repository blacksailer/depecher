# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = depecher

QT += sql

CONFIG += sailfishapp
CONFIG += c++11
CONFIG += link_pkgconfig
PKGCONFIG += nemonotifications-qt5 tdlibjson
PKGCONFIG += sailfishapp

LIBS += -L$$OUT_PWD/../tdlibjson_wrapper -ltdlibjson_wrapper

# WebP Plugin
webp.files = $$OUT_PWD/../webp-plugin/plugins/imageformats/*.so
webp.path  = /usr/share/$$TARGET/lib/imageformats
INSTALLS += webp

DEPENDPATH += $$OUT_PWD/../tdlibjson_wrapper
INCLUDEPATH = $$PWD/../tdlibjson_wrapper

CONFIG (debug, debug|release) {
        OBJECTS_DIR = build/debug
} else {
        OBJECTS_DIR = build/release
}
MOC_DIR = build/mocs

SOURCES += \
    src/main.cpp \
    src/FileWorker.cpp


OTHER_FILES += qml/app.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    translations/*.ts

SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/depecher-de.ts

RESOURCES += \
    resource.qrc

DISTFILES += \
    qml/js/countries.js \
    depecher.desktop \
    rpm/depecher.yaml \
    rpm/depecher.spec \
    rpm/depecher.changes.in \
    ../README.md

HEADERS += \
    src/FileWorker.hpp
