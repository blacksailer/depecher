import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import "../../../js/utils.js" as Utils
import QtMultimedia 5.6
Page {
    id:page
    property alias chatId: itemsModel.peerId
    property alias filter: itemsModel.filter
    property alias totalCount: itemsModel.totalCount
    SearchChatMessagesModel {
        id: itemsModel
    }
SilicaListView {
    id:list
    property var currentFilter
model: itemsModel
    header: PageHeader {
        title:  qsTr("Audios")
    }
    anchors.fill: parent
    delegate:         BackgroundItem {
        width: Utils.getWidth()
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
                                               (__depecher_audio.source == "file://"+content && __depecher_audio.playbackState == Audio.PlayingState)
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
                                if(file_is_downloading)
                                    itemsModel.cancelDownload(index)
                            else
                                itemsModel.downloadDocument(index)
                        } else {
                            if(__depecher_audio.playbackState == Audio.PlayingState)
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
                anchors.verticalCenter: playIcon.verticalCenter

                Label {

                    color: pressed ? Theme.primaryColor : Theme.secondaryColor
                    font.pixelSize: Theme.fontSizeSmall
                    text: audio_title
                }

                Label {

                    color: pressed ? Theme.primaryColor : Theme.secondaryColor
                    font.pixelSize: Theme.fontSizeTiny
                    text: audio_performer
                }
                Label {

                    color: pressed ? Theme.primaryColor : Theme.secondaryColor
                    font.pixelSize: Theme.fontSizeTiny
                    text: Format.formatDuration(duration,Formatter.DurationShort)
                }
            }
        }
    }
}


}
