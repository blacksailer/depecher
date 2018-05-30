import QtQuick 2.0
import Sailfish.Silica 1.0
import tdlibQtEnums 1.0
import TelegramModels 1.0
import QtQml.Models 2.3

Column {
    signal sendUrlItems(var items)
    anchors.fill: parent
    SilicaListView {
        id:thumbnails
       width: parent.width
       height: Theme.itemSizeSmall
       orientation: Qt.Horizontal
       layoutDirection: Qt.LeftToRight
       currentIndex: listView.indexAtTop
       model: stickerModel
       spacing: Theme.paddingSmall
       delegate: BackgroundItem {
           width: height
           height: Theme.itemSizeSmall
           highlighted: ListView.isCurrentItem
           Image {
           width: height
           height: Theme.itemSizeSmall - 2* Theme.paddingSmall
           anchors.centerIn: parent
           fillMode: Image.PreserveAspectFit
           source: {
            if(title == qsTr("Favorite"))
                return "image://theme/icon-s-favorite"
            if(title == qsTr("Recent"))
                return "image://theme/icon-s-duration"

               return "image://depecherDb/"+set_thumbnail
           }
           }
           onClicked: listView.currentIndex = index
       }
   }

    SilicaListView {
        id:listView
        width: parent.width
        height: parent.height - thumbnails.height
        property int indexAtTop: 0
//        curre: ListView.OverlayHeader
        onCurrentIndexChanged: console.log(currentIndex)
        onContentYChanged: {
            console.log(contentY)
            indexAtTop = indexAt(Screen.width/2,contentY + height/2)
        }
        clip:true

        StickerModel {
            id:stickerModel
            modelState: StickerModel.SendState
        }
        model:  DelegateModel {
            id:stickerSetModel
            model: stickerModel
            delegate: Column {
                width: parent.width
                SectionHeader {
                    id:sectionHeader
                    text:title
                }
                DelegateModel {
                    id:stickers
                    model: stickerModel
                    rootIndex:listView.model.modelIndex(index)
                    delegate: Image {
                        width: stickersList.cellWidth
                        height: width
                        asynchronous: true
                        fillMode: Image.PreserveAspectFit
                        source: "image://depecherDb/" + sticker
                        MouseArea {
                            anchors.fill: parent
                            onClicked: sendUrlItems([{"id":sticker_file_id,"type":TdlibState.Sticker,"url":sticker}])
                        }
                    }
                }
                SilicaGridView {
                    id:stickersList
                    width: parent.width
                    cellWidth: parent.width/3
                    cellHeight: cellWidth
                    height:Math.ceil(count / 3) * cellHeight
                    model:stickers
                }
            }
        }
    }

}

