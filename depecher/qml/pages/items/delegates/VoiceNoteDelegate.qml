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
    property int maxWidth: messageListItem.width *2/3 - Theme.horizontalPageMargin * 2
    width: maxWidth

    BackgroundItem {
        width: parent.width
        height: Theme.itemSizeSmall
        Row {
            id: documentRowWrapper
            width: parent.width
            spacing: Theme.paddingMedium
            height: parent.height

            Image {
                id: playIcon
                fillMode: Image.PreserveAspectFit
                source: progress.visible ? "image://theme/icon-m-clear"
                                         : file_downloading_completed ?
                                               (__depecher_audio.source == "file://"+content && __depecher_audio.playbackState === Audio.PlayingState)
                                               ? "image://theme/icon-m-pause"
                                               : "image://theme/icon-m-play"
                                               : "image://theme/icon-m-cloud-download"
                anchors.verticalCenter: parent.verticalCenter

                ProgressCircle {
                    id: progress
                    anchors.fill: parent
                    visible: file_is_uploading || file_is_downloading
                    value : file_is_uploading ? file_uploaded_size / file_downloaded_size :
                                                file_downloaded_size / file_uploaded_size
                }


                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(!file_downloading_completed) {
                            if(progress.visible)
                                if(file_is_downloading)
                                    messagingModel.cancelDownload(index)
                                else
                                    messagingModel.deleteMessage(index)
                            else
                                messagingModel.downloadDocument(index)
                        } else {
                            if(__depecher_audio.playbackState === Audio.PlayingState)
                                __depecher_audio.stop()
                            else {
                            __depecher_audio.source =  "file://"+content
                            __depecher_audio.play()
                            }
                        }
                    }
                }

            }

            Column {
                width: parent.width - playIcon.width - parent.spacing
                spacing: Theme.paddingSmall
                anchors.verticalCenter: playIcon.verticalCenter

                Label {

                    color: pressed ? Theme.primaryColor : Theme.secondaryColor
                    font.pixelSize: Theme.fontSizeSmall
                    text: qsTr("Voice note")
}
                Label {

                    color: pressed ? Theme.primaryColor : Theme.secondaryColor
                    font.pixelSize: Theme.fontSizeTiny
                    text: Format.formatDuration(duration,Formatter.DurationShort)
                }
            }
        }
    }

    LinkedLabel {
        width: documentRowWrapper.width
        plainText: file_caption
        color: pressed ? Theme.secondaryColor :Theme.primaryColor
        linkColor: pressed ? Theme.secondaryHighlightColor : Theme.highlightColor
        font.pixelSize: Theme.fontSizeSmall
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        visible: file_caption ? true : false
    }
}

