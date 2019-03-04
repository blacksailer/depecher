import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import QtMultimedia 5.6
import Nemo.Configuration 1.0
import Nemo.DBus 2.0
import QtQml.Models 2.3
import depecherUtils 1.0

Column{
        width: image.width
        property alias textHeight: captionText.height
        Image {
            id: image
            asynchronous: true
            property int maxWidth: getWidth()-Theme.itemSizeExtraSmall - Theme.paddingMedium - 2*Theme.horizontalPageMargin
            property int maxHeight: getHeight()/2
            width: photo_aspect >= 1 ? maxWidth : maxHeight * photo_aspect
            height: photo_aspect >= 1 ? maxWidth/photo_aspect : maxHeight
            fillMode: Image.PreserveAspectFit
            source: "image://depecherDb/"+content
            
            MouseArea{
                anchors.fill: parent
                enabled: file_downloading_completed
                onClicked: pageStack.push("../../PicturePage.qml",{imagePath:content})
            }
            
            ProgressCircle {
                id: progress
                anchors.centerIn: parent
                visible: file_is_uploading || file_is_downloading
                value : file_is_uploading ? file_uploaded_size / file_downloaded_size :
                                            file_downloaded_size / file_uploaded_size
            }
            
            Image {
                id: downloadIcon
                visible: !file_downloading_completed || progress.visible
                source: progress.visible ? "image://theme/icon-s-clear-opaque-cross"
                                         : "image://theme/icon-s-update"
                anchors.centerIn: parent
                
                MouseArea {
                    enabled: parent.visible
                    anchors.fill: parent
                    onClicked: {
                        if(progress.visible)
                            if(file_is_downloading)
                                messagingModel.cancelDownload(index)
                            else
                                messagingModel.deleteMessage(index)
                        else
                            messagingModel.downloadDocument(index)
                    }
                }
            }
            function getWidth() {
                switch(page.orientation) {
                case Orientation.Portrait:
                case Orientation.PortraitInverted:
                    return Screen.width
                case Orientation.Landscape:
                case Orientation.LandscapeInverted:
                    return Screen.height

                }
            }
            function getHeight() {
                switch(page.orientation) {
                case Orientation.Portrait:
                case Orientation.PortraitInverted:
                    return Screen.height
                case Orientation.Landscape:
                case Orientation.LandscapeInverted:
                    return Screen.width

                }
            }

        }
        
        LinkedLabel {
            id:captionText
            width: parent.width
            plainText: file_caption
            color: pressed ? Theme.secondaryColor :Theme.primaryColor
            linkColor: pressed ? Theme.secondaryHighlightColor :Theme.highlightColor
            font.pixelSize: Theme.fontSizeSmall
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            visible: file_caption === "" ? false : true
        }
    }

