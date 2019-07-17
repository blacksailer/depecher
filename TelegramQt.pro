TEMPLATE = subdirs
SUBDIRS =  webp \
            lib \
            shareui \
            sharechat \
            app
  # where to find the sub projects - give the folders
lib.subdir  = tdlibjson_wrapper
app.subdir  = depecher
webp.file = webp-plugin/webp.pro
lib.makefile = MyMakefile
  # what subproject depends on others
app.depends = lib

# build the project sequentially as listed in SUBDIRS !
CONFIG += ordered

DISTFILES += \
    depecher/qml/DepecherTheme.qml \
    depecher/qml/pages/components/settings/ProxyDialog.qml \
    depecher/qml/Thm.qml \
    depecher/qml/ThemePlugin/qmldir \
    depecher/qml/pages/SelectChatDialog.qml \
    depecher/qml/pages/VideoPage.qml \
    depecher/qml/pages/components/settings/ProxyPage.qml \
    depecher/qml/pages/items/VoiceButton.qml \
    depecher/qml/pages/items/delegates/utils.js \
    depecher/qml/ShareUI.qml \
    ../../DepecherPluginTest/qml/pages/components/ChatItemShare.qml

RESOURCES += \
    depecher/qml/pages/components/settings/proxypage.qrc

