import QtQuick 2.6
import Sailfish.Silica 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import "items"
Page {
    id: page
    allowedOrientations: Orientation.All
    property alias userName:messagingModel.userName
    property alias chatId: messagingModel.peerId
    property alias chatType: messagingModel.chatType
    property alias lastMessageId: messagingModel.lastMessage
    property alias lastReadMessage: messagingModel.currentMessage

    MessagingModel{
        id:messagingModel
        onChatTypeChanged: {
            if(chatType === TdlibState.Channel)
            {
                writer.sendAreaHeight = 0
                writer.bottomArea.visible = false
            }
        }
    }
    Component.onDestruction: {
        c_telegramWrapper.closeChat(messagingModel.peerId)
    }
    WritingItem{
        id:writer

        actionButton.onClicked:
        {
            messagingModel.sendTextMessage(textArea.text,0)
            textArea.text = ""
            textArea.forceActiveFocus(Qt.MouseFocusReason)
        }
        onSendFiles: {
            for(var i = 0; i < files.length; i++)
            {
                var fileUrl = String(files[i].url)
                if(fileUrl.slice(0,4) === "file")
                    fileUrl = fileUrl.slice(7,fileUrl.length)
                //Slicing removes occurance of file://
                if(files[i].type === TdlibState.Photo)
                    messagingModel.sendPhotoMessage(fileUrl,0,"")
                if(files[i].type === TdlibState.Document)
                    messagingModel.sendDocumentMessage(fileUrl,0,"")
            }

        }
        Column{
            width:page.width
            height:parent.height-writer.sendAreaHeight
            PageHeader {
                id:nameplate
                title:  messagingModel.userName
                description: messagingModel.action
            }
            SilicaListView {
                id:messageList
                width:parent.width
                height: parent.height - nameplate.height
                clip: true
                verticalLayoutDirection: ListView.BottomToTop
                spacing: Theme.paddingSmall
                model:messagingModel

                NumberAnimation {
                    id:moveAnimation
                    target: messageList
                    property: "contentY"
                    duration: 500
                    easing.type: Easing.InOutQuad
                    running: false
                    onRunningChanged: {
                        console.log(running)
                        if(!running)
                            messagingModel.getNewMessages()
                    }
                }
                PushUpMenu{
                    id:pushMenu
                    quickSelect: true
                    visible: !messagingModel.atYEnd
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
                    menu: ContextMenu {
                        MenuItem {
                            text: qsTr("Copy Text")
                            onClicked: {
                                Clipboard.text = content
                            }
                        }
                    }
                }
            }
        }
    }
}
