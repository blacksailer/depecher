import QtQuick 2.6
import Sailfish.Silica 1.0
import TelegramModels 1.0
import QtFeedback 5.0
import tdlibQtEnums 1.0
import Nemo.Notifications 1.0
import Nemo.Configuration 1.0
import "items"

Page {
    id: page
    allowedOrientations: Orientation.All
    property alias chatId: messagingModel.peerId
    property var arrayIndex: []

    Notification {
        id: notificationError
        appName: "Depecher"

        //        icon: "image://theme/icon-lock-warning"
        expireTimeout: 1
    }
    ConfigurationValue {
        id:sendByEnter
        key:"/apps/depecher/behavior/sendByEnter"
        defaultValue: false
    }
    ConfigurationValue {
        id:hideNameplate
        key:"/apps/depecher/ui/hideNameplate"
        defaultValue: false
    }
    MessagingModel{
        id: messagingModel
        isActive: page.status === PageStatus.Active && Qt.application.active
        onChatTypeChanged: {
            if(chatType["type"] == TdlibState.Supergroup)
            {
                if(!canPostMessages(memberStatus)) {
                    writer.sendAreaHeight = 0
                    writer.bottomArea.visible = false
                }
            }
        }
        function canPostMessages(statusObj) {
            if(messagingModel.chatType["type"] == TdlibState.Supergroup) {
                if(messagingModel.chatType["is_channel"])
                {
                    if(statusObj["status"] == MessagingModel.Member)
                        return false;
                    if(statusObj["status"] == MessagingModel.Creator && statusObj["is_member"])
                        return true;
                    if(statusObj["status"] == MessagingModel.Administrator)
                        return statusObj["can_post_messages"];
                }

                return true;
            }
            return true;
        }
        onCallbackQueryAnswerShow: {
            notificationError.previewBody = text
            if(show_alert)
                notificationError.icon = "image://theme/icon-lock-warning"
            else
                notificationError.icon = "image://theme/icon-lock-information"
            notificationError.publish()
        }

        onErrorReceived: {
            notificationError.previewBody = error_code +"-" +error_message
            notificationError.icon = "image://theme/icon-lock-warning"

            notificationError.publish()
        }
    }
    Component.onCompleted: {
        c_telegramWrapper.openChat(messagingModel.peerId)
    }
    Component.onDestruction: {
        c_telegramWrapper.closeChat(messagingModel.peerId)
    }

    ThemeEffect {
        id: buzz
        effect: ThemeEffect.Press
    }

    WritingItem {
        id: writer
        rootPage: page

        Timer {
            //Because TextBase of TextArea uses Timer for losing focus.
            //Let's reuse that =)
            id: restoreFocusTimer
            interval: 50
            onTriggered: writer.textArea.forceActiveFocus()
        }
        EnterKey.iconSource: sendByEnter.value ? "image://theme/icon-m-enter-next" : "image://theme/icon-m-enter"
        EnterKey.onClicked: {
            if(sendByEnter.value) {
                //removing on enter clicked symbol - /n
                var messageText = textArea.text.slice(0,textArea.cursorPosition-1) + textArea.text.slice(textArea.cursorPosition,textArea.text.length)
                sendText(messageText,writer.reply_id)
            }
        }
        returnButtonItem.onClicked: {
            if(arrayIndex.length>0)
            {
                messageList.currentIndex = arrayIndex.pop()
                messageList.positionViewAtIndex(messageList.currentIndex,ListView.Center)

            }
            returnButtonEnabled = arrayIndex.length > 0
        }
        actionButton.onClicked:  {
            sendText(textArea.text,writer.reply_id)
        }
        onSendFiles: {
            for(var i = 0; i < files.length; i++)
            {
                var fileUrl = String(files[i].url)
                if(fileUrl.slice(0,4) === "file")
                    fileUrl = fileUrl.slice(7, fileUrl.length)
                //Slicing removes occurance of file://
                if(files[i].type === TdlibState.Photo)
                    messagingModel.sendPhotoMessage(fileUrl, 0, "")
                if(files[i].type === TdlibState.Document)
                    messagingModel.sendDocumentMessage(fileUrl,0,"")
                if(files[i].type === TdlibState.Sticker)
                    messagingModel.sendStickerMessage(files[i].id,0)
            }
        }
        HorizontalScrollDecorator{}
        BusyIndicator {
            id:placeholder
            running: true
            size: BusyIndicatorSize.Large
            anchors.centerIn: messageList.parent
        }

        bottomArea.onFocusChanged: {
            messageList.positionViewAtEnd()
        }

        Column {
            width: page.width
            height: parent.height - writer.sendAreaHeight

            PageHeader {
                id: nameplate
                title: hideNameplate.value ? "" : messagingModel.userName
                height: hideNameplate.value ? actionLabel.height + Theme.paddingMedium : Math.max(_preferredHeight, _titleItem.y + _titleItem.height + actionLabel.height  + Theme.paddingMedium)
                Label {
                    id: actionLabel
                    width: parent.width - parent.leftMargin - parent.rightMargin
                    anchors {
                        top: hideNameplate.value ? parent.top : parent._titleItem.bottom
                        topMargin: hideNameplate.value ? Theme.paddingSmall : 0
                        right: parent.right
                        rightMargin: parent.rightMargin
                    }
                    text: messagingModel.action
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.highlightColor
                    opacity: 0.8
                    horizontalAlignment: Text.AlignRight
                    truncationMode: TruncationMode.Fade
                }
            }
            SilicaListView {
                id: messageList
                property bool needToScroll: false
                width: parent.width
                height: parent.height - nameplate.height
                clip: true
                spacing: Theme.paddingSmall
                model: messagingModel

                Connections {
                    target: messagingModel
                    onRowsAboutToBeInserted: {
                        if(messageList.atYEnd)
                        {
                            messageList.needToScroll = true
                            console.log("about to be inserted")
                        }
                    }
                }
                onFlickStarted: {
                    needToScroll = false
                    currentIndex = -1
                }
                onCountChanged: {
                    if(needToScroll)
                    {
                        positionViewAtEnd()
                    }
                }
                onCurrentIndexChanged:{
                    console.log(currentIndex)
                    //                    //Required - highlightRangeMode: ListView.StrictlyEnforceRange
                    //                    if(currentIndex == 10)
                    //                        messagingModel.fetchOlder()
                }
                state: "preparing"
                states: [
                    State {
                        name: "preparing"
                        PropertyChanges {
                            target: placeholder
                            running:true
                        }
                        PropertyChanges {
                            target: messageList
                            visible:false
                        }
                    }, State {
                        name: "ready"
                        PropertyChanges {
                            target: placeholder
                            running:false
                        }
                        PropertyChanges {
                            target: messageList
                            visible:true
                        }
                    }
                ]
                section {
                    property: "section"
                    labelPositioning:ViewSection.CurrentLabelAtStart | ViewSection.InlineLabels
                    delegate: Label {
                        id:secLabel
                        property string defaultString: Format.formatDate(new Date(section*1000),Formatter.DateMediumWithoutYear)
                        wrapMode: Text.WordWrap
                        color:Theme.highlightColor
                        font.pixelSize: Theme.fontSizeSmall
                        text: defaultString
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.topMargin: Theme.paddingMedium
                        anchors.bottomMargin: Theme.paddingMedium

                        MouseArea {
                            anchors.fill: parent
                            onClicked:{
                                parent.text = Format.formatDate(new Date(section*1000),Formatter.DateFull)
                                restoreDefaultInlineSectionTimer.start()
                            }
                        }
                        Timer {
                            id:restoreDefaultInlineSectionTimer
                            interval: 3 * 1000
                            onTriggered: {
                                parent.text = parent.defaultString
                            }
                        }
                    }
                }

                NumberAnimation {
                    id:moveAnimation
                    target: messageList
                    property: "contentY"
                    duration: 500
                    easing.type: Easing.InOutQuad
                    running: false
                    onRunningChanged: {
                        if(!running)
                            messagingModel.fetchOlder()
                    }
                }
                PullDownMenu {
                    quickSelect: true
                    visible:!messagingModel.reachedHistoryEnd
                    MenuItem{
                        text:qsTr("get more")
                        onClicked:
                        {
                            var pos = messageList.contentY;
                            messageList.positionViewAtIndex(1,ListView.Beginning)
                            messageList.currentIndex = 1
                            var destPos = messageList.contentY;
                            moveAnimation.from = pos;
                            moveAnimation.to = destPos;
                            moveAnimation.running = true;
                        }
                    }
                    busy: messagingModel.fetchOlderPending
                }
                delegate: MessageItem {
                    id: myDelegate
                    onReplyMessageClicked:
                    {
                        arrayIndex.push(source_message_index)
                        writer.returnButtonEnabled = true
                        //                        messageList.positionViewAtIndex(replied_message_index,ListView.Center)
                        messageList.currentIndex = replied_message_index
                        console.log(messageList.currentIndex,replied_message_index)
                    }
                    RemorseItem {
                        id: remorseDelete
                    }
                    //                    ListView.onAdd: AddAnimation {
                    //                        target: myDelegate
                    //                    }
                    ListView.onRemove: RemoveAnimation {
                        target: myDelegate
                    }
                    menu: ContextMenu {

                        MenuItem {
                            text: qsTr("Copy Text")
                            onClicked: {
                                if(message_type == MessagingModel.TEXT)
                                    Clipboard.text = content
                                else
                                    Clipboard.text = file_caption


                            }
                        }
                        MenuItem {
                            text: qsTr("Reply")
                            onClicked: {
                                writer.reply_id = id
                                writer.replyMessageAuthor = author
                                writer.replyMessageText = replyMessageContent()


                            }
                            function replyMessageContent() {
                                if(message_type == MessagingModel.TEXT) {
                                    return content
                                }
                                else if(message_type == MessagingModel.PHOTO) {
                                    return qsTr("Photo")
                                }
                                else if(message_type == MessagingModel.STICKER) {
                                    return qsTr("Sticker")
                                }
                                else if(message_type == MessagingModel.DOCUMENT) {
                                    return qsTr("Document")
                                }
                                else if(message_type == MessagingModel.ANIMATION) {
                                    return qsTr("Animation")
                                }
                                else if(message_type == MessagingModel.CONTACT) {
                                    return qsTr("Contact")
                                }
                                return qsTr("Message");
                            }
                        }
                        MenuItem {
                            text: qsTr("Delete Message")
                            visible: can_be_deleted_only_for_yourself ? can_be_deleted_only_for_yourself : false
                            onClicked: {
                                showRemorseDelete()
                            }
                        }
                        MenuItem {
                            text: qsTr("Delete for everyone")
                            visible: can_be_deleted_for_all_users ? can_be_deleted_for_all_users : false
                            onClicked: {
                                showRemorseDeleteToAll()
                            }
                        }
                    }
                    function showRemorseDeleteToAll() {
                        remorseDelete.execute(myDelegate, qsTr("Deleting..."), function() { messagingModel.deleteMessage(index,true) } )
                    }
                    function showRemorseDelete() {
                        remorseDelete.execute(myDelegate, qsTr("Deleting..."), function() { messagingModel.deleteMessage(index) } )
                    }
                }

                Timer {
                    id:centerTimer
                    interval: 500
                    onTriggered: {
                        messageList.positionViewAtIndex(messagingModel.lastMessageIndex,ListView.Center)
                        messageList.currentIndex = messagingModel.lastMessageIndex
                        messageList.state = "ready"
                    }
                }

                Component.onCompleted: {
                    centerTimer.start()
                }

            }
        }

        function sendText(text,reply_id) {
            messagingModel.sendTextMessage(text,reply_id)
            buzz.play()
            textArea.text = ""
            restoreFocusTimer.start()
        }
    }

}

