import QtQuick 2.0
import Sailfish.Silica 1.0
import tdlibQtEnums 1.0
import TelegramModels 1.0
import QtQml.Models 2.3

SilicaListView {
    id:listView
    anchors.fill: parent
    header:PageHeader {
        title: qsTr("Stickers")
    }
    StickerModel {
            id:stickerModel
            modelState: StickerModel.SendState
        }
    model:  DelegateModel {
        model: stickerModel
        delegate: Column {
            width: parent.width
            SectionHeader {
                text:title
            }

            DelegateModel {
                id:stickers
        model: stickerModel
        rootIndex:listView.model.modelIndex(index)
        delegate: Image {
            width: parent.width/3
            height: width
            source: "image://depecherDb/" + sticker
        }
            }
            SilicaGridView {
                width: parent.width
                cellWidth: parent.width/3
                cellHeight: cellWidth
                height:Math.ceil(count / 3) * cellHeight
                model:stickers
            }
    }
    }

//    section {
//        property: "title"

//        delegate: SectionHeader {
//            text: title
//            height: Theme.itemSizeExtraSmall
//        }
//    }


}
