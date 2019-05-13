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
        id: imageColumn
        width: image.width
        property alias textHeight: captionText.height
        ConfigurationValue {
            id: fullSizeInChannels
            key:"/apps/depecher/ui/message/fullSizeInChannels"
            defaultValue: false
        }
        property real currentWidth: image.getWidth()
        property real currentHeight: image.getHeight() - nameplateHeight - 20
        property bool marginCorrection: currentWidth < currentHeight*photo_aspect ||
                                        currentHeight*photo_aspect > currentWidth - Theme.horizontalPageMargin + 10
        states: [
            State {
                name: "fullSize"
                when: fullSizeInChannels.value && messagingModel.chatType["is_channel"] &&
                      !marginCorrection
                PropertyChanges {
                    target: image
                    maxWidth: currentWidth
                    maxHeight: currentHeight
                    width: Math.min(maxHeight * photo_aspect, maxWidth)
                    height: Math.min(maxHeight, maxWidth / photo_aspect)
                }
            }, State {
                name: "fullSizeWithMarginCorrection"
                extend: "fullSize"
                when: fullSizeInChannels.value && messagingModel.chatType["is_channel"] &&
                      marginCorrection
                PropertyChanges {
                    target: captionText
                    x: Theme.horizontalPageMargin + 10
                    width: image.width - 2 * x
                }
                PropertyChanges {
                    target: imageColumn
                    x: -10
                }
            }
        ]
        Image {
            id: image
            asynchronous: true
            property int maxWidth: getWidth()-Theme.itemSizeExtraSmall - Theme.paddingMedium - 2*Theme.horizontalPageMargin
            property int maxHeight: getHeight()/2
            width: photo_aspect >= 1 ? maxWidth *3/4 : maxHeight * photo_aspect
            height: photo_aspect >= 1 ? maxWidth/photo_aspect : maxHeight
            fillMode: Image.PreserveAspectFit
            source: content
            MouseArea{
                anchors.fill: parent
                enabled: file_downloading_completed
                onClicked: {
                    pageStack.push("../../PicturePage.qml",{imagePath:content})

                }
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
                            if(file_is_uploading)
                                messagingModel.deleteMessage(index)
                            else if(file_is_downloading)
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

