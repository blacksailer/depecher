import QtQuick 2.0
import Sailfish.Silica 1.0 
import QtDocGallery 5.0
import Sailfish.Pickers 1.0
import org.nemomobile.thumbnailer 1.0

import tdlibQtEnums 1.0
Item {
    id: thumbnailWrapper
    anchors.fill: parent
    property var selectedItems: []
    property int countItems: selectedItems.length
    property alias docType: galleryModel.rootType
    property string attachmentId: ""
    property string attachmentPreview: ""
    signal sendUrlItems(var items)
    signal menuTypeChanged (var type)

    // if there are many options, they will open
    // in a separate dialog
    ComboBox {
        id: files
        width: parent.width
        label: qsTr("Type")
        menu: ContextMenu {
            MenuItem { text: qsTr("Photo") } //Порядок жестко определен. В родителе перечесление
               MenuItem { text: qsTr("Document") }
        }
        onCurrentIndexChanged:
        {
            menuTypeChanged(currentIndex)
        }

    }
    DocumentGalleryModel {
        id: galleryModel
        rootType: DocumentGallery.Image //DocumentGallery.File || DocumentGallery.Audio
        properties: [ "url", "title", "dateTaken" ]
        autoUpdate: true
        sortProperties: ["-dateTaken"]
    }

    ListModel {
        id: fileModel

        ListElement {
            iconPath: "image://theme/icon-m-home"
            title: qsTr("Home")
            subtitle: qsTr("Go to Home folder")
        }

        ListElement {
            iconPath: "image://theme/icon-m-file-folder"
            title: qsTr("Documents")
            subtitle: qsTr("Send a document")
        }
    }

    Component {
        id: filesViewComponent

        SilicaListView {
            model: fileModel
            anchors.fill: parent
            spacing: Theme.paddingSmall
            currentIndex: -1 // otherwise currentItem will steal focus
            delegate: fileComponent
            clip: true
            VerticalScrollDecorator {
                flickable: parent
            }
        }
    }

    Loader {
        width: parent.width
        anchors.top: files.bottom
        anchors.bottom: attachButton.top
        anchors.bottomMargin: Theme.paddingMedium
        sourceComponent: files.currentIndex === 1 ? filesViewComponent : photosViewComponent
    }

    Component {
        id: photosViewComponent

        SilicaGridView{
            id: thumbnailPhotos
            property var icons: ["image://theme/icon-l-image", "image://theme/icon-l-diagnostic", "image://theme/icon-l-document"]
            anchors.fill: parent
            clip: true
            //anchors.fill: parent
            property real cellSize: Math.floor(width / columnCount)
            property int columnCount: Math.floor(width / Theme.itemSizeHuge)
            cellWidth: cellSize
            cellHeight: cellSize
            model: galleryModel
            delegate:         Image {
                asynchronous: true
                // From org.nemomobile.thumbnailer
                source:   "image://nemoThumbnail/"+url
                sourceSize: Qt.size(thumbnailPhotos.cellWidth,thumbnailPhotos.cellHeight)
                width: thumbnailPhotos.cellWidth
                height: width
                fillMode: Image.PreserveAspectFit
                Rectangle{
                    id:selectedCircle
                    color: "transparent"
                    opacity:0.5
                    width:parent.width
                    height: width
                }

                MouseArea {
                    anchors.fill:parent
                    onClicked: {
                        if(!thumbnailWrapper.selectedContainsAndRemove(index,TdlibState.Photo))
                        {
                            selectedCircle.color = Theme.secondaryHighlightColor;
                            thumbnailWrapper.selectedItems.push({"id":index,"type":TdlibState.Photo,"url":galleryModel.get(index).url});
                            thumbnailWrapper.countItems++;
                        }
                        else
                        {
                            selectedCircle.color = "transparent";
                            thumbnailWrapper.countItems--;
                        }
                    }
                    onPressAndHold: {
                        var fileUrl = galleryModel.get(index).url.toString()
                        //                        if(fileUrl.slice(0,4) === "file")
                        //                            fileUrl = fileUrl.slice(7, fileUrl.length)

                        pageStack.push("../PicturePage.qml",{imagePath:fileUrl})
                    }

                }
            }

        }
    }

    Button {
        id: attachButton
        preferredWidth: Theme.buttonWidthLarge
        text: countItems == 0 ? qsTr("Cancel") : qsTr("Send") + " ("+countItems+")"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Theme.paddingMedium
        onClicked: {
            if(countItems>0)
            {
                thumbnailWrapper.sendUrlItems(thumbnailWrapper.selectedItems)
                thumbnailWrapper.selectedItems = [];
            }
            attachDrawer.open = false
        }
    }



    Component {
        id: audioComponent

        Image {
            asynchronous: true
            // From org.nemomobile.thumbnailer
            source: thumbnailPhotos.icons[1]
            sourceSize: Qt.size(thumbnailPhotos.cellWidth, thumbnailPhotos.cellHeight)

            Rectangle{
                id:selectedCircle
                border.color: Theme.primaryColor
                color: "transparent"
                border.width: 2
                radius: 90
                width: Theme.paddingLarge
                height: width
                x: Theme.paddingLarge
                y: Theme.paddingLarge
            }

            MouseArea {
                anchors.fill: parent
                onClicked:
                {
                    selectedCircle.color = Theme.secondaryHighlightColor;
                    thumbnailWrapper.selectedItems.push({"url":audioModel.get(index).url, "type":files.currentIndex});
                }
            }

            Label {
                width: parent.width
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Theme.paddingSmall
                wrapMode: Text.Wrap
                text: title
            }
        }
    }

    Component {
        id: fileComponent

        BackgroundItem{
            width: parent.width
            height: Theme.itemSizeSmall

            Row {
                width: parent.width - 2*Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                height: parent.height
                spacing: Theme.paddingSmall

                Image {
                    id:icon
                    anchors.verticalCenter: parent.verticalCenter
                    source: iconPath
                }

                Column {
                    width: parent.width - icon.width - spacing
                    anchors.verticalCenter: parent.verticalCenter

                    Label {
                        font.pixelSize: Theme.fontSizeSmall
                        font.bold: true
                        text: title
                    }

                    Label {
                        font.pixelSize: Theme.fontSizeTiny
                        color: Theme.secondaryColor
                        text: subtitle
                    }
                }
            }
            onClicked: index ===0 ? pageStack.push(filePickerPage) : pageStack.push(documentPickerPage)

            Component {
                id: filePickerPage

                FilePickerPage {
                    title: qsTr("Files to send")
                    onSelectedContentPropertiesChanged: {
                        thumbnailWrapper.selectedItems = []
                        thumbnailWrapper.selectedItems.push({"id":0, "type":TdlibState.Document, "url":selectedContentProperties.filePath});
                        thumbnailWrapper.sendUrlItems(thumbnailWrapper.selectedItems)
                        thumbnailWrapper.selectedItems=[];
                        attachDrawer.open = false
                    }
                }
            }

            Component {
                id: documentPickerPage

                DocumentPickerPage {
                    title: qsTr("Files to send")
                    onSelectedContentPropertiesChanged: {
                        thumbnailWrapper.selectedItems = []
                        thumbnailWrapper.selectedItems.push({"id":0, "type":TdlibState.Document, "url":selectedContentProperties.filePath});
                        thumbnailWrapper.sendUrlItems(thumbnailWrapper.selectedItems)
                        thumbnailWrapper.selectedItems=[];
                        attachDrawer.open = false
                    }
                }
            }
        }
    }

    function selectedContainsAndRemove(idx, type)
    {
        for(var i=0;i<selectedItems.length;i++)
        {   if(selectedItems[i].id===idx && selectedItems[i].type===type)
            {
                selectedItems.splice(i,1)
                return true;
            }
        }
        return false;
    }
}
