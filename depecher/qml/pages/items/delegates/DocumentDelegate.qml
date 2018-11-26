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

