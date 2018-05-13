import QtQuick 2.0
import Sailfish.Silica 1.0
import QtDocGallery 5.0
import Sailfish.Pickers 1.0
import org.nemomobile.thumbnailer 1.0

import tdlibQtEnums 1.0
Item {
    id:thumbnailWrapper
    anchors.fill: parent
    property var selectedItems:[]
    property int countItems: selectedItems.length
    property alias docType : galleryModel.rootType
    property string attachmentId: ""
    property string attachmentPreview:""
    signal sendUrlItems(var items)
    signal menuTypeChanged (var type)

    // if there are many options, they will open
    // in a separate dialog
    ComboBox {
        id:files
        width: parent.width
        label: qsTr("Type")
        menu: ContextMenu {
            MenuItem { text: qsTr("Photo") } //Порядок жестко определен. В родителе перечесление
            //            MenuItem { text: qsTr("Аудио") }
            MenuItem { text: qsTr("Document") }
            //            MenuItem { text:qsTr("Видео") }
            //            MenuItem { text: qsTr("Место") }
            //            MenuItem { text: qsTr("Фото VK") }
            //            MenuItem { text: qsTr("Видео VK") }
        }
        onCurrentIndexChanged:
        {
            menuTypeChanged(currentIndex)
            galleryModel.cancel()
            galleryModel.clear()
        }

    }
    //nemo-qml-plugin-thumbnailer-qt5-video
    /*!
        \qmlproperty enum DocumentGalleryModel::rootType
        This property contains the type of item a query should return.
        It can be one of:
        \list
        \o DocumentGallery.InvalidType
        \o DocumentGallery.File
        \o DocumentGallery.Folder
        \o DocumentGallery.Document
        \o DocumentGallery.Text
        \o DocumentGallery.Audio
        \o DocumentGallery.Image
        \o DocumentGallery.Video
        \o DocumentGallery.Playlist
        \o DocumentGallery.Artist
        \o DocumentGallery.AlbumArtist
        \o DocumentGallery.Album
        \o DocumentGallery.AudioGenre
        \o DocumentGallery.PhotoAlbum
        \endlist
        The default value is DocumentGallery.File
    */
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
            title : qsTr("Home")
            subtitle: qsTr("Go to Home folder")
        }
        ListElement {
            iconPath: "image://theme/icon-m-file-folder"
            title : qsTr("Documents")
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
            delegate:  fileComponent
            clip: true
            VerticalScrollDecorator {}
        }
    }
    Loader {
        width: parent.width
        anchors.top: files.bottom
        anchors.bottom: attachButton.top
        sourceComponent: files.currentIndex === 1 ? filesViewComponent : photosViewComponent
    }

    Component {
        id: photosViewComponent
        SilicaGridView{
            id:thumbnailPhotos
            property var icons:["image://theme/icon-l-image","image://theme/icon-l-diagnostic","image://theme/icon-l-document"]
            width:parent.width
            anchors.fill: parent
            clip:true
            //            anchors.fill: parent
            cellWidth: width/3
            cellHeight: width/3
            model: galleryModel
            delegate: imageComponent
        }
    }
    Button{
        id:attachButton
        preferredWidth: Theme.buttonWidthLarge
        text: countItems == 0 ? qsTr("Cancel") : qsTr("Send") + " ("+countItems+")"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        onClicked: {
            if(countItems>0)
            {
                thumbnailWrapper.sendUrlItems(thumbnailWrapper.selectedItems)
                thumbnailWrapper.selectedItems=[];
            }
            attachDrawer.open = false
        }
    }


    Component{
        id:imageComponent
        Image {
            asynchronous: true
            // From org.nemomobile.thumbnailer
            source:   "image://nemoThumbnail/"+url
            sourceSize: Qt.size(Screen.width/3,Screen.width/3)
            width: Screen.width/3
            height: width

            Rectangle{
                id:selectedCircle
                border.color: Theme.primaryColor
                color: "transparent"
                border.width: 2
                radius: 90
                width:Theme.paddingLarge
                height: width
                x:Theme.paddingLarge
                y:Theme.paddingLarge
            }
            MouseArea {
                id:selectionArea
                x:0
                y:0
                width:Theme.paddingLarge * 2
                height: width
                onClicked:
                {
                    console.log(selectedItems.length)
                    if(!selectedContainsAndRemove(index,files.currentIndex))
                    {
                        selectedCircle.color = Theme.secondaryHighlightColor;
                        thumbnailWrapper.selectedItems.push({"id":index,"type":TdlibState.Photo,"url":galleryModel.get(index).url});
                        countItems++;
                    }
                    else
                    {
                        selectedCircle.color = "transparent";
                        countItems--;
                    }
                }
            }

            MouseArea {
                anchors.top: selectionArea.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                onClicked: pageStack.push("../PicturePage.qml",{imagePath:galleryModel.get(index).url})
            }

        }

    }
    Component {id:audioComponent
        Image {
            asynchronous: true
            // From org.nemomobile.thumbnailer
            source:   thumbnailPhotos.icons[1]
            sourceSize: Qt.size(thumbnailPhotos.cellWidth, thumbnailPhotos.cellHeight)

            Rectangle{
                id:selectedCircle
                border.color: Theme.primaryColor
                color: "transparent"
                border.width: 2
                radius: 90
                width:Theme.paddingLarge
                height: width
                x:Theme.paddingLarge
                y:Theme.paddingLarge
            }
            MouseArea {
                anchors.fill: parent
                onClicked:
                {

                    selectedCircle.color = Theme.secondaryHighlightColor;
                    thumbnailWrapper.selectedItems.push({"url":audioModel.get(index).url,"type":files.currentIndex});
                }
            }
            Label{
                width: parent.width
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Theme.paddingSmall
                wrapMode:Text.Wrap
                text:title
            }
        }
    }
    Component {id:fileComponent
        BackgroundItem{
            width: parent.width
            height: Theme.itemSizeSmall
            Row {
                width:parent.width - Theme.horizontalPageMargin * 2
                x: Theme.horizontalPageMargin
                height: parent.height
                spacing: Theme.paddingSmall
                Image {
                    id:icon
                    anchors.verticalCenter: parent.verticalCenter
                    source:iconPath
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
                        font.bold: true
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
                        thumbnailWrapper.selectedItems.push({"id":0,"type":TdlibState.Document,"url":selectedContentProperties.filePath});
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
                        thumbnailWrapper.selectedItems.push({"id":0,"type":TdlibState.Document,"url":selectedContentProperties.filePath});
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
        console.log(selectedItems.length)
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
