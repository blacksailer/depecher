import QtQuick 2.6
import Sailfish.Silica 1.0
import "items"

Page {

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: content.height + header.height

        PullDownMenu {
        MenuItem {
        text: "Join / Leave Channel"
        }
        }

        PageHeader {
            id:header
            title:qsTr("Channel info")
        }
        Column {
            id:content
            width: parent.width
            anchors.top: header.bottom
            Row {
                width: parent.width
                Image {
                    id: avatar
                    width: Theme.itemSizeLarge
                    height: width
                    source: "image://theme/icon-m-contact"
                }
                Column {
                    width: parent.width - avatar.width
                    anchors.verticalCenter:   parent.verticalCenter
                    Label {
                        text: "Channel Name"
                        font.pixelSize: Theme.fontSizeMedium
                        width:parent.width
                    }
                    Label {
                        font.pixelSize: Theme.fontSizeTiny
                        text: "XXXX members"
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
                            text:"t.me/sailfishos"
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }
                BackgroundItem {
                    width: parent.width
                    height: Theme.itemSizeSmall
                    Row {
                        width: parent.width - 2 * x
                        anchors.verticalCenter: parent.verticalCenter
                        x: Theme.horizontalPageMargin
                        Item {
                            width:Theme.paddingLarge + Theme.iconSizeMedium
                            height: Theme.paddingLarge
                        }
                        Column {
                            width: parent.width - iconAbout.width - Theme.paddingLarge
                            anchors.verticalCenter:   parent.verticalCenter
                            Label {
                                text:"ipsum lorem"
                                wrapMode: Text.WordWrap
                                width:parent.width
                            }
                            Label {
                                font.pixelSize: Theme.fontSizeTiny
                                text: "Description"
                                width:parent.width
                            }
                        }

                    }
                }
                IconTextSwitch {
                    text: "Notifications"
                    icon.source: "image://theme/icon-m-alarm"
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
                            text:"%1 photos".arg(27)
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }
                BackgroundItem {
                    width: parent.width
                    height: Theme.itemSizeSmall
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
                            text:"%1 videos".arg(27)
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }
                BackgroundItem {
                    width: parent.width
                    height: Theme.itemSizeSmall
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
                            text:"%1 files".arg(27)
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }
                BackgroundItem {
                    width: parent.width
                    height: Theme.itemSizeSmall
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
                            text:"%1 audio files".arg(88)
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }

                BackgroundItem {
                    width: parent.width
                    height: Theme.itemSizeSmall
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
                            text:"%1 shared links".arg(13)
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }
                BackgroundItem {
                    width: parent.width
                    height: Theme.itemSizeSmall
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
                            text:"%1 audio voice files".arg(88)
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }


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
                        text:"%1 Members".arg(111)
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
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
                    Item {
                        width: Theme.paddingLarge + Theme.iconSizeMedium
                        height: Theme.paddingLarge
                    }
                    Label {
                        width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                        text:"Block user"
                        color:Theme.errorColor
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }

        }
    }
}
