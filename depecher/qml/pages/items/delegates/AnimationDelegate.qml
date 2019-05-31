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
    id:gifColumn
        width:animation.width
        property alias textHeight: captionText.height
        ConfigurationValue {
            id: fullSizeInChannels
            key:"/apps/depecher/ui/message/fullSizeInChannels"
            defaultValue: false
        }
        property real currentWidth: getWidth()
        property real currentHeight: getHeight() - nameplateHeight - 20
        property bool marginCorrection: currentWidth < currentHeight*photo_aspect ||
                                        currentHeight*photo_aspect > currentWidth - Theme.horizontalPageMargin + 10
        states: [
            State {
                name: "fullSize"
                when: fullSizeInChannels.value && messagingModel.chatType["is_channel"] &&
                      !marginCorrection
            }, State {
                name: "fullSizeWithMarginCorrection"
                extend: "fullSize"
                when: fullSizeInChannels.value && messagingModel.chatType["is_channel"] &&
                      marginCorrection
                PropertyChanges {
                    target: captionText
                    x: Theme.horizontalPageMargin + 10
                    width: animation.width - 2 * x
                }
                PropertyChanges {
                    target: gifColumn
                    x: -10
                }

            }
        ]

        Component {
            id:gifComponent
            AnimatedImage {
                id:animationGif
                property int maxWidth:gifColumn.getWidth()-Theme.itemSizeExtraSmall - Theme.paddingMedium - 2*Theme.horizontalPageMargin
                property int maxHeight: gifColumn.getHeight() / 2
                width: photo_aspect > 1 ? maxWidth : maxHeight * photo_aspect
                height: photo_aspect > 1 ? maxWidth/photo_aspect : maxHeight
                fillMode: VideoOutput.PreserveAspectFit
                source: file_downloading_completed ? "file://"+content : ""
                playing: false
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
                        animationGif.playing = !animationGif.playing
                    }
                    Connections {
                        target: Qt.application
                        onStateChanged: {
                            if(Qt.application.state !== Qt.ApplicationActive)
                                nimationGif.playing = false
                        }
                    }
                    
                }
                states: [
                    State {
                        name: "fullSize"
                        when: fullSizeInChannels.value && messagingModel.chatType["is_channel"] &&
                              !marginCorrection
                        PropertyChanges {
                            target: animationGif
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
                    }
                ]
            }
        }
        Component {
            id:mp4Component
            VideoOutput {
                id: animationVideo
                property int maxWidth: gifColumn.getWidth() - Theme.itemSizeExtraSmall - Theme.paddingMedium - 2*Theme.horizontalPageMargin
                property int maxHeight: gifColumn.getHeight() / 2
                width: photo_aspect > 1 ? maxWidth : maxHeight * photo_aspect
                height: photo_aspect > 1 ? maxWidth / photo_aspect : maxHeight
                fillMode: VideoOutput.PreserveAspectFit
                
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
                }
                Rectangle {
                    id:dimmedPlayColor
                    anchors.fill: animationVideo
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
                MouseArea {
                    anchors.fill: dimmedPlayColor
                    enabled: file_downloading_completed
                    onClicked: {
                        mediaPlayer.playbackState != MediaPlayer.PlayingState ?   mediaPlayer.play() : mediaPlayer.stop()
                    }
                }
                states: [
                    State {
                        name: "fullSize"
                        when: fullSizeInChannels.value && messagingModel.chatType["is_channel"] &&
                              !marginCorrection
                        PropertyChanges {
                            target: animationVideo
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
                    }
                ]

            }
        }
        Loader {
            id:animation
            sourceComponent: file_type === "video/mp4" ? mp4Component : gifComponent
        }
        
        LinkedLabel {
            id:captionText
            width: parent.width
            plainText:file_caption
            color: pressed ? Theme.secondaryColor :Theme.primaryColor
            linkColor: pressed ? Theme.secondaryHighlightColor :Theme.highlightColor
            font.pixelSize: Theme.fontSizeSmall
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            visible:  file_caption === "" ? false : true
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
