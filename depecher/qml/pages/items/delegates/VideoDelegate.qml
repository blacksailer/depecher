import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import QtMultimedia 5.6
import Nemo.Configuration 1.0
import Nemo.DBus 2.0
import QtQml.Models 2.3
import depecherUtils 1.0
import "utils.js" as JsUtils


Column{
    id:videoColumn
        width: image.width
        property alias textHeight: captionText.height
        property real currentWidth: JsUtils.getWidth()
        property real currentHeight: JsUtils.getHeight()
        property bool marginCorrection: currentWidth < currentHeight*photo_aspect ||
                                        currentHeight*photo_aspect > currentWidth - Theme.horizontalPageMargin + 10

        ConfigurationValue {
            id: fullSizeInChannels
            key:"/apps/depecher/ui/message/fullSizeInChannels"
            defaultValue: false
        }
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
                    x: Theme.paddingMedium
                    width: image.width - 2 * x
                }

            }
        ]


        Image {
            id: image
            asynchronous: true
            property int maxWidth: JsUtils.getWidth() - Theme.itemSizeExtraSmall - Theme.paddingMedium - 2*Theme.horizontalPageMargin
            property int maxHeight: JsUtils.getHeight()/2
            width: photo_aspect >= 1 ? maxWidth : maxHeight * photo_aspect
            height: photo_aspect >= 1 ? maxWidth/photo_aspect : maxHeight
            fillMode: Image.PreserveAspectFit
            source: "image://depecherDb/" + media_preview

            MouseArea{
                anchors.fill: parent
                enabled: file_downloading_completed
                onClicked:{
                    pageStack.push("../../VideoPage.qml",{source:content,thumbnail:media_preview})}
            }

            ProgressCircle {
                id: progress
                anchors.centerIn: parent
                visible: file_is_uploading || file_is_downloading
                value : file_is_uploading ? file_uploaded_size / file_downloaded_size :
                                            file_downloaded_size / file_uploaded_size
            }

            Label {
                id:durationText
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.rightMargin:  Theme.paddingSmall
                anchors.bottomMargin: Theme.paddingSmall

                color: pressed ? Theme.primaryColor : Theme.secondaryColor
                font.pixelSize: Theme.fontSizeTiny
                text: Format.formatDuration(duration,Formatter.DurationShort)
                z:1
            }
            Rectangle {
                id:dimmedPlayColor
                anchors.fill: image
                opacity: 0.5
                color:"black"
                visible: file_downloading_completed
            }
            Image {
                id: playIcon
                visible: file_downloading_completed
                source:  "image://theme/icon-m-play"
                anchors.centerIn: dimmedPlayColor
            }
            Rectangle {
            width: durationText.width + Theme.paddingSmall
            height: durationText.height
            anchors.centerIn: durationText
            radius: 10
            color:Theme.rgba(Theme.secondaryHighlightColor,0.5)
            z:0
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

