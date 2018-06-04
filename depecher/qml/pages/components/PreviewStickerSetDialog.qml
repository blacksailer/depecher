import QtQuick 2.0
import Sailfish.Silica 1.0
import tdlibQtEnums 1.0
import TelegramModels 1.0
import QtQml.Models 2.3
import org.nemomobile.notifications 1.0
import "../items"
Dialog {
    id:rootPage
    property alias set_id: stickerModel.set_id
    property bool _previewEnabled: false
    property bool _setIsInstalled: false
    canAccept: !_previewEnabled
    states:[
        State {
            name: "general"
            PropertyChanges {
                target: rootPage
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
                target: rootPage
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
    onAccepted: {
        if(_setIsInstalled)
            stickerModel.changeStickerSet(set_id,false)
        else
            stickerModel.changeStickerSet(set_id,true)
    }
    Notification {
        id:notificationPreviewMode
        appName: "Depecher"
        previewBody: qsTr("Sticker preview mode")
    }
    StickerModel {
        id:stickerModel
        modelState: set_id ==="" ? StickerModel.UknownState : StickerModel.PreviewState
    }


    MouseArea {
        id:previewArea
        enabled: _previewEnabled
        focus: _previewEnabled
        width: parent.width
        height: parent.height - header.height
        anchors.bottom: parent.bottom
        property var component
        property var previewItem
        preventStealing: true
        onPositionChanged: previewThis(mouseX,mouseY)
        onEnabledChanged: {
            if(enabled)
            {
                component = Qt.createComponent(Qt.resolvedUrl("../items/StickerPreviewComponent.qml"));
                previewItem = component.createObject(rootPage, {"source": undefined});
                previewItem.anchors.centerIn = rootPage
                previewItem.z = listView.z + 2
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
        onReleased: rootPage.state = "general"
    }
    Rectangle {
        id:previewRect
        visible: false
        parent: rootPage
        z:listView.z + 1
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position:  1.0; color: "transparent" }
            GradientStop { position:  0.0; color: Theme.highlightDimmerColor }
        }
    }
    Column {
        width:parent.width


        DialogHeader {
            id:header
            acceptText: rootPage._setIsInstalled ? qsTr("Remove %1 stickers").arg(listView.contentItem.children[0].gridSticker.count) :qsTr("Add %1 stickers").arg(listView.contentItem.children[0].gridSticker.count)
            cancelText: qsTr("Back")
        }
        SilicaListView {
            id:listView
            width: parent.width
            height: rootPage.height - header.height
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
                                Connections {
                                    target: stickerModel
                                    onRefreshSticker:{
                                        stickersGrid.forceLayout()
                                    }
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    enabled: !_previewEnabled
                                    onPressed:{
                                        previewTimer.start()
                                    }
                                    onClicked:  {
                                        if( rootPage.state === "general")
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
                    Component.onCompleted:{
                        rootPage._setIsInstalled = is_installed
                    }
                }
            }


        }
    }

    Timer {
        id:previewTimer
        interval: 800
        onTriggered:                 rootPage.state = "preview"
    }
}
