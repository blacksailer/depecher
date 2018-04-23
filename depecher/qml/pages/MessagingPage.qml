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
                delegate: ListItem {
                    id:messageListItem
                    width:parent.width
                    contentHeight: columnWrapper.height

                    menu: ContextMenu {
                        MenuItem {
                            text: qsTr("Copy Text")
                            onClicked: {
                                Clipboard.text = content
                            }
                        }
                    }
                    Column{
                        id:columnWrapper
                        width:contentLoader.width
                        height: contentLoader.height
                        anchors.right: is_outgoing ? parent.right : undefined
                        anchors.left: is_outgoing ?  undefined : parent.left
                        anchors.rightMargin: is_outgoing ? Theme.horizontalPageMargin : 0
                        anchors.leftMargin: is_outgoing ?  0 : Theme.horizontalPageMargin
                        Loader {
                            id:contentLoader
                            focus:true

                            Component.onCompleted:  {
                                if(message_type == 0)
                                    sourceComponent = textContent
                                if(message_type == 1)
                                    sourceComponent = imageContent
                                if(message_type == 2)
                                    sourceComponent = stickerContent
                                if(message_type == 3)
                                    sourceComponent = newMessageContent
                            }
                            Component {
                                id:textContent
                                Column{
                                    id:textColumn
                                    width:textItem.width
                                    Row{
                                        id:subInfoRow
                                        width:parent.width
                                        Label {
                                            visible: messagingModel.chatType == TdlibState.BasicGroup ?  true :
                                                                                                        messagingModel.chatType == TdlibState.Supergroup ? true
                                                                                                                                                         : false
                                            id:authorName
                                            //                                        width:Math.max(parent.width*4/5,implicitWidth)
                                            text:author
                                            color: pressed ?Theme.highlightColor: Theme.secondaryHighlightColor
                                            font.pixelSize: Theme.fontSizeExtraSmall
                                            truncationMode: TruncationMode.Fade
                                        }
                                    }

                                    LinkedLabel {
                                        id:textItem
                                        width: text.length<32?paintedWidth:messageListItem.width*3/4
                                        plainText:content?content:""
                                        color: pressed ? Theme.secondaryColor :Theme.primaryColor
                                        linkColor: pressed ? Theme.secondaryHighlightColor :Theme.highlightColor
                                        font.pixelSize: Theme.fontSizeSmall
                                        wrapMode: Text.WordWrap
                                    }
                                    Separator{
                                        color:pressed ? Theme.primaryColor : Theme.secondaryColor
                                        width:parent.width/3
                                    }
                                    Row {
                                        id:metaInfoRow
                                        width:parent.width
                                        layoutDirection: is_outgoing ? Qt.RightToLeft : Qt.LeftToRight
                                        Label{
                                            function timestamp(dateTime){
                                                var dateTimeDate=new Date(dateTime*1000)

                                                var datetime_day = dateTimeDate.getDay()
                                                var currentDay = new Date().getDay()

                                                if (datetime_day==currentDay)
                                                    return Format.formatDate(dateTimeDate, Formatter.TimeValue)
                                                else
                                                    return Format.formatDate(dateTimeDate, Formatter.DateMediumWithoutYear)
                                            }
                                            font.pixelSize: Theme.fontSizeTiny
                                            color:pressed ? Theme.primaryColor : Theme.secondaryColor
                                            text:timestamp(date)
                                        }

                                    }
                                }
                            }
                            Component {
                                id:imageContent
                                Column{
                                    width:messageListItem.width/4*3
                                    Row{
                                        id:subInfoRow
                                        width:parent.width
                                        Label {
                                            visible: messagingModel.chatType == TdlibState.BasicGroup ?  true :
                                                                                                        messagingModel.chatType == TdlibState.Supergroup ? true
                                                                                                                                                         : false
                                            id:authorName
                                            //                                        width:Math.max(parent.width*4/5,implicitWidth)
                                            text:author
                                            color: pressed ?Theme.highlightColor: Theme.secondaryHighlightColor
                                            font.pixelSize: Theme.fontSizeExtraSmall
                                            truncationMode: TruncationMode.Fade
                                        }
                                    }

                                    Image {
                                        width: messageListItem.width/4*3 < implicitWidth ? messageListItem.width/4*3 : implicitWidth
                                        fillMode: Image.PreserveAspectFit
                                        source:"image://depecherDb/"+content
                                        MouseArea{
                                            anchors.fill: parent
                                            onClicked: pageStack.push("PicturePage.qml",{imagePath:content})
                                        }
                                    }
                                    LinkedLabel {
                                        width: parent.width
                                        plainText:photo_caption
                                        color: pressed ? Theme.secondaryColor :Theme.primaryColor
                                        linkColor: pressed ? Theme.secondaryHighlightColor :Theme.highlightColor
                                        font.pixelSize: Theme.fontSizeSmall
                                        wrapMode: Text.WordWrap
                                        visible:  photo_caption === "" ? false : true
                                    }
                                    Separator{
                                        color:pressed ? Theme.primaryColor : Theme.secondaryColor
                                        width:parent.width/3
                                    }
                                    Row {
                                        id:metaInfoRow
                                        width:parent.width
                                        layoutDirection: is_outgoing ? Qt.RightToLeft : Qt.LeftToRight
                                        Label{
                                            function timestamp(dateTime){
                                                var dateTimeDate=new Date(dateTime*1000)

                                                var datetime_day = dateTimeDate.getDay()
                                                var currentDay = new Date().getDay()

                                                if (datetime_day==currentDay)
                                                    return Format.formatDate(dateTimeDate, Formatter.TimeValue)
                                                else
                                                    return Format.formatDate(dateTimeDate, Formatter.DateMediumWithoutYear)
                                            }
                                            font.pixelSize: Theme.fontSizeTiny
                                            color:pressed ? Theme.primaryColor : Theme.secondaryColor
                                            text:timestamp(date)
                                        }

                                    }

                                }
                            }
                            Component {
                                id:stickerContent
                                Column{
                                    width:messageListItem.width/4*3
                                    Row{
                                        id:subInfoRow
                                        width:parent.width
                                        Label {
                                            visible: messagingModel.chatType == TdlibState.BasicGroup ?  true :
                                                                                                        messagingModel.chatType == TdlibState.Supergroup ? true
                                                                                                                                                         : false
                                            id:authorName
                                            //                                        width:Math.max(parent.width*4/5,implicitWidth)
                                            text:author
                                            color: pressed ?Theme.highlightColor: Theme.secondaryHighlightColor
                                            font.pixelSize: Theme.fontSizeExtraSmall
                                            truncationMode: TruncationMode.Fade
                                        }
                                    }

                                    Image {

                                        width:parent.width
                                        fillMode: Image.PreserveAspectFit
                                        source:"image://depecherDb/"+content
                                    }
                                    Row {
                                        id:metaInfoRow
                                        width:parent.width
                                        layoutDirection: is_outgoing ? Qt.RightToLeft : Qt.LeftToRight
                                        Label{
                                            function timestamp(dateTime){
                                                var dateTimeDate=new Date(dateTime*1000)

                                                var datetime_day = dateTimeDate.getDay()
                                                var currentDay = new Date().getDay()

                                                if (datetime_day==currentDay)
                                                    return Format.formatDate(dateTimeDate, Formatter.TimeValue)
                                                else
                                                    return Format.formatDate(dateTimeDate, Formatter.DateMediumWithoutYear)
                                            }
                                            font.pixelSize: Theme.fontSizeTiny
                                            color:pressed ? Theme.primaryColor : Theme.secondaryColor
                                            text:timestamp(date)
                                        }

                                    }

                                }
                            }
                            Component {
                                id:newMessageContent
                                Item{
                                    width: messageListItem.width - 2*Theme.horizontalPageMargin
                                    height:Theme.itemSizeSmall
                                    Rectangle {
                                        width: newMessagesLabel.width + 2* Theme.paddingLarge
                                        height: newMessagesLabel.height
                                        anchors.centerIn: parent

                                        radius: 90
                                        color:Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity)
                                        Label{
                                            id:newMessagesLabel
                                            anchors.centerIn: parent
                                            text:qsTr("new messages")
                                            font.pixelSize: Theme.fontSizeTiny
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
