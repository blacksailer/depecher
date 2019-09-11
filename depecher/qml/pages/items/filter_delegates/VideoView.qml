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
SilicaGridView {
        id:grid
        property var currentFilter
        header: PageHeader {
            title: qsTr("Videos")
        }
        model:itemsModel
        anchors.fill: parent
        cellHeight: width/3
        cellWidth: width/3

        delegate: Image {
            id: image
            asynchronous: true
            width:  Utils.getWidth() / 3
            height: width
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
                            if(file_is_downloading)
{

                                itemsModel.cancelDownload(index)
}
                            else
{
                            itemsModel.downloadDocument(index)
}
                    }
                }
            }
        }

    }

}
