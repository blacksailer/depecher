import QtQuick 2.6
import Sailfish.Silica 1.0
import TelegramDAO 1.0
import tdlibQtEnums 1.0
import Nemo.Notifications 1.0
import "items"
import "items/delegates"
import "items/filter_delegates"
Page {
    property int user_id: -1
    property int supergroup_id: -1
    property double chat_id: -1
    property alias username: resolver.username
    property bool hideOpenMenu: false
    Component.onCompleted: {
        console.log(chat_id)
        if(user_id > -1 && username == "")
        {
            loader.sourceComponent  = userInfoComponent
            loader.item.chatId=user_id
            loader.item.userId=user_id
        }
        if  (chat_id !== -1)      {
            loader.sourceComponent  = channelInfoComponent
            loader.item.chatId=chat_id
            loader.item.hideOpenMenu=hideOpenMenu

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
                console.log(resolver.resolvedChatId,resolver.resolvedId)

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
            Connections {
                target: userInfo
                onChatIdReceived: {
                    var page = pageStack.find(function (page) {
                        return page.__chat_page !== undefined;
                    });
                    pageStack.replaceAbove(page,"MessagingPage.qml",{chatId:chatId})
                }
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
                        var cid = userInfo.getChatId()
                        if(cid != "-1")
                        {
                            var page = pageStack.find(function (page) {
                                return page.__chat_page !== undefined;
                            });
                            pageStack.replaceAbove(page,"MessagingPage.qml",{chatId:cid})
                        }
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
                                    text: qsTr("Username")
                                    width:parent.width
                                }
                            }

                        }
                    }
                    IconTextSwitch {
                        text: qsTr("Notifications")
                        description: checked ? qsTr("Click to disable notifications") :  qsTr("Click to enable notifications")
                        icon.source: checked ? "image://theme/icon-m-speaker-on" :  "image://theme/icon-m-speaker-mute"
                        checked: userInfo.muteFor == 0
                        onClicked: userInfo.changeNotifications(!checked)
                    }
                }
                Item {
                    width: 1
                    height:Theme.paddingLarge
                }

                SharedContent {
                    chatId:userInfo.chatId

                    photoCount:userInfo.photoCount
                    videoCount:userInfo.videoCount
                    fileCount:userInfo.fileCount
                    audioCount:userInfo.audioCount
                    linkCount:userInfo.linkCount
                    voiceCount:userInfo.voiceCount
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
                            id:iconVoices
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

                Item {
                    width: 1
                    height:Theme.paddingLarge
                }

                //                Column {
                //                    width: parent.width
                //                    BackgroundItem {
                //                        width: parent.width
                //                        height: Theme.itemSizeSmall
                //                        Row {
                //                            width: parent.width - 2 * x
                //                            anchors.verticalCenter: parent.verticalCenter
                //                            x: Theme.horizontalPageMargin
                //                            Item {
                //                                width: Theme.paddingLarge + Theme.iconSizeMedium
                //                                height: Theme.paddingLarge
                //                            }
                //                            Label {
                //                                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                //                                text:"Share contact"
                //                                anchors.verticalCenter: parent.verticalCenter
                //                            }
                //                        }
                //                    }
                //                    BackgroundItem {
                //                        width: parent.width
                //                        height: Theme.itemSizeSmall
                //                        Row {
                //                            width: parent.width - 2 * x
                //                            anchors.verticalCenter: parent.verticalCenter
                //                            x: Theme.horizontalPageMargin
                //                            Item {
                //                                width: Theme.paddingLarge + Theme.iconSizeMedium
                //                                height: Theme.paddingLarge
                //                            }
                //                            Label {
                //                                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                //                                text:"Edit contact"
                //                                anchors.verticalCenter: parent.verticalCenter
                //                            }
                //                        }
                //                    }
                //                    BackgroundItem {
                //                        width: parent.width
                //                        height: Theme.itemSizeSmall
                //                        Row {
                //                            width: parent.width - 2 * x
                //                            anchors.verticalCenter: parent.verticalCenter
                //                            x: Theme.horizontalPageMargin
                //                            Item {
                //                                width: Theme.paddingLarge + Theme.iconSizeMedium
                //                                height: Theme.paddingLarge
                //                            }
                //                            Label {
                //                                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                //                                text:"Delete contact"
                //                                anchors.verticalCenter: parent.verticalCenter
                //                            }
                //                        }
                //                    }
                //                    BackgroundItem {
                //                        width: parent.width
                //                        height: Theme.itemSizeSmall
                //                        Row {
                //                            width: parent.width - 2 * x
                //                            anchors.verticalCenter: parent.verticalCenter
                //                            x: Theme.horizontalPageMargin
                //                            Item {
                //                                width: Theme.paddingLarge + Theme.iconSizeMedium
                //                                height: Theme.paddingLarge
                //                            }
                //                            Label {
                //                                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                //                                text:"Clear history"
                //                                anchors.verticalCenter: parent.verticalCenter
                //                            }
                //                        }
                //                    }
                //                    BackgroundItem {
                //                        width: parent.width
                //                        height: Theme.itemSizeSmall
                //                        Row {
                //                            width: parent.width - 2 * x
                //                            anchors.verticalCenter: parent.verticalCenter
                //                            x: Theme.horizontalPageMargin
                //                            Item {
                //                                width: Theme.paddingLarge + Theme.iconSizeMedium
                //                                height: Theme.paddingLarge
                //                            }
                //                            Label {
                //                                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                //                                text:"Delete conversation"
                //                                anchors.verticalCenter: parent.verticalCenter
                //                            }
                //                        }
                //                    }
                //                    BackgroundItem {
                //                        width: parent.width
                //                        height: Theme.itemSizeSmall
                //                        Row {
                //                            width: parent.width - 2 * x
                //                            anchors.verticalCenter: parent.verticalCenter
                //                            x: Theme.horizontalPageMargin
                //                            Item {
                //                                width: Theme.paddingLarge + Theme.iconSizeMedium
                //                                height: Theme.paddingLarge
                //                            }
                //                            Label {
                //                                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                //                                text:"Block user"
                //                                color:Theme.errorColor
                //                                anchors.verticalCenter: parent.verticalCenter
                //                            }
                //                        }
                //                    }

                //                }

            }
        }

    }
    Component {
        id:channelInfoComponent
        SilicaFlickable {
            id:flickable
            property alias chatId: channelInfo.chatId
            property alias supergroupId: channelInfo.supergroupId
            property bool hideOpenMenu: false

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
                MenuItem {
                    text: qsTr("Open channel")
                    visible: !flickable.hideOpenMenu
                    onClicked:{
                        {
                            var page = pageStack.find(function (page) {
                                return page.__chat_page !== undefined;
                            });
                            pageStack.replaceAbove(page,"MessagingPage.qml",{chatId:channelInfo.chatId})
                        }
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
                        checked: channelInfo.muteFor == 0
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


                SharedContent {
                    chatId:channelInfo.chatId

                    photoCount:channelInfo.photoCount
                    videoCount:channelInfo.videoCount
                    fileCount:channelInfo.fileCount
                    audioCount:channelInfo.audioCount
                    linkCount:channelInfo.linkCount
                    voiceCount:channelInfo.voiceCount
                }                Item {
                    width: 1
                    height:Theme.paddingLarge
                }

                //                Column {
                //                    width: parent.width

                //                    BackgroundItem {
                //                        width: parent.width
                //                        height: Theme.itemSizeSmall
                //                        Row {
                //                            width: parent.width - 2 * x
                //                            anchors.verticalCenter: parent.verticalCenter
                //                            x: Theme.horizontalPageMargin
                //                            Item {
                //                                width: Theme.paddingLarge + Theme.iconSizeMedium
                //                                height: Theme.paddingLarge
                //                            }
                //                            Label {
                //                                width: parent.width - Theme.iconSizeMedium - Theme.paddingLarge
                //                                text:qsTr('Report')
                //                                color:Theme.errorColor
                //                                anchors.verticalCenter: parent.verticalCenter
                //                            }
                //                        }
                //                    }

                //                }

            }
        }

    }
}
