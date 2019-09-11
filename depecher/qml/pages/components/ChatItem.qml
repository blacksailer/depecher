import QtQuick 2.0
import Sailfish.Silica 1.0
import tdlibQtEnums 1.0 //org.blacksailer.depecher.sharechat
import "../../js/utils.js" as Utils
import "../items"

ListItem {
    width:parent.width
    contentHeight: contentWrapper.height
    Item{
        id:contentWrapper
        x:Theme.horizontalPageMargin
        width:parent.width-2*x
        height:Theme.itemSizeMedium
        Row {
            width:parent.width
            height:parent.height - Theme.paddingMedium
            anchors.verticalCenter: parent.verticalCenter
            spacing:Theme.paddingMedium
            CircleImage {
                id: avatar
                width:height
                height: parent.height
                source: photo ? "image://depecherDb/"+photo : ""
                fallbackText: title.charAt(0)
                fallbackItemVisible: photo ? false : true
            }
            Column{
                //title,date,text
                //icon-m-speaker-mute
                width:parent.width-avatar.width-parent.spacing
                height: parent.height
                Row {
                    width:parent.width
                    height: parent.height/2
                    spacing: Theme.paddingSmall
                    Image {
                        id: iconGroup
                        source: type["is_channel"] ? "image://theme/icon-m-media-radio?" + (pressed
                                                                                                    ? Theme.highlightColor
                                                                                                    : Theme.primaryColor) :
                                                             type["type"] == TdlibState.Supergroup || type["type"] == TdlibState.BasicGroup ? "image://theme/icon-s-group-chat?"+ (pressed
                                                                                                                                                                   ? Theme.highlightColor
                                                                                                                                                                   : Theme.primaryColor) :
                                                                                                                              type["type"] == TdlibState.Secret ? "image://theme/icon-s-secure?"+ (pressed
                                                                                                                                                                                           ? Theme.highlightColor
                                                                                                                                                                                           : Theme.primaryColor) :
                                                                                                                                                          ""
                        anchors.verticalCenter: parent.verticalCenter
                        height: parent.height
                        width: source == "" ? 0 : implicitWidth
                        fillMode: Image.PreserveAspectFit
                    }
                    Row {
                        width:parent.width - iconGroup.width - messageTimestamp.width - parent.spacing
                        height:parent.height
                        Label {
                            //title
                            anchors.verticalCenter: parent.verticalCenter
                            width: Math.min(implicitWidth,parent.width - iconMute.width)
                            color: pressed?Theme.secondaryHighlightColor:Theme.highlightColor
                            font.pixelSize: Theme.fontSizeSmall
                            text:title
                            truncationMode: TruncationMode.Fade
                        }
                        Image {
                            id: iconSponsored
                            source: mute_for > 0  ? "image://theme/icon-m-favorite?"
                                                    + (pressed
                                                       ? Theme.secondaryHighlightColor
                                                       : "gray") :
                                                    ""
                            visible: is_sponsored
                            height: Theme.fontSizeSmall
                            anchors.verticalCenter: parent.verticalCenter
                            width: visible ? implicitWidth : 0
                            fillMode: Image.PreserveAspectFit
                        }
                        Image {
                            id: iconMute
                            source: mute_for > 0  ? "image://theme/icon-m-speaker-mute?"
                                                    + (pressed
                                                       ? Theme.secondaryHighlightColor
                                                       : "gray") :
                                                    ""
                            visible: mute_for > 0
                            height: Theme.fontSizeSmall
                            anchors.verticalCenter: parent.verticalCenter
                            width: visible ? implicitWidth : 0
                            fillMode: Image.PreserveAspectFit
                        }
                    }
                    Label{
                        id:messageTimestamp
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        font.pixelSize: Theme.fontSizeSmall
                        color: pressed ? Theme.secondaryHighlightColor : Theme.secondaryColor
                        text: Utils.formatDate(date, false)
                    }
                }
                Row {
                    width:parent.width
                    height: parent.height/2
                    spacing: Theme.paddingSmall
                    Label {
                        id:lastMessageAuthor
                        anchors.verticalCenter: parent.verticalCenter
                        color:pressed ? Theme.highlightColor : Theme.secondaryHighlightColor
                        text: last_message_author+":"
                        font.pixelSize: Theme.fontSizeExtraSmall
                        visible: action ? false : type == TdlibState.BasicGroup || type==TdlibState.Supergroup ? true : false
                        width: visible ? implicitWidth : 0
                    }
                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        width:lastMessageAuthor.width == 0 ?parent.width - mentions.width  : parent.width  - lastMessageAuthor.width - mentions.width  - parent.spacing
                        text:action ?  action : last_message ? last_message : ""
                        font.pixelSize: Theme.fontSizeExtraSmall
                        maximumLineCount: 1
                        truncationMode:TruncationMode.Fade
                        color: action  ? Theme.secondaryColor :
                                         pressed ?
                                             Theme.highlightColor : Theme.primaryColor

                    }
                    Row{
                        id: mentions
                        height: parent.height
                        spacing: Theme.paddingSmall
                        Label {
                            font.pixelSize: Theme.fontSizeTiny
                            width: visible ? implicitWidth : 0
                            color:pressed ? Theme.secondaryHighlightColor : Theme.secondaryColor
                            visible: !(type["type"] == TdlibState.Supergroup && type["is_channel"])
                            anchors.verticalCenter: counterWrapper.verticalCenter
                            text: {
                                if(sending_state === TdlibState.Sending_Pending) {
                                    return "<b>\u23F1</b>" // clock
                                }
                                else if(sending_state === TdlibState.Sending_Failed) {
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

                        Image {
                            id: iconPinned
                            source: is_pinned ? "image://theme/icon-s-task?"+ (pressed
                                                                               ? Theme.highlightColor
                                                                               : Theme.primaryColor) :
                                                ""
                            visible: unread_count == 0
                            width: visible ? implicitWidth : 0
                            fillMode: Image.PreserveAspectFit
                        }
                        Rectangle{
                            id:mentionWrapper
                            color: pressed ? Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity*2) : Theme.highlightBackgroundColor
                            radius: 90
                            width: visible ? Math.max(50,mention.width+Theme.paddingSmall*2) : 0
                            height: parent.height
                            visible: unread_mention_count > 0 ? true : false
                            Label{
                                id:mention
                                text:"@"
                                anchors.centerIn: parent
                                font.pixelSize: Theme.fontSizeTiny
                                color: Theme.primaryColor
                            }
                        }
                        Rectangle{
                            id:counterWrapper
                            property bool muted: mute_for > 0
                            color: pressed ? Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity*2) : backgroundColor
                            property color backgroundColor: muted ? Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity) :Theme.highlightBackgroundColor
                            radius: 90

                            width: visible ? Math.max(50,counter.width+Theme.paddingSmall*2) : 0
                            height: parent.height
                            visible: unread_count > 0 || is_marked_unread
                            Label{
                                id:counter
                                text:is_marked_unread ? "" : unread_count
                                anchors.centerIn: parent
                                font.pixelSize: Theme.fontSizeTiny
                                color: Theme.primaryColor
                            }
                        }
                    }

                }

            }
        }
    }
}

