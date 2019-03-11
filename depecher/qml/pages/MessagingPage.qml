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
    property var forwardMessages: ({})
    property var arrayIndex: []

    Notification {
        id: notificationError
        appName: "Depecher"
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
        if (Object.keys(forwardMessages).length !== 0) {
            writer.reply_id = "-1"
        writer.replyMessageAuthor = qsTr("Forwarded messages")
        writer.replyMessageText = forwardMessages.messages.length + " " + qsTr("messages")
        }
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
        anchors.fill: parent
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
                {
                    messagingModel.sendPhotoMessage(fileUrl, writer.reply_id, "")
                    writer.clearReplyArea()
                }
                if(files[i].type === TdlibState.Document)
                {
                    messagingModel.sendDocumentMessage(fileUrl,writer.reply_id,"")
                    writer.clearReplyArea()
                }
                if(files[i].type === TdlibState.Sticker)
                {
                    messagingModel.sendStickerMessage(files[i].id,writer.reply_id)
                    writer.clearReplyArea()

                }
            }
        }
    onReplyAreaCleared: {
    forwardMessages = {}
    }
        BusyIndicator {
            id:placeholder
            running: true
            size: BusyIndicatorSize.Large
            anchors.centerIn: messageList.parent
        }

//        bottomArea.onFocusChanged: {
//            messageList.positionViewAtEnd()
//        }

        Column {
            width: page.width
//            height: parent.height - writer.sendAreaHeight
            anchors.top:parent.top
            anchors.bottom:parent.bottom
            anchors.bottomMargin: writer.sendAreaHeight
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

                onHeightChanged: {
                    if(messageList.indexAt(width/2,height+contentY) >= count - 2)
{
                        messageList.positionViewAtEnd()
}
                }

                clip: true
                spacing: Theme.paddingSmall
                model: messagingModel

                Connections {
                    target: messagingModel
                    onRowsInserted: {
                    if(first == 0)
                        for(var i = 0; i < arrayIndex.length;i ++)
                            arrayIndex[i] = arrayIndex[i] + last + 1
                    if(messageList.atYEnd && messageList.state !== "preparing")
                        positionAtEndTimer.start()
                    }
                }
                topMargin:  -1 * Theme.itemSizeExtraLarge
                VerticalScrollDecorator {
                    flickable: messageList
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
                boundsBehavior: Flickable.DragOverBounds

                onContentYChanged: {

                    if(atYBeginning &&  !messagingModel.reachedHistoryEnd) {
                        fetchOlderTimer.start()
                    }
//                    needToScroll = indexAt(messageList.width/2,contentY + 50) > messageList.count - 8

                }
                delegate:           MessageItem {
                    id: myDelegate
                    onReplyMessageClicked:    {
                        if(messagingModel.findIndexById(replied_message_index) !== -1) {
                            arrayIndex.push(source_message_index)
                            writer.returnButtonEnabled = true

                            messageList.positionViewAtIndex(messagingModel.findIndexById(replied_message_index)+ 1,ListView.Center)
                            messageList.currentIndex =messagingModel.findIndexById(replied_message_index)+ 1
                        }/* else {
                                                                                  messagingModel.loadAndRefreshRepliedByIndex(source_message_index)
                                                                              }*/
                    }

                    ListView.onAdd: AddAnimation {
                        target: myDelegate
                    }
                    RemorseItem {
                        id: remorseDelete
                    }
                    ListView.onRemove: RemoveAnimation {
                        target: myDelegate
                    }
                    menu: ContextMenu {
                        MenuItem {
                            text: qsTr("Reply")
                            visible:  ((messagingModel.chatType["type"] == TdlibState.Supergroup && !messagingModel.chatType["is_channel"]) ||
                                      messagingModel.chatType["type"] == TdlibState.BasicGroup ||
                                      messagingModel.chatType["type"] == TdlibState.Private)
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
                        text:qsTr("Edit")
                        visible: can_be_edited && (message_type == MessagingModel.TEXT
                        || message_type == MessagingModel.PHOTO
                        || message_type == MessagingModel.VIDEO
                        || message_type == MessagingModel.DOCUMENT
                         || message_type == MessagingModel.ANIMATION
                         || message_type == MessagingModel.VOICE
                         || message_type == MessagingModel.AUDIO)



                        onClicked: {
                            if(message_type == MessagingModel.TEXT)
                            writer.state = "editText"
                            else
                            writer.state = "editCaption"

                            writer.edit_message_id = id
                            writer.replyMessageText = replyMessageContent()
                            writer.text = message_type == MessagingModel.TEXT ? content : file_caption
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
                        }
                        MenuItem {
                            text: qsTr("Forward")
                            visible: can_be_forwarded
                            onClicked: {
                                pageStack.push("SelectChatDialog.qml",{"from_chat_id": chatId,
                                                    "messages": [id]})
                            }
                        }
                        MenuItem {
                            text:message_type == MessagingModel.TEXT || file_caption ? qsTr("Copy text") : qsTr("Copy path")
                            onClicked: {
                                if(message_type == MessagingModel.TEXT)
                                    Clipboard.text = content
                                else if (file_caption)
                                    Clipboard.text = file_caption
                                else
                                    Clipboard.text = content
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
                        remorseDelete.execute(myDelegate, qsTr("Deleting..."), function() {
                            messagingModel.deleteMessage(index,true) }
                        )
                    }
                    function showRemorseDelete() {
                        remorseDelete.execute(myDelegate, qsTr("Deleting..."), function() { messagingModel.deleteMessage(index) } )
                    }
                }

                Timer {
                    id:centerTimer
                    interval: 800
                    onTriggered: {
                        messageList.positionViewAtIndex(messagingModel.lastMessageIndex + 1,ListView.Beginning)
                        messageList.currentIndex = messagingModel.lastMessageIndex + 1
                        messagingModel.fetchOlder()
                        messageList.state = "ready"
                    }
                }
                Timer {
                    id:fetchOlderTimer
                    interval: 500
                    repeat: false
                    onTriggered:{
                        if(messageList.state == "ready")
                        messagingModel.fetchOlder()
                    }
                }
                Timer {
                    id:positionAtEndTimer
                    interval: 500
                    repeat: false
                    onTriggered: messageList.positionViewAtEnd()
                }

                Component.onCompleted: {
                    centerTimer.start()
                }

            }
        }

        function sendText(text,reply_id) {
            if(writer.state == "publish")
{
            if(text.trim().length > 0)
                messagingModel.sendTextMessage(text,reply_id)
            if(reply_id == -1)
                messagingModel.sendForwardMessages(chatId,forwardMessages.from_chat_id,forwardMessages.messages)
} else if (writer.state == "editText") {
                messagingModel.sendEditTextMessage(writer.edit_message_id,text)
            }
            else if (writer.state == "editCaption") {
                messagingModel.sendEditCaptionMessage(writer.edit_message_id,text)

            }

            buzz.play()
            textArea.text = ""
            restoreFocusTimer.start()
            clearReplyArea()
        }
    }
}

