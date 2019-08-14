import QtQuick 2.6
import Sailfish.Silica 1.0
import TelegramDAO 1.0
import tdlibQtEnums 1.0
import Nemo.Notifications 1.0
import "items"
import "items/delegates"
Page {
    property int user_id: -1
    property int supergroup_id: -1
    property double chat_id: -1
    property alias username: resolver.username
    Component.onCompleted: {
        if(user_id > -1)
        {
            loader.sourceComponent  = userInfoComponent
            loader.item.chatId=user_id
            loader.item.userId=user_id
        } else
        {
            loader.sourceComponent  = channelInfoComponent
            loader.item.chatId=chat_id
        }
    }
    Notification {
        id: notificationError
        appName: "Depecher"
        expireTimeout: 1
    }

    UsernameResolver {
        id:resolver
        onChatTypeChanged: {
            if(resolver.chatType === TdlibState.Private)
            {
                loader.sourceComponent  = userInfoComponent
                loader.item.chatId=resolver.resolvedChatId
                loader.item.userId=resolver.resolvedId
            }
            else {
                loader.sourceComponent  = channelInfoComponent
                loader.item.chatId=resolver.resolvedChatId
                loader.item.supergroupId=resolver.resolvedId
            }
        }
    }

    ViewPlaceholder {
        id:errorPlaceholder
        enabled:resolver.error != ""
        text: resolver.error
    }
    Loader {
        id:loader
        anchors.fill: parent
    }
    Component {
        id:userInfoComponent
        SilicaFlickable {
            property alias chatId: userInfo.chatId
            property alias userId: userInfo.userId

            UserInfo {
                id:userInfo
            }

            anchors.fill: parent
            visible: !errorPlaceholder.enabled
            contentHeight: content.height + header.height
            PageHeader {
                id:header
                title:qsTr("User info")
            }
            PullDownMenu {
                MenuItem {
                    text: qsTr("Send message")
                    onClicked:    {
                        var page = pageStack.find(function (page) {
                            return page.__chat_page !== undefined;
                        });
                        pageStack.replaceAbove(page,"MessagingPage.qml",{chatId:user_id})
                    }
                }
            }
            Column {
                id:content
                width: parent.width
                anchors.top: header.bottom
                Row {
                    width: parent.width - 2 * x
                    x:Theme.horizontalPageMargin
                    CircleImage {
                        id: avatar
                        width: Theme.itemSizeLarge
                        height: width
                        source: userInfo.avatar
                        fallbackText: userInfo.firstName != "" ? userInfo.firstName.charAt(0) :userInfo.lastName.charAt(0)
                        fallbackItemVisible: userInfo.avatar == ""

                    }
                    Item {
                        width: Theme.paddingLarge
                        height:Theme.paddingLarge
                    }

                    Column {
                        width: parent.width - avatar.width - Theme.paddingLarge
                        anchors.verticalCenter:   parent.verticalCenter
                        Label {
                            text: userInfo.firstName + " " + userInfo.lastName
                            font.pixelSize: Theme.fontSizeMedium
                            width:parent.width
                        }
                        Label {
                            font.pixelSize: Theme.fontSizeTiny
                            text: userInfo.status
                            color:Theme.secondaryColor

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
                        visible: userInfo.phoneNumber != ""
                        Row {
                            width: parent.width - 2 * x
                            anchors.verticalCenter: parent.verticalCenter
                            x: Theme.horizontalPageMargin
                            Icon {
                                id:iconPhone
                                source: "image://theme/icon-m-device"
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            Item {
                                width: Theme.paddingLarge
                                height: Theme.paddingLarge
                            }
                            Label {
                                width: parent.width - iconPhone.width - Theme.paddingLarge
                                text:userInfo.phoneNumber
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                    BackgroundItem {
                        width: parent.width
                        height: Theme.itemSizeSmall
                        visible: userInfo.username != ""

                        Row {
                            width: parent.width - 2 * x
                            anchors.verticalCenter: parent.verticalCenter
                            x: Theme.horizontalPageMargin
                            Item {
                                width:Theme.paddingLarge + Theme.iconSizeMedium
                                height: Theme.paddingLarge
                            }
                            Column {
                                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                                anchors.verticalCenter:   parent.verticalCenter
                                Label {
                                    text:"@"+userInfo.username
                                    width:parent.width
                                }
                                Label {
                                    font.pixelSize: Theme.fontSizeTiny
                                    color:Theme.secondaryColor
                                    text: "Username"
                                    width:parent.width
                                }
                            }

                        }
                    }
                    IconTextSwitch {
                        text: qsTr("Notifications")
                        description: checked ? qsTr("Click to disable notifications") :  qsTr("Click to enable notifications")
                        icon.source: checked ? "image://theme/icon-m-speaker-on" :  "image://theme/icon-m-speaker-mute"
                        checked: userInfo.muteFor != 0
                        onClicked: userInfo.changeNotifications(!checked)
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
                        visible: userInfo.photoCount
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
                                width: parent.width - iconPhone.width - Theme.paddingLarge
                                text:qsTr("%1 photos").arg(userInfo.photoCount)
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                    BackgroundItem {
                        width: parent.width
                        height: Theme.itemSizeSmall
                        visible: userInfo.videoCount
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
                                text:qsTr("%1 videos").arg(userInfo.videoCount)
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                    BackgroundItem {
                        width: parent.width
                        height: Theme.itemSizeSmall
                        visible: userInfo.fileCount
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
                                text:qsTr("%1 files").arg(userInfo.fileCount)
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                    BackgroundItem {
                        width: parent.width
                        height: Theme.itemSizeSmall
                        visible: userInfo.audioCount
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
                                text:qsTr("%1 audio").arg(userInfo.audioCount)
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                    BackgroundItem {
                        width: parent.width
                        height: Theme.itemSizeSmall
                        visible: userInfo.linkCount

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
                                text:qsTr("%1 links").arg(userInfo.linkCount)
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                    BackgroundItem {
                        width: parent.width
                        height: Theme.itemSizeSmall
                        visible: userInfo.groupCount
                        Row {
                            width: parent.width - 2 * x
                            anchors.verticalCenter: parent.verticalCenter
                            x: Theme.horizontalPageMargin
                            Icon {
                                id:iconGroups
                                source: "image://theme/icon-m-people"
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            Item {
                                width: Theme.paddingLarge
                                height: Theme.paddingLarge
                            }
                            Label {
                                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                                text:qsTr("%1 groups in common").arg(userInfo.groupCount)
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                    BackgroundItem {
                        width: parent.width
                        height: Theme.itemSizeSmall
                        visible: userInfo.voiceCount
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
                                text:qsTr("%1 voice notes").arg(userInfo.voiceCount)
                                anchors.verticalCenter: parent.verticalCenter
                            }
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
                            Item {
                                width: Theme.paddingLarge + Theme.iconSizeMedium
                                height: Theme.paddingLarge
                            }
                            Label {
                                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                                text:"Share contact"
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
                                width: Theme.paddingLarge + Theme.iconSizeMedium
                                height: Theme.paddingLarge
                            }
                            Label {
                                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                                text:"Edit contact"
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
                                width: Theme.paddingLarge + Theme.iconSizeMedium
                                height: Theme.paddingLarge
                            }
                            Label {
                                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                                text:"Delete contact"
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
                                width: Theme.paddingLarge + Theme.iconSizeMedium
                                height: Theme.paddingLarge
                            }
                            Label {
                                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                                text:"Clear history"
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
                                width: Theme.paddingLarge + Theme.iconSizeMedium
                                height: Theme.paddingLarge
                            }
                            Label {
                                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                                text:"Delete conversation"
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

    }
    Component {
        id:channelInfoComponent
        SilicaFlickable {
            property alias chatId: channelInfo.chatId
            property alias supergroupId: channelInfo.supergroupId

            ChannelInfo {
                id:channelInfo
            }
            Connections {
                target: channelInfo
                onErrorChanged: {
                    notificationError.summary = errorPlaceholder
                    notificationError.publish()
                }
            }
            anchors.fill: parent
            visible: !errorPlaceholder.enabled
            contentHeight: content.height + header.height
            PageHeader {
                id:header
                title:qsTr("Channel info")
            }
            PullDownMenu {
                MenuItem {
                    text: channelInfo.isMember ?  qsTr("Leave channel") : qsTr("Join channel")
                    onClicked: {
                        if(channelInfo.isMember)
                        leaveRemorse.execute(qsTr("Leaving"), function() {
                            channelInfo.leaveChat()
                        })
                        else
                            channelInfo.joinChat()
                    }
                }
                RemorsePopup {
                    id:leaveRemorse
                }
            }

            Column {
                id:content
                width: parent.width
                anchors.top: header.bottom
                Row {
                    width: parent.width - 2 * x
                    x:Theme.horizontalPageMargin
                    CircleImage {
                        id: avatar
                        width: Theme.itemSizeLarge
                        height: width
                        source: channelInfo.avatar
                        fallbackText: channelInfo.name.charAt(0)
                        fallbackItemVisible: channelInfo.avatar == ""

                    }
                    Item {
                        width: Theme.paddingLarge
                        height:Theme.paddingLarge
                    }

                    Column {
                        width: parent.width - avatar.width - Theme.paddingLarge
                        anchors.verticalCenter:   parent.verticalCenter
                        Label {
                            text: channelInfo.name
                            font.pixelSize: Theme.fontSizeMedium
                            width:parent.width
                        }
                        Label {
                            font.pixelSize: Theme.fontSizeTiny
                            text: qsTr('%1 members').arg(channelInfo.members)
                            color:Theme.secondaryColor

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
                        visible: channelInfo.link != ""
                        Row {
                            width: parent.width - 2 * x
                            anchors.verticalCenter: parent.verticalCenter
                            x: Theme.horizontalPageMargin
                            Icon {
                                id:iconPhone
                                source: "image://theme/icon-m-device"
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            Item {
                                width: Theme.paddingLarge
                                height: Theme.paddingLarge
                            }
                            Label {
                                width: parent.width - iconPhone.width - Theme.paddingLarge
                                text:channelInfo.link
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                    BackgroundItem {
                        width: parent.width
                        height: descriptionWrapper.height
                        visible:channelInfo.description != ""

                        Row {
                            width: parent.width - 2 * x
                            anchors.verticalCenter: parent.verticalCenter
                            x: Theme.horizontalPageMargin
                            Item {
                                width:Theme.paddingLarge + Theme.iconSizeMedium
                                height: Theme.paddingLarge
                            }
                            Column {
                                id:descriptionWrapper
                                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                                anchors.verticalCenter:   parent.verticalCenter
                                RichTextItem {
                                    text:channelInfo.description
                                    font.pixelSize: Theme.fontSizeSmall
                                    wrapMode: Text.WordWrap
                                    width:parent.width
                                }
                                Label {
                                    font.pixelSize: Theme.fontSizeTiny
                                    color:Theme.secondaryColor
                                    text: "Description"
                                    width:parent.width
                                }
                            }

                        }
                    }
                    IconTextSwitch {
                        text: qsTr("Notifications")
                        description: checked ? qsTr("Click to disable notifications") :  qsTr("Click to enable notifications")
                        icon.source: checked ? "image://theme/icon-m-speaker-on" :  "image://theme/icon-m-speaker-mute"
                        checked: muteFor != 0
                        onClicked:
                        {
                            channelInfo.changeNotifications(!checked)
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
                        visible: channelInfo.photoCount
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
                                width: parent.width - iconPhone.width - Theme.paddingLarge
                                text:qsTr("%1 photos").arg(channelInfo.photoCount)
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                    BackgroundItem {
                        width: parent.width
                        height: Theme.itemSizeSmall
                        visible: channelInfo.videoCount
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
                                text:qsTr("%1 videos").arg(channelInfo.videoCount)
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                    BackgroundItem {
                        width: parent.width
                        height: Theme.itemSizeSmall
                        visible: channelInfo.fileCount
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
                                text:qsTr("%1 files").arg(channelInfo.fileCount)
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                    BackgroundItem {
                        width: parent.width
                        height: Theme.itemSizeSmall
                        visible: channelInfo.audioCount
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
                                text:qsTr("%1 audio").arg(channelInfo.audioCount)
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                    BackgroundItem {
                        width: parent.width
                        height: Theme.itemSizeSmall
                        visible: channelInfo.linkCount

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
                                text:qsTr("%1 links").arg(channelInfo.linkCount)
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                    BackgroundItem {
                        width: parent.width
                        height: Theme.itemSizeSmall
                        visible: channelInfo.voiceCount
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
                                text:qsTr("%1 voice notes").arg(channelInfo.voiceCount)
                                anchors.verticalCenter: parent.verticalCenter
                            }
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
                            Item {
                                width: Theme.paddingLarge + Theme.iconSizeMedium
                                height: Theme.paddingLarge
                            }
                            Label {
                                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                                text:qsTr('Report')
                                color:Theme.errorColor
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }

                }

            }
        }

    }
}
