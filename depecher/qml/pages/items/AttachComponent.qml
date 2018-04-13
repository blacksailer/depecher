import QtQuick 2.0
import Sailfish.Silica 1.0
import "../../MessageSendNetwork.js" as Net
import QtDocGallery 5.0

Item {
    id:thumbnailWrapper
    anchors.fill: parent
    property var selectedItems:[]
    property int countItems: selectedItems.length
    property alias docType : galleryModel.rootType
    property string attachmentId: ""
    property string attachmentPreview:""
    signal s_items(var items)
    signal menuTypeChanged (var type)

    // if there are many options, they will open
    // in a separate dialog
    ComboBox {
        id:files
        width: parent.width
        label: "Тип"
        menu: ContextMenu {
            MenuItem { text: qsTr("Фото") } //Порядок жестко определен. В родителе перечесление
            //            MenuItem { text: qsTr("Аудио") }
            //            MenuItem { text: qsTr("Документ") }
            //            MenuItem { text:qsTr("Видео") }
            //            MenuItem { text: qsTr("Место") }
            //            MenuItem { text: qsTr("Фото VK") }
            //            MenuItem { text: qsTr("Видео VK") }
        }
        onCurrentIndexChanged:
        {

            menuTypeChanged(currentIndex)
            if(currentIndex==0)
                thumbnailPhotos.delegate=imageComponent
            if(currentIndex==1)
                thumbnailPhotos.delegate=audioComponent
            galleryModel.cancel()
            galleryModel.clear()
            if(currentIndex==0) {
                thumbnailPhotos.model=galleryModel
            }
            if(currentIndex==1) {
                thumbnailPhotos.model=audioModel
            }
            if(currentIndex==2) {
                thumbnailPhotos.model=fileModel
            }

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
    DocumentGalleryModel {
        id: fileModel
        rootType: DocumentGallery.File //DocumentGallery.File || DocumentGallery.Audio
        properties: [ "url", "title", "fileName","lastModified" ]
        autoUpdate: true
        sortProperties: ["-lastModified"]
    }
    DocumentGalleryModel {
        id: audioModel
        rootType: DocumentGallery.Audio //DocumentGallery.File || DocumentGallery.Audio
        properties: [ "url", "title", "lastModified" ]
        autoUpdate: true
        sortProperties: ["-lastModified"]
    }
    SilicaGridView{
        id:thumbnailPhotos
        property var icons:["image://theme/icon-l-image","image://theme/icon-l-diagnostic","image://theme/icon-l-document"]
        width:parent.width
        anchors.top: files.bottom
        anchors.bottom: attachButton.top
        clip:true
        //            anchors.fill: parent
        cellWidth: width/3
        cellHeight: width/3
        model: galleryModel
        delegate: imageComponent
    }

    Button{
        id:attachButton
        preferredWidth: Theme.buttonWidthLarge
        text: countItems == 0 ? qsTr("Отменить") : qsTr("Прикрепить") + " ("+countItems+")"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        onClicked: {
            if(countItems>0)
            {
                console.log(galleryModel.get(thumbnailWrapper.selectedItems[0].id).url)
                thumbnailWrapper.s_items(thumbnailWrapper.selectedItems)
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
            sourceSize: Qt.size(thumbnailPhotos.cellWidth,thumbnailPhotos.cellHeight)
            width: thumbnailPhotos.cellWidth
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
                anchors.fill: parent
                onClicked:
                {
                    console.log(selectedItems.length)
                    if(!selectedContainsAndRemove(index,files.currentIndex))
                    {
                        selectedCircle.color = Theme.secondaryHighlightColor;
                        thumbnailWrapper.selectedItems.push({"id":index,"type":files.currentIndex,"url":galleryModel.get(index).url});
                        countItems++;
                    }
                    else
                    {
                        selectedCircle.color = "transparent";
                        countItems--;
                    }
                }
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
        Image {
            asynchronous: true
            // From org.nemomobile.thumbnailer
            source:   thumbnailPhotos.icons[2]
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
                    thumbnailWrapper.selectedItems.push({"url":fileModel.get(index).url,"type":files.currentIndex});
                }
            }
            Label{
                width: parent.width
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Theme.paddingSmall
                wrapMode:Text.Wrap
                text:fileName
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
