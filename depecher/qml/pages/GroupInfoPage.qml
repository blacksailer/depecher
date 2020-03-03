import QtQuick 2.6
import Sailfish.Silica 1.0
import TelegramDAO 1.0
import tdlibQtEnums 1.0
import "items"
import "items/filter_delegates"
Page {

    property alias chat_id: groupInfo.chatId
    BasicGroupInfo {
        id:groupInfo
        onMembersModelChanged: {
            membersList.model = groupInfo.membersModel
        }
    }
    SilicaFlickable {
        anchors.fill: parent
        contentHeight: contentWrapper.height + header.height
        PageHeader {
            id:header
            title:qsTr("Group info")
        }
        PullDownMenu {
            MenuItem {
                text: groupInfo.inviteLink
            }
        }
        Column {
            id:contentWrapper
            width: parent.width
            anchors.top: header.bottom
            Row {
                width: parent.width
                CircleImage {
                    id: avatar
                    width: Theme.itemSizeLarge
                    height: width
                    source: groupInfo.avatar
                    fallbackText:  groupInfo.name.charAt(0)
                    fallbackItemVisible: groupInfo.avatar == ""
                }
                Item {
                    width: Theme.paddingLarge
                    height:Theme.paddingLarge
                }

                Column {
                    width: parent.width - avatar.width - Theme.paddingLarge
                    anchors.verticalCenter:   parent.verticalCenter
                    Label {
                        text: groupInfo.name
                        font.pixelSize: Theme.fontSizeMedium
                        width:parent.width
                    }
                    Label {
                        font.pixelSize: Theme.fontSizeTiny
                        color:Theme.secondaryColor

                        text: qsTr("%1 members").arg(groupInfo.members)
                        width:parent.width
                    }
                }
            }
            Item {
                width: 1
                height:Theme.paddingLarge
            }
            Column {
                width: parent.width
                BackgroundItem {
                    width: parent.width
                    height: Theme.itemSizeSmall
                    visible: groupInfo.inviteLink
                    Row {
                        width: parent.width - 2 * x
                        anchors.verticalCenter: parent.verticalCenter
                        x: Theme.horizontalPageMargin
                        Icon {
                            id:iconAbout
                            source: "image://theme/icon-m-about"
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Item {
                            width: Theme.paddingLarge
                            height: Theme.paddingLarge
                        }
                        Label {
                            width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                            text: groupInfo.inviteLink
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }
                IconTextSwitch {
                    text: qsTr("Notifications")
                    description: checked ? qsTr("Click to disable notifications") :  qsTr("Click to enable notifications")
                    icon.source: checked ? "image://theme/icon-m-speaker-on" :  "image://theme/icon-m-speaker-mute"
                    checked: groupInfo.muteFor == 0
                    onClicked: groupInfo.changeNotifications(!checked)
                }
            }
            Item {
                width: 1
                height:Theme.paddingLarge
            }
SharedContent {
    chatId:groupInfo.chatId

    photoCount:groupInfo.photoCount
    videoCount:groupInfo.videoCount
    fileCount:groupInfo.fileCount
    audioCount:groupInfo.audioCount
    linkCount:groupInfo.linkCount
    voiceCount:groupInfo.voiceCount
}
            Item {
                width: 1
                height:Theme.paddingLarge
            }

            BackgroundItem {
                width: parent.width
                height: Theme.itemSizeSmall
                Row {
                    width: parent.width - 2 * x
                    anchors.verticalCenter: parent.verticalCenter
                    x: Theme.horizontalPageMargin
                    Icon {
                        id:iconMembers
                        source: "image://theme/icon-m-people"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Item {
                        width: Theme.paddingLarge
                        height: Theme.paddingLarge
                    }
                    Label {
                        width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                        text:qsTr("%1 members").arg(groupInfo.members)
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }

            SilicaListView {
                id:membersList
                width: parent.width
                height: 6 *  Theme.itemSizeSmall
                clip:true
                delegate:  BackgroundItem {
                    width: parent.width
                    height: Theme.itemSizeSmall
                    Row {
                        width: parent.width - 2 * x
                        anchors.verticalCenter: parent.verticalCenter
                        x: Theme.horizontalPageMargin
                        CircleImage {
                            id:userPhoto
                            source: avatar ? avatar : ""
                            fallbackItemVisible: avatar == undefined
                            fallbackText:name.charAt(0)
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Item {
                            width: Theme.paddingLarge
                            height: Theme.paddingLarge
                        }
                        Column {
                            width: parent.width - userPhoto.width
                            anchors.verticalCenter:   parent.verticalCenter
                            Label {
                                text: name
                                font.pixelSize: Theme.fontSizeMedium
                                width:parent.width
                            }
                            Label {
                                font.pixelSize: Theme.fontSizeTiny
                                color:Theme.secondaryColor
                                text: online_status
                                width:parent.width
                            }
                        }
                    }
                }

            }

        }
    }
}
