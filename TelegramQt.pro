TEMPLATE = subdirs
SUBDIRS = lib \
webp \
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
    depecher/qml/pages/items/SendStickerComponent.qml \
    depecher/qml/pages/items/AttachSticker.qml

