import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import QtMultimedia 5.6
import Nemo.Configuration 1.0
import Nemo.DBus 2.0
import QtQml.Models 2.3
import depecherUtils 1.0
import QtGraphicalEffects 1.0

Column{
        width:animation.width
        Item {
            property int maxWidth: page.width -Theme.itemSizeExtraSmall - Theme.paddingMedium - 2*Theme.horizontalPageMargin
            property int maxHeight: setHeight()
            width: maxHeight
            height: width
        VideoOutput {
            id: animation
            anchors.fill: parent
            fillMode: VideoOutput.PreserveAspectFit
            layer.enabled:true
            layer.effect: OpacityMask {
                maskSource: Item {
                    width: animation.width
                    height: animation.height
                    Rectangle {
                        anchors.centerIn: parent
                        width: animation.width
                        height: animation.height
                        radius: Math.min(width, height)
                    }
                }
            }

            source: MediaPlayer {
                id: mediaPlayer
                source: file_downloading_completed ? "file://"+(content) : ""
                autoLoad: true
                // autoPlay: true
                loops:  Animation.Infinite
            }
            Connections {
                target: Qt.application
                onStateChanged: {
                    if(Qt.application.state !== Qt.ApplicationActive)
                        mediaPlayer.stop()
                }
            }

            Image {
                id:animationThumbnail
                anchors.fill: parent
                source: "image://depecherDb/"+media_preview
                visible:  mediaPlayer.playbackState != MediaPlayer.PlayingState || !file_downloading_completed;
                Rectangle {
                    id:dimmedColor
                    anchors.fill: parent
                    opacity: 0.5
                    color:"black"
                }
                ProgressCircle {
                    id:progress
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
                    MouseArea{
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
            Rectangle {
                id:dimmedPlayColor
                anchors.fill: animation
                opacity: 0.5
                color:"black"
                visible: file_downloading_completed && mediaPlayer.playbackState != MediaPlayer.PlayingState

            }
            Image {
                id: playIcon
                visible: file_downloading_completed && mediaPlayer.playbackState != MediaPlayer.PlayingState
                source:  "image://theme/icon-m-play"
                anchors.centerIn: dimmedPlayColor
            }
            MouseArea{
                anchors.fill: dimmedPlayColor
                enabled: file_downloading_completed
                onClicked: {
                    mediaPlayer.playbackState != MediaPlayer.PlayingState ?   mediaPlayer.play() : mediaPlayer.stop()
                }
            }

        }

        Label {
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: Theme.paddingSmall
            anchors.bottomMargin: Theme.paddingSmall

            color: pressed ? Theme.primaryColor : Theme.secondaryColor
            font.pixelSize: Theme.fontSizeTiny
            text:  mediaPlayer.playbackState != MediaPlayer.StoppedState ?
                       Format.formatDuration(mediaPlayer.duration / 1000 - mediaPlayer.position / 1000,Formatter.DurationShort)
                     : Format.formatDuration(duration,Formatter.DurationShort)
        }
        Label {
            color:  Theme.primaryColor
            visible: downloadIcon.visible
            font.pixelSize: Theme.fontSizeTiny
            text: Format.formatFileSize(file_downloaded_size) + "/"
                  + Format.formatFileSize(file_uploaded_size)
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: Theme.paddingSmall
            anchors.bottomMargin: Theme.paddingSmall
        }
        function setHeight() {
            switch(page.orientation) {
            case Orientation.Portrait:
            case Orientation.PortraitInverted:
                return Screen.height / 3
            case Orientation.Landscape:
            case Orientation.LandscapeInverted:
                return Screen.width / 2

            }
        }
        }
    }
