import QtQuick 2.6
import Sailfish.Silica 1.0
import TelegramModels 1.0
import QtFeedback 5.0
import tdlibQtEnums 1.0
import org.nemomobile.notifications 1.0
import "items"

Page {
    id: page
    allowedOrientations: Orientation.All
    property alias userName: messagingModel.userName
    property alias chatId: messagingModel.peerId
    property alias chatType: messagingModel.chatType
    property alias lastMessageId: messagingModel.lastMessage
    property alias lastOutboxId: messagingModel.lastOutboxId
    property alias lastReadMessage: messagingModel.currentMessage

    Notification {
        id: notificationError
        appName: "Depecher"
        icon: "image://theme/icon-lock-warning"
        expireTimeout: 1
    }

    MessagingModel{
        id: messagingModel
        onChatTypeChanged: {
            if(chatType === TdlibState.Channel)
            {
                writer.sendAreaHeight = 0
                writer.bottomArea.visible = false
            }
        }
        onErrorReceived: {
            notificationError.previewBody(error_code +"-" +error_message)
            notificationError.publish()
        }
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

        Timer {
            //Because TextBase of TextArea uses Timer for losing focus.
            //Let's reuse that =)
            id: restoreFocusTimer
            interval: 50
            onTriggered: writer.textArea.forceActiveFocus()
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
                title: messagingModel.userName
                height: Math.max(_preferredHeight, _titleItem.y + _titleItem.height + actionLabel.height + Theme.paddingMedium)

                Label {
                    id: actionLabel
                    width: parent.width - parent.leftMargin - parent.rightMargin
                    anchors {
                        top: parent._titleItem.bottom
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
                onAtYEndChanged: {
                    if (messageList.atYEnd) {
                        debouncer.restart() // Debounce to avoid too much requests
                    }
                }

                Timer {
                    id: debouncer
                    interval: 500
                    repeat: false
                    running: false
                    onTriggered: messagingModel.getNewMessages()
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
                                Clipboard.text = content
                            }
                        }
                        MenuItem {
                            text: qsTr("Delete Message")
                            visible: can_be_deleted_only_for_yourself
                            onClicked: {
                                showRemorseDelete()
                            }
                        }
                        MenuItem {
                            text: qsTr("Delete for everyone")
                            visible: can_be_deleted_for_all_users
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

