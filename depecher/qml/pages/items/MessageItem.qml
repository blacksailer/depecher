import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import QtMultimedia 5.6
import Nemo.Configuration 1.0
import Nemo.DBus 2.0
import QtQml.Models 2.3
import depecherUtils 1.0
import "../components"
import "delegates"

ListItem {
    id: messageListItem
    width: parent.width
    contentHeight:  columnWrapper.height + inlineView.height
    property string settingsPath:  "/apps/depecher/ui/message"
    property int currentMessageType: message_type ? message_type : 0
    onCurrentMessageTypeChanged: contentLoader.reload()
    signal replyMessageClicked(int source_message_index,string replied_message_index)
    highlighted: ListView.isCurrentItem

    Timer {
        id:highlightedTimer
        interval: 1000
        running: highlighted
        onTriggered: messageListItem.highlighted = false
    }

    ConfigurationValue {
        id:radiusValue
        key:settingsPath +"/radius"
        defaultValue: 0
    }
    ConfigurationValue {
        id:opacityValue
        key:settingsPath +"/opacity"
        defaultValue: 0
    }
    ConfigurationValue {
        id:colorValue
        key:settingsPath +"/color"
        defaultValue: Theme.secondaryColor
    }
    ConfigurationValue {
        id:incomingColorValue
        key:settingsPath +"/incomingColor"
        defaultValue: Theme.secondaryColor
    }
    ConfigurationValue {
        id:timeValue
        key:settingsPath +"/timepoint"
        defaultValue: Formatter.Timepoint
    }
    ConfigurationValue {
        id:oneAligningValue
        key:settingsPath +"/oneAlign"
        defaultValue: false//Theme.highlightDimmerColor
    }
    Rectangle {
        id:background
        width: columnWrapper.width
        height: columnWrapper.height
        x:columnWrapper.x
        y:columnWrapper.y
        visible: currentMessageType != MessagingModel.STICKER &&
                 currentMessageType != MessagingModel.SYSTEM_NEW_MESSAGE &&
                 currentMessageType != MessagingModel.JOINBYLINK &&
                 currentMessageType != MessagingModel.CONTACT_REGISTERED &&
                 currentMessageType != MessagingModel.CHAT_CREATED &&
                 index != 0

        radius: radiusValue.value
        opacity: opacityValue.value
        color: messageListItem.ListView.isCurrentItem ? Theme.highlightColor
                                                      :            is_outgoing ? getColor(colorValue.value)
                                                                               : getColor(incomingColorValue.value)

        function getColor(colorEnum) {
            if(typeof colorEnum == "number") {
                switch(colorEnum) {
                case 0:
                    return Theme.primaryColor
                case 1:
                    return Theme.secondaryColor
                case 2:
                    return Theme.highlightColor
                case 3:
                    return Theme.highlightBackgroundColor
                case 4:
                    return Theme.secondaryHighlightColor
                case 5:
                    return Theme.highlightDimmerColor
                }
            }
            return colorEnum
        }
    }

    Column {
        id: columnWrapper
        width: contentWrapper.width + 20
        anchors.right: oneAligningValue.value ? undefined :
                                          is_outgoing ? parent.right : undefined
        anchors.left: oneAligningValue.value ? parent.left :
                                         is_outgoing ? undefined : parent.left
        anchors.rightMargin:currentMessageType != MessagingModel.SYSTEM_NEW_MESSAGE &&
                            currentMessageType != MessagingModel.JOINBYLINK &&
                            currentMessageType != MessagingModel.CONTACT_REGISTERED &&
                            currentMessageType != MessagingModel.CHAT_CREATED ? Theme.horizontalPageMargin
                                                                              : 0
        anchors.leftMargin:currentMessageType != MessagingModel.SYSTEM_NEW_MESSAGE &&
                           currentMessageType != MessagingModel.JOINBYLINK &&
                           currentMessageType != MessagingModel.CONTACT_REGISTERED &&
                           currentMessageType != MessagingModel.CHAT_CREATED ? Theme.horizontalPageMargin :
                                                                               0
        Item {
            width: parent.width
            height:15
        }
        Row {
            id: contentWrapper
            spacing: Theme.paddingMedium
            x:currentMessageType != MessagingModel.SYSTEM_NEW_MESSAGE &&
              currentMessageType != MessagingModel.JOINBYLINK &&
              currentMessageType != MessagingModel.CONTACT_REGISTERED &&
              currentMessageType != MessagingModel.CHAT_CREATED ? 10 : 0
            width: Math.max(metaInfoRow.width,replyLoader.width,
                            userAvatarLoader.width + contentColumn.width +
                            (userAvatarLoader.width == 0 ? 0:spacing))
            //                       height: Math.max(userAvatarLoader.height+replyLoader.height,contentLoader.height+replyLoader.height)
            layoutDirection:oneAligningValue.value ?  Qt.LeftToRight :
                                                     is_outgoing ? Qt.RightToLeft : Qt.LeftToRight
            Loader {
                id: userAvatarLoader
                active: index != 0
                anchors.top: contentColumn.top
                sourceComponent: Component {
                    CircleImage {
                        id: userAvatar
                        width: visible ? Theme.itemSizeExtraSmall : 0
                        source: sender_photo ? "image://depecherDb/"+sender_photo : ""
                        fallbackText: author ? author.charAt(0) : ""
                        fallbackItemVisible: sender_photo ? false : true
                        visible: oneAligningValue.value ? currentMessageType != MessagingModel.SYSTEM_NEW_MESSAGE &&
                                                          currentMessageType != MessagingModel.JOINBYLINK &&
                                                          currentMessageType != MessagingModel.CONTACT_REGISTERED &&
                                                          currentMessageType != MessagingModel.CHAT_CREATED  &&
                                                          !messagingModel.chatType["is_channel"]
                                                        : !is_outgoing && currentMessageType != MessagingModel.SYSTEM_NEW_MESSAGE &&
                                                         currentMessageType != MessagingModel.JOINBYLINK &&
                                                         currentMessageType != MessagingModel.CONTACT_REGISTERED &&
                                                         currentMessageType != MessagingModel.CHAT_CREATED  &&
                                                         !messagingModel.chatType["is_channel"]  &&
                                                         messagingModel.chatType["type"] != TdlibState.Private &&
                                                         messagingModel.chatType["type"] != TdlibState.Secret
                    }
                }
            }


            Column {
                id: contentColumn
                Row {
                    id: subInfoRow
                    Label {
                        id: authorName
                        text: author ? author : ""
                        color: pressed ? Theme.highlightColor: Theme.secondaryHighlightColor
                        font.pixelSize: Theme.fontSizeExtraSmall
                        truncationMode: TruncationMode.Fade
                        visible: {
                            if(currentMessageType == MessagingModel.SYSTEM_NEW_MESSAGE ||
                                    currentMessageType == MessagingModel.JOINBYLINK ||
                                    currentMessageType == MessagingModel.CONTACT_REGISTERED ||
                                    currentMessageType == MessagingModel.CHAT_CREATED ) {
                                return false
                            }
                            else if(messagingModel.chatType["type"] == TdlibState.BasicGroup || (messagingModel.chatType["type"] == TdlibState.Supergroup && !messagingModel.chatType["is_channel"])) {
                                return true
                            }

                            return false
                        }
                    }
                }
                Row {
                    id: forwardRow
                    Label {
                        id: forwardInfoLabel
                        visible: forward_info ? true : false
                        text: forward_info ? qsTr("Forwarded from") + " " + forward_info : ""
                        width: contentLoader.width
                        color: pressed ? Theme.highlightColor: Theme.secondaryHighlightColor
                        font.pixelSize: Theme.fontSizeSmall
                        font.bold: true
                        truncationMode: TruncationMode.Fade
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    }
                }
                Loader {
                    id:replyLoader
                    active: reply_to_message_id != 0 && index != 0
                    sourceComponent: Component {
                        MouseArea {
                            id:replyBackgroundItem
                            height: replyRowWrapper.height
                            width: replyRowWrapper.width
                            onClicked: replyMessageClicked(index,reply_to_message_id)

                            Row {
                                id:replyRowWrapper
                                height: reply_to_message_id != 0 ? Theme.itemSizeExtraSmall : 0
                                visible: reply_to_message_id != 0
                                Rectangle {
                                    width:5
                                    height: parent.height
                                    color: Theme.highlightColor
                                }
                                Item {
                                    width:Theme.paddingMedium
                                    height: parent.height
                                }
                                Column {
                                    id:replyContentColumn
                                    Label {
                                        id:replyAuthorLabel
                                        color: Theme.secondaryHighlightColor
                                        font.pixelSize: Theme.fontSizeSmall
                                        text:reply_author ? reply_author : ""
                                        elide: Text.ElideRight

                                    }
                                    Label {
                                        id:replyTextLabel
                                        width: Math.min(implicitWidth,messageListItem.width *2/3)

                                        color: Theme.secondaryColor
                                        font.pixelSize: Theme.fontSizeTiny
                                        text:reply_message ? reply_message : ""
                                        maximumLineCount: 1
                                        elide: Text.ElideRight
                                    }
                                }

                            }
                        }
                    }
                }

                Loader {
                    id:contentLoader
                    function reload() {
                            source = ""
                            source = setItem()
                    }
                    function setItem() {
                        if (index == 0) {
                            return "delegates/TopMarginDelegate.qml"
                        }
                        if(currentMessageType == MessagingModel.TEXT) {
                            return "delegates/TextDelegate.qml"
                        }
                        else if(currentMessageType == MessagingModel.PHOTO) {
                            //                            var maxWidth = messageListItem.width-Theme.itemSizeExtraSmall - Theme.paddingMedium - 2*Theme.horizontalPageMargin
                            //                            var maxHeight = page.height/2
                            //                            width = photo_aspect >= 1 ? maxWidth : maxHeight * photo_aspect
                            //                            height = photo_aspect >= 1 ? maxWidth/photo_aspect : maxHeight
                            return "delegates/ImageDelegate.qml"
                        }
                        else if(currentMessageType == MessagingModel.VIDEO) {
                            //                            var maxWidth = messageListItem.width-Theme.itemSizeExtraSmall - Theme.paddingMedium - 2*Theme.horizontalPageMargin
                            //                            var maxHeight = page.height/2
                            //                            width = photo_aspect >= 1 ? maxWidth : maxHeight * photo_aspect
                            //                            height = photo_aspect >= 1 ? maxWidth/photo_aspect : maxHeight
                            return "delegates/VideoDelegate.qml"
                        }
                        else if(currentMessageType == MessagingModel.VIDEO_NOTE) {
                            return "delegates/VideoNoteDelegate.qml"
                        }
                        else if(currentMessageType == MessagingModel.STICKER) {
                            width = 400
                            height = width
                            return "delegates/StickerDelegate.qml"
                        }
                        else if(currentMessageType == MessagingModel.SYSTEM_NEW_MESSAGE) {
                            return "delegates/NewMessageDelegate.qml"
                        }
                        else if(currentMessageType == MessagingModel.DOCUMENT) {
                            return "delegates/DocumentDelegate.qml"
                        }
                        else if(currentMessageType == MessagingModel.ANIMATION) {
                            //                            var maxWidth = messageListItem.width-Theme.itemSizeExtraSmall - Theme.paddingMedium - 2*Theme.horizontalPageMargin
                            //                            var maxHeight = page.height/2
                            //                            width = photo_aspect > 1 ? maxWidth : maxHeight * photo_aspect
                            //                            height = photo_aspect > 1 ? maxWidth/photo_aspect : maxHeight
                            return "delegates/AnimationDelegate.qml"
                        }
                        else if(currentMessageType == MessagingModel.AUDIO) {
                            return "delegates/AudioDelegate.qml"
                        }
                        else if(currentMessageType == MessagingModel.VOICE) {
                            return "delegates/VoiceNoteDelegate.qml"
                        }
                        else if(currentMessageType == MessagingModel.CONTACT) {
                            return "delegates/ContactDelegate.qml"
                        }
                        else if(currentMessageType == MessagingModel.JOINBYLINK) {
                            return "delegates/JoinByLinkDelegate.qml"
                        }
                        else if(currentMessageType == MessagingModel.CONTACT_REGISTERED) {
                            return "delegates/JoinedDelegate.qml"
                        }
                        else if(currentMessageType == MessagingModel.CHAT_CREATED) {
                            return "delegates/ChatCreatedDelegate.qml"
                        }
                        return undefined
                    }
                    Component.onCompleted: {
                        setSource(setItem())
                    }
                }

                Row {
                    id: metaInfoRow
                    visible: currentMessageType !== MessagingModel.SYSTEM_NEW_MESSAGE &&
                             currentMessageType != MessagingModel.JOINBYLINK &&
                             currentMessageType != MessagingModel.CONTACT_REGISTERED &&
                             currentMessageType != MessagingModel.CHAT_CREATED

                    layoutDirection: is_outgoing ? Qt.RightToLeft : Qt.LeftToRight
                    spacing: Theme.paddingSmall
                    Label {
                        function timestamp(dateTime) {
                            var dateTimeDate=new Date(dateTime*1000)
                            return Format.formatDate(dateTimeDate, Formatter.TimeValue)
                        }
                        font.pixelSize: Theme.fontSizeTiny
                        color:pressed ? Theme.primaryColor : Theme.secondaryColor
                        text:edit_date ? qsTr("edited") + " " + timestamp(edit_date) : timestamp(date) + ' ' + index
                    }
                    Label {
                        font.pixelSize: Theme.fontSizeTiny
                        visible: sending_state === TdlibState.Sending_Pending || sending_state === TdlibState.Sending_Failed
                                 ||  messagingModel.chatType["type"] == TdlibState.Private || messagingModel.chatType["type"] == TdlibState.Secret
                        text: {
                            if(sending_state == TdlibState.Sending_Pending) {
                                return "<b>\u23F1</b>" // clock
                            }
                            else if(sending_state == TdlibState.Sending_Failed) {
                                return "<b>\u26A0</b>" // warning sign
                            }
                            else if(sending_state == TdlibState.Sending_Read) {
                                return "<b>\u2713\u2713</b>" // double check mark
                            }
                            else {
                                return "<b>\u2713</b>" // check mark
                            }
                        }
                    }
                }
            }


        }
//        Loader {
//            sourceComponent: Component {
//            }
//        }
    }
    ListView {
        id:inlineView
        anchors.top: columnWrapper.bottom
        visible:reply_markup && index != 0 ? true : false
        x:Theme.horizontalPageMargin
        width:parent.width - 2 * x
        height:reply_markup ? Theme.itemSizeMedium * reply_markup.length : 0
        model:reply_markup ? reply_markup.length : 0
        delegate: Item {
            width: parent.width
            height:Theme.itemSizeSmall
            SilicaGridView {
                id:cellsGrid
                width: parent.width
                cellWidth: parent.width / count
                cellHeight: Theme.itemSizeSmall

                height:Theme.itemSizeSmall
                model:reply_markup[index]
                delegate:           Button {
                    width: cellsGrid.cellWidth - Theme.paddingSmall * 2
                    height: cellsGrid.cellHeight
                    Label {
                        anchors.centerIn: parent
                        text:modelData.text
                        font.pixelSize: Theme.fontSizeSmall
                    }
                    onClicked: {
                        if(modelData.type["@type"] === "inlineKeyboardButtonTypeUrl") {
                            Qt.openUrlExternally(modelData.type["url"])
                        } else if (modelData.type["@type"] === "inlineKeyboardButtonTypeSwitchInline") {

                        } else
                            messagingModel.getCallbackQueryAnswerFunc(id,modelData.type["@type"],modelData.type["data"])
                    }
                }

            }
        }
    }

}
