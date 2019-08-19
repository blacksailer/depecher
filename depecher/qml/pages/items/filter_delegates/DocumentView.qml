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
model:itemsModel
    header: PageHeader {
        title:   qsTr("Documents")
    }
    anchors.fill: parent
    delegate:            BackgroundItem {
        width: parent.width
        height: Theme.itemSizeMedium
        enabled: file_downloading_completed && !file_is_uploading
        onClicked: Qt.openUrlExternally("file://"+content)

        Row {
            id: documentRowWrapper
            width: parent.width
            spacing: Theme.paddingMedium
            height: parent.height

            Image {
                id: image
                fillMode: Image.PreserveAspectFit
                source: "image://theme/icon-m-file-document"
                anchors.verticalCenter: parent.verticalCenter

                ProgressCircle {
                    id: progress
                    anchors.fill: parent
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
                }

                MouseArea {
                    enabled: downloadIcon.visible
                    anchors.fill: parent
                    onClicked: {
                            if(file_is_downloading)
                                itemsModel.cancelDownload(index)
                        else
                            itemsModel.downloadDocument(index)
                    }
                }

            }

            Column {
                width: parent.width - image.width - parent.spacing
                spacing: Theme.paddingSmall
                anchors.verticalCenter: image.verticalCenter

                Label {
                    width: parent.width
                    elide: Text.ElideMiddle
                    color: pressed ? Theme.secondaryColor : Theme.primaryColor
                    font.pixelSize: Theme.fontSizeSmall
                    text: document_name
                }

                Label {

                    color: pressed ? Theme.primaryColor : Theme.secondaryColor
                    font.pixelSize: Theme.fontSizeTiny
                    text: Format.formatFileSize(file_downloaded_size) + "/"
                          + Format.formatFileSize(file_uploaded_size)
                }
            }
        }
    }

}


}


