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
        isActive: page.status === PageStatus.Active
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

                messagingModel.sendTextMessage(messageText,0)
                buzz.play()
                textArea.text = ""
                restoreFocusTimer.start()
            }
        }
        actionButton.onClicked:
        {
            messagingModel.sendTextMessage(textArea.text,0)
            buzz.play()
            textArea.text = ""
            restoreFocusTimer.start()
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

        Column {
            width: page.width
            height: parent.height - writer.sendAreaHeight

            PageHeader {
                id: nameplate
                title: hideNameplate.value ? "" : messagingModel.userName
                height: hideNameplate.value ? actionLabel.height + Theme.paddingMedium : Math.max(_preferredHeight, _titleItem.y + _titleItem.height + actionLabel.height + Theme.paddingMedium)
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
                width: parent.width
                height: parent.height - nameplate.height
                clip: true
                verticalLayoutDirection: ListView.BottomToTop
                spacing: Theme.paddingSmall
                model: messagingModel
                //                onAtYEndChanged: {
                //                    if (messageList.atYEnd) {
                //                        debouncer.restart() // Debounce to avoid too much requests
                //                    }
                //                }

                NumberAnimation {
                    id:moveAnimation
                    target: messageList
                    property: "contentY"
                    duration: 500
                    easing.type: Easing.InOutQuad
                    running: false
                    onRunningChanged: {
                        if(!running)
                            messagingModel.getNewMessages()
                    }
                }
                PushUpMenu{
                    id:pushMenu
                    quickSelect: true
                    visible:!messagingModel.atYEnd
                    MenuItem{
                        text:qsTr("get newer")
                        onClicked:
                        {
                            var pos = messageList.contentY;
                            messageList.positionViewAtIndex(1,ListView.Beginning)
                            var destPos = messageList.contentY;
                            moveAnimation.from = pos;
                            moveAnimation.to = destPos;
                            moveAnimation.running = true;
                        }

                    }
                }
                delegate: MessageItem {
                    id: myDelegate

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
            }
        }
    }

}

