import QtQuick 2.0
import Sailfish.Silica 1.0
import tdlibQtEnums 1.0
import TelegramModels 1.0
import QtQml.Models 2.3
import org.nemomobile.notifications 1.0
Item {
    anchors.fill: parent
    id:root
    signal sendUrlItems(var items)
    property Item previewView
    property Page rootPage
    property bool _previewEnabled: false
    property alias set_id:stickerModel.set_id
    Component.onDestruction: rootPage.backNavigation = true
    Notification {
        id:notificationPreviewMode
        appName: "Depecher"
        previewBody: qsTr("Sticker preview mode")
    }
    StickerModel {
        id:stickerModel
        modelState: set_id ==="" ? StickerModel.SendState : StickerModel.PreviewState
    }

    states:[
        State {
            name: "general"
            PropertyChanges {
                target: root
                _previewEnabled:false
            }
            PropertyChanges {
                target: rootPage
                backNavigation:true
            }
            PropertyChanges {
                target: previewRect
                visible:false
            }

        },
        State {
            name: "preview"
            PropertyChanges {
                target: root
                _previewEnabled:true
            }
            PropertyChanges {
                target: rootPage
                backNavigation:false
            }
            PropertyChanges {
                target: previewRect
                visible:true
            }
            StateChangeScript {
                name: "showNotification"
                script: notificationPreviewMode.publish()
            }

        }
    ]
    state: "general"

    MouseArea {
        id:previewArea
        enabled: _previewEnabled
        focus: _previewEnabled
        width: parent.width
        height: parent.height - thumbnails.height
        anchors.bottom: parent.bottom
        property var component
        property var previewItem
        preventStealing: true
        onPositionChanged: previewThis(mouseX,mouseY)
        onEnabledChanged: {
            if(enabled)
            {
                component = Qt.createComponent(Qt.resolvedUrl("StickerPreviewComponent.qml"));
                previewItem = component.createObject(previewView, {"source": undefined});
            }
            else {
                if(component)
                    component.destroy()
                if(previewItem)
                    previewItem.destroy()
            }
        }

        function previewThis(x,y) {
            //delegateModel do not get item through index
            //Thats why getting sticker url via model slot
            var stikerGridIndex =  listView.indexAt(x,y+listView.contentY)
            var grid =listView.itemAt(x,y+listView.contentY).gridSticker
            if (grid) {
                var previousHeight = 0;
                var indexItem = 0
                var setIndex = stikerGridIndex
                //Get height of all gridView previously
                indexItem = grid.indexAt(x,mapToItem(grid,x,y).y)
                var stickerUrl = listView.model.model.getStickerUrl(setIndex,indexItem);
                if(stickerUrl)
                {
                    previewItem.source = "image://depecherDb/"+stickerUrl;
                    previewItem.emoji = listView.model.model.getStickerEmoji(setIndex,indexItem);
                }

            }
        }
        onReleased: root.state = "general"
    }
    Rectangle {
        id:previewRect
        visible: false
        parent: previewView
        anchors.fill: parent
        color:Qt.rgba(0,0,0,0.5)
    }

    Column {
        anchors.fill: parent
        SilicaListView {
            id:thumbnails
            width: parent.width
            height: Theme.itemSizeSmall
            orientation: Qt.Horizontal
            layoutDirection: Qt.LeftToRight
            currentIndex:listView.atYBeginning ? 0 : listView.indexAtTop
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
                        if(name == "Favorite")
                            return "image://theme/icon-m-favorite"
                        if(name == "Recent")
                            return "image://theme/icon-m-clock"

                        return "image://depecherDb/"+set_thumbnail+".webp"
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
            onContentYChanged: indexAtTop = indexAt(root.width/2,contentY + height/2)
            clip:true
            interactive: !_previewEnabled
            onDragStarted: {
                previewTimer.stop()
            }
            onFlickingChanged: {
                previewTimer.stop()
            }
            model:  DelegateModel {
                id:stickerSetModel
                model: stickerModel
                delegate: Item {
                    width: parent.width
                    height: columnStickers.height
                    property alias itemIndex: stickersGrid
                    property alias gridSticker: stickersGrid
                    property alias stickersCount: stickersGrid.count

                    Column {
                        id:columnStickers
                        width: parent.width
                        height: sectionHeader.height + stickersGrid.height
                        SectionHeader {
                            id:sectionHeader
                            text:title
                        }
                        DelegateModel {
                            id:stickers
                            model: stickerModel
                            rootIndex:listView.model.modelIndex(index)
                            delegate: Image {
                                width: stickersGrid.cellWidth
                                height: width
                                asynchronous: true
                                fillMode: Image.PreserveAspectFit
                                source: "image://depecherDb/" + sticker
                                MouseArea {
                                    anchors.fill: parent
                                    enabled: !_previewEnabled
                                    onPressed:{
                                        previewTimer.start()
                                    }
                                    onClicked:  {
                                        if( root.state === "general")
                                            sendUrlItems([{"id":sticker_file_id,"type":TdlibState.Sticker,"url":sticker}])

                                    }
                                    onExited: {
                                        if(previewTimer.running)
                                            previewTimer.stop()
                                    }
                                }
                            }
                        }
                        SilicaGridView {
                            id:stickersGrid
                            width: parent.width
                            interactive: !_previewEnabled
                            cellWidth: parent.width/5
                            cellHeight: cellWidth
                            height:Math.ceil(count / 5) * cellHeight
                            model:stickers
                        }
                    }
                }
            }


        }
        Timer {
            id:previewTimer
            interval: 800
            onTriggered:                 root.state = "preview"
        }

    }

}
