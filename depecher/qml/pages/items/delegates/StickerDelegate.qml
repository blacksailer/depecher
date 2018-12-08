import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import QtMultimedia 5.6
import Nemo.Configuration 1.0
import Nemo.DBus 2.0
import QtQml.Models 2.3
import depecherUtils 1.0

Column {
    width: stickerImage.width//messageListItem.width/4*3
    property int maxWidth: messageListItem.width-Theme.itemSizeExtraSmall - Theme.paddingMedium - 2*Theme.horizontalPageMargin

        Image {
            id:stickerImage
            asynchronous: true
            width: Math.min(implicitWidth,parent.maxWidth)
            height: width
            fillMode: Image.PreserveAspectFit
            source: content ? "image://depecherDb/" + content : ""
            MouseArea {
                anchors.fill: parent
                onClicked: pageStack.push(Qt.resolvedUrl("../../components/PreviewStickerSetDialog.qml"),{set_id:sticker_set_id})
            }
        }
    }

