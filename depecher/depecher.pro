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

QT += sql dbus multimedia

CONFIG += sailfishapp
CONFIG += c++11
CONFIG += link_pkgconfig
PKGCONFIG += nemonotifications-qt5 tdlibjson
PKGCONFIG += sailfishapp

LIBS += -L$$OUT_PWD/../tdlibjson_wrapper -ltdlibjson_wrapper

# WebP Plugin
webp.files = $$OUT_PWD/../webp-plugin/plugins/imageformats/*.so
webp.path  = /usr/share/$$TARGET/lib/imageformats

dbus.files = $$PWD/dbus/org.blacksailer.depecher.service
dbus.path = /usr/share/dbus-1/services

dbus_interface.files= $$PWD/dbus/org.blacksailer.depecher.xml
dbus_interface.path= /usr/share/dbus-1/interfaces

systemd.files = $$PWD/systemd/depecher.service
systemd.path = /usr/lib/systemd/user

INSTALLS += webp dbus dbus_interface systemd

DEPENDPATH += $$OUT_PWD/../tdlibjson_wrapper
INCLUDEPATH = $$PWD/../tdlibjson_wrapper

notificationcategories.files=$$PWD/notificationcategories/*.conf
notificationcategories.path=/usr/share/lipstick/notificationcategories

events.files=$$PWD/events/*.ini
events.path=/usr/share/ngfd/events.d

INSTALLS += notificationcategories events

# Settings
settings_json.files = $$PWD/qml/settings/$${TARGET}.json
settings_json.path = /usr/share/jolla-settings/entries/
INSTALLS += settings_json

settings_qml.files = $$PWD/qml/settings/*.qml
settings_qml.path = /usr/share/$${TARGET}/settings/
INSTALLS += settings_qml

i18n.path = /usr/share/depecher/translations
i18n.files =     translations/*.qm

INSTALLS += i18n

CONFIG (debug, debug|release) {
        OBJECTS_DIR = build/debug
} else {
        OBJECTS_DIR = build/release
}
MOC_DIR = build/mocs

SOURCES += \
    src/main.cpp \
    src/FileWorker.cpp \
    ModelTest.cpp \
    src/DBusAdaptor.cpp \
    dbus/DepecherAdaptor.cpp


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

# automatic generation of the translation .qm files from .ts files
system(lrelease $$PWD/translations/*.ts)
TRANSLATIONS += translations/*.ts

RESOURCES += \
    resource.qrc

DISTFILES += \
    qml/js/countries.js \
    depecher.desktop \
    rpm/depecher.yaml \
    rpm/depecher.spec \
    rpm/depecher.changes.in \
    ../README.md \
    events/depecher_im_fg.ini \
    events/depecher_im_exists.ini \
    events/depecher_im.ini \
    notificationcategories/x-depecher.im.conf \
    notificationcategories/x-depecher.im.fg.conf \
    translations/depecher-es.ts \
    systemd/depecher.service \
    dbus/org.blacksailer.depecher.service \
    dbus/org.blacksailer.depecher.xml \
    dbus/application.xml

HEADERS += \
    src/FileWorker.hpp \
    ModelTest.hpp \
    src/DBusAdaptor.hpp \
    dbus/DepecherAdaptor.hpp
