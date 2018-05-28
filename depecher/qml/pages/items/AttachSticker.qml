import QtQuick 2.0
import Sailfish.Silica 1.0
import tdlibQtEnums 1.0
import TelegramModels 1.0

SilicaGridView {
    id:listView
    anchors.fill: parent
    header:PageHeader {
        title: qsTr("Stickers")
    }

    model: StickerModel {
        id:stickerModel
        modelState: StickerModel.SendState
    }
    cellWidth:width/3
    cellHeight:cellWidth
//    section {
//        property: "title"

//        delegate: SectionHeader {
//            text: title
//            height: Theme.itemSizeExtraSmall
//        }
//    }

    delegate: Image {
        width: parent.width/3
        height:width
        source: "image://depecherDb/" + sticker
    }

}
