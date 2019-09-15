import QtQuick 2.6
import Sailfish.Silica 1.0
import TelegramDAO 1.0
import tdlibQtEnums 1.0


Column {
    id:sharedContent
    property var chatId

    property int photoCount
    property int videoCount
    property int fileCount
    property int audioCount
    property int linkCount
    property int voiceCount

    width: parent.width
    BackgroundItem {
        width: parent.width
        height: Theme.itemSizeSmall
        visible: sharedContent.photoCount
        Row {
            width: parent.width - 2 * x
            anchors.verticalCenter: parent.verticalCenter
            x: Theme.horizontalPageMargin
            Icon {
                id:iconImages
                source: "image://theme/icon-m-image"
                anchors.verticalCenter: parent.verticalCenter
            }
            Item {
                width: Theme.paddingLarge
                height: Theme.paddingLarge
            }
            Label {
                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                text:qsTr("%1 photos").arg(sharedContent.photoCount)
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    onClicked: pageStack.push("PhotoView.qml",{
                              totalCount: sharedContent.photoCount,
                              chatId: sharedContent.chatId,
                              filter:TdlibState.Photo
                              })
    }
    BackgroundItem {
        width: parent.width
        height: Theme.itemSizeSmall
        visible: sharedContent.videoCount
        Row {
            width: parent.width - 2 * x
            anchors.verticalCenter: parent.verticalCenter
            x: Theme.horizontalPageMargin
            Icon {
                id:iconVideos
                source: "image://theme/icon-m-video"
                anchors.verticalCenter: parent.verticalCenter
            }
            Item {
                width: Theme.paddingLarge
                height: Theme.paddingLarge
            }
            Label {
                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                text:qsTr("%1 videos").arg(videoCount)
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        onClicked: pageStack.push("VideoView.qml",{
                                  totalCount: sharedContent.photoCount,
                                  chatId: sharedContent.chatId,
                                  filter:TdlibState.Video
                                  })

    }
    BackgroundItem {
        width: parent.width
        height: Theme.itemSizeSmall
        visible: sharedContent.fileCount
        Row {

            width: parent.width - 2 * x
            anchors.verticalCenter: parent.verticalCenter
            x: Theme.horizontalPageMargin
            Icon {
                id:iconFiles
                source: "image://theme/icon-m-other"
                anchors.verticalCenter: parent.verticalCenter
            }
            Item {
                width: Theme.paddingLarge
                height: Theme.paddingLarge
            }
            Label {
                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                text:qsTr("%1 files").arg(sharedContent.fileCount)
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        onClicked: pageStack.push("DocumentView.qml",{
                                  totalCount: sharedContent.photoCount,
                                  chatId: sharedContent.chatId,
                                  filter:TdlibState.Document
                                  })
    }
    BackgroundItem {
        width: parent.width
        height: Theme.itemSizeSmall
        visible: sharedContent.audioCount
        Row {
            width: parent.width - 2 * x
            anchors.verticalCenter: parent.verticalCenter
            x: Theme.horizontalPageMargin
            Icon {
                id:iconAudios
                source: "image://theme/icon-m-sounds"
                anchors.verticalCenter: parent.verticalCenter
            }
            Item {
                width: Theme.paddingLarge
                height: Theme.paddingLarge
            }
            Label {
                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                text:qsTr("%1 audio").arg(sharedContent.audioCount)
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        onClicked: pageStack.push("AudioView.qml",{
                                  totalCount: sharedContent.photoCount,
                                  chatId: sharedContent.chatId,
                                  filter:TdlibState.Audio
                                  })
    }
    BackgroundItem {
        width: parent.width
        height: Theme.itemSizeSmall
        visible: sharedContent.linkCount

        Row {
            width: parent.width - 2 * x
            anchors.verticalCenter: parent.verticalCenter
            x: Theme.horizontalPageMargin
            Icon {
                id:iconLinks
                source: "image://theme/icon-m-link"
                anchors.verticalCenter: parent.verticalCenter
            }
            Item {
                width: Theme.paddingLarge
                height: Theme.paddingLarge
            }
            Label {
                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                text:qsTr("%1 links").arg(sharedContent.linkCount)
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        onClicked: pageStack.push("LinkView.qml",{
                                  totalCount: sharedContent.linkCount,
                                  chatId: sharedContent.chatId,
                                  filter:TdlibState.Url
                                  })

    }
    BackgroundItem {
        width: parent.width
        height: Theme.itemSizeSmall
        visible: sharedContent.voiceCount
        Row {
            width: parent.width - 2 * x
            anchors.verticalCenter: parent.verticalCenter
            x: Theme.horizontalPageMargin
            Icon {
                id:iconVoices
                source: "image://theme/icon-m-mic"
                anchors.verticalCenter: parent.verticalCenter
            }
            Item {
                width: Theme.paddingLarge
                height: Theme.paddingLarge
            }
            Label {
                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                text:qsTr("%1 voice notes").arg(sharedContent.voiceCount)
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        onClicked: pageStack.push("VoiceView.qml",{
                                  totalCount: sharedContent.photoCount,
                                  chatId: sharedContent.chatId,
                                  filter:TdlibState.VoiceNote
                                  })

    }
}
