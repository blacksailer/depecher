import QtQuick 2.0
import QtQml 2.2
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0
import QtGraphicalEffects 1.0
import depecherUtils 1.0
import QtMultimedia 5.6

Drawer {
    id: attachDrawer
    state: "publish"
    property Page rootPage
    //    property var audioRec: null
    property alias sendAreaHeight: sendArea.height
    property alias bottomArea: sendArea
    property alias actionButton: sendButton
    property alias text: messageArea.text
    property alias textArea:messageArea
    property alias replyMessageAuthor: authorsLabel.text
    property alias replyMessageText: authorsTextLabel.text
    property alias returnButtonItem: returnButton
    property alias returnButtonEnabled: returnButton.enabled
    property string reply_id: "0"
    property string edit_message_id: "0"

    property string typeWriter
    signal sendVoice(var location,var duration, var waveform)
    signal sendFiles(var files)
    signal setFocusToEdit()
    signal replyAreaCleared()

    property string settingsBehaviorPath:  "/apps/depecher/behavior"
    ConfigurationValue {
        id:sendByEnter
        key:settingsBehaviorPath +"/sendByEnter"
        defaultValue: false
    }
    function clearReplyArea() {
        if(attachDrawer.state == "editText" || attachDrawer.state == "editCaption") {
            messageArea.text = ""
            attachDrawer.state = "publish"
        }

        edit_message_id =  "0"
        replyMessageAuthor = ""
        replyMessageText = ""
        reply_id = "0"
        if(attachDrawer.state=="edit")
            attachDrawer.state = "publish"

    }
    onSetFocusToEdit: messageArea.focus = true

    states: [
        State {
            name:"editText"
            PropertyChanges {
                target: attachDrawer
                replyMessageAuthor: qsTr("Edit text")
            }
        },
        State {
            name: "editCaption"
            PropertyChanges {
                target: attachDrawer
                replyMessageAuthor: qsTr("Edit caption")
            }
        },
        State{
            name:"publish"
        },
        State{
            name:"edit"
        }
    ]

    open: false
    dock: Dock.Bottom
    anchors.fill: parent

    Item {
        id: sendArea
        anchors.bottom: parent.bottom
        z:1
        width: parent.width
        height: replyArea.height + messageArea.height + returnButton.height + Theme.paddingSmall

        BackgroundItem {
            id:returnButton
            width: parent.width
            height: enabled ? Theme.paddingLarge + Theme.paddingMedium : 0
            anchors.bottom: replyArea.top
            enabled: false
            visible: enabled
            Rectangle {
                anchors.fill: parent
                color: Theme.highlightColor
            }
            Image {
                source: "image://theme/icon-s-low-importance"
                anchors.centerIn: parent
            }
        }
        Item {
            id: replyArea
            width: parent.width
            height: reply_id != "0" ||  edit_message_id != "0"  ? Theme.itemSizeExtraSmall : 0
            anchors.bottom: messageArea.top
            Row {
                width: parent.width
                height:parent.height
                spacing: Theme.paddingSmall
                IconButton{
                    id: removeReplyButton
                    icon.source: "image://theme/icon-s-clear-opaque-cross?"+Theme.highlightColor
                    visible: parent.height!=0
                    onClicked: {
                        clearReplyArea()
                        replyAreaCleared()
                    }
                }

                Rectangle {
                    id: replyLine
                    width: 3
                    height: parent.height
                    color: Theme.secondaryHighlightColor
                }
Item {
    width: 1
    height:parent.height
}
                Column {
                    id: data
                    width: parent.width - replyLine.width - removeReplyButton.width - 2 * parent.spacing - Theme.horizontalPageMargin
                    height:parent.height
                    Label {
                        id: authorsLabel
                        font.pixelSize: Theme.fontSizeExtraSmall
                        width: parent.width
                        elide: TruncationMode.Fade
                        height: authorsTextLabel.text == "" ? removeReplyButton.height : implicitHeight
                    }
                    Label {
                        id: authorsTextLabel
                        font.pixelSize: Theme.fontSizeExtraSmall
                        width: parent.width
                        maximumLineCount: 1
                        elide: TruncationMode.Fade
                        visible: authorsText != ""
                    }
                }


            }
        }
        Row {
            id:row
            width:parent.width
            height: messageArea.height
            anchors.bottom: parent.bottom
            Row  {
                id:rowArea
                height: messageArea.height
                width: row.width - mic.width - sendButton.width
                IconButton {
                    id: skrepkaWizard
                    icon.source: "image://theme/icon-m-attach"
                    width: visible ? stickerButton.width : 0
                    highlighted: false
                    onClicked: {
                        attachLoader.setSource("AttachComponent.qml")
                        attachDrawer.open=true
                    }
                    visible: messageArea.text.length == 0


                }
                IconButton {
                    id:stickerButton
                    icon.source: "image://theme/icon-m-other"
                    highlighted: false
                    onClicked: {
                        if(!attachDrawer.opened)
                            attachLoader.setSource("AttachSticker.qml",{previewView:foregroundItem,rootPage:rootPage})
                        attachDrawer.open=!attachDrawer.open
                    }
                }
                TextArea {
                    id: messageArea
                    onTextChanged: {
                        if(text === "")
{
                              state ="text"
                            messageArea.forceActiveFocus()
}
                        if(text != "")
                            state ="typing"
                    }
                    height:  Math.min(Theme.itemSizeHuge,implicitHeight)
                    _labelItem.opacity: 1
                    _labelItem.font.pixelSize: Theme.fontSizeTiny

                    Timer {
                        interval: 60*1000
                        repeat: true
                        running: true
                        onTriggered: {
                            var date = new Date()
                            messageArea.label =  Format.formatDate(date, Formatter.TimeValue)
                        }
                    }

                    Component.onCompleted: {
                        var date = new Date()
                        label =  Format.formatDate(date, Formatter.TimeValue)
                    }
                    state:"text"
                    states:[
                        State {
                            name:"text"
                            PropertyChanges {
                                target:messageArea
                                width :rowArea.width - skrepkaWizard.width - stickerButton.width
                                opacity:1
                            }
                            PropertyChanges {
                                target:stickerButton
                                visible:true
                            }
                            PropertyChanges {
                                target:skrepkaWizard
                                visible:true
                            }
                            PropertyChanges {
                                target:mic
                                visible:true
                            }
                            PropertyChanges {
                                target:sendButton
                                visible:!sendByEnter.value || reply_id == "-1"
                            }
                        },
                        State {
                            name:"typing"
                            PropertyChanges {
                                target:messageArea
                                width :row.width - sendButton.width
                                opacity:1
                            }
                            PropertyChanges {
                                target:stickerButton
                                visible:false
                            }
                            PropertyChanges {
                                target:skrepkaWizard
                                visible:false
                            }
                            PropertyChanges {
                                target:mic
                                visible:false
                            }
                            PropertyChanges {
                                target:sendButton
                                visible:!sendByEnter.value || reply_id == "-1"
                            }
                        },
                        State  {
                            name:"voice"
                            PropertyChanges {
                                target:rowArea
                                width:0
                                opacity:0
                            }
                            PropertyChanges {
                                target:mic
                                width: row.width  - sendButton.width
                            }
                            PropertyChanges {
                                target:stickerButton
                                visible:false
                            }
                            PropertyChanges {
                                target:skrepkaWizard
                                visible:false
                            }
                            PropertyChanges {
                                target:mic
                                visible:true
                            }

                            PropertyChanges {
                                target:sendButton
                                visible:!sendByEnter.value || reply_id == "-1"
                            }

                        }, State  {
                            name:"voice-fixed"
                            PropertyChanges {
                                target:rowArea
                                width:0
                                opacity:0
                            }
                            PropertyChanges {
                                target:mic
                                visible:true
                            }

                            PropertyChanges {
                                target:mic
                                width: row.width  - sendButton.width
                            }
                            PropertyChanges {
                                target:stickerButton
                                visible:false
                            }
                            PropertyChanges {
                                target:skrepkaWizard
                                visible:false
                            }
                            PropertyChanges {
                                target:sendButton
                                visible:false
                            }

                        },  State  {
                            name:"voice-validation"
                            PropertyChanges {
                                target:mic
                                width: row.width  - sendButton.width
                            }
                            PropertyChanges {
                                target:rowArea
                                width:0
                                opacity:0
                            }
                            PropertyChanges {
                                target:stickerButton
                                visible:false
                            }
                            PropertyChanges {
                                target:mic
                                visible:true
                            }

                            PropertyChanges {
                                target:skrepkaWizard
                                visible:false
                            }
                            PropertyChanges {
                                target:sendButton
                                visible:false
                            }
                        }
                    ]
                    transitions: [
                        Transition {
                            from:"text"
                            to:"voice"
                            NumberAnimation {
                                target:rowArea
                                properties:"width"
                                duration:200
                            }
                            NumberAnimation  {
                                target: mic
                                properties :"width"
                                duration :200
                            }
                        }
                    ]
                }
            }
            VoiceButton {
            id:mic
            height: rowArea.height
            width: visible ? buttonWidth : 0
            onStateChanged: {
            if(state == "default")
                messageArea.state = "text"
             else if (state == "voice-validation")
                messageArea.state = "voice-validation"
             else if (state == "fixed")
                messageArea.state = "voice-fixed"
             else
                messageArea.state = "voice"
            }
            }
            IconButton {
                id: sendButton
                icon.source: "image://theme/icon-m-message"
                highlighted: false
                width: visible ? Theme.itemSizeMedium : 0
                visible: !sendByEnter.value || reply_id == "-1"
            }
        }
    }

    MouseArea {
        enabled: attachDrawer.open
        anchors.fill: parent
        z:10
        onClicked: attachDrawer.open = false
    }

    Connections {
        target: attachLoader.item
        onSendUrlItems: sendFiles(items)

    }

    background: Loader {
        id: attachLoader
        anchors.fill: parent
    }
    onOpenedChanged:
        if(!opened)
            attachLoader.sourceComponent=undefined
}
