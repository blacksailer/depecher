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
        signal sendVoice(var location,var duration)
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
            Rectangle {
                id: replyLine
                width: 3
                height: parent.height
                color: Theme.secondaryHighlightColor
                anchors.left: parent.left
                anchors.leftMargin: 8
            }

            Column {
                id: data
                anchors.left: replyLine.right
                anchors.leftMargin: Theme.paddingLarge
                anchors.right: removeReplyButton.left

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

            IconButton{
                id: removeReplyButton
                icon.source: "image://theme/icon-s-clear-opaque-cross?"+Theme.highlightColor
                anchors.right: parent.right
                anchors.rightMargin: Theme.paddingLarge
                visible: parent.height!=0
                onClicked: {
                    clearReplyArea()
                    replyAreaCleared()
                }
            }
        }
        Row {
            id:row
            width:parent.width
            height: messageArea.height
            anchors.bottom: parent.bottom
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
                        messageArea.forceActiveFocus()
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
                state:"text"
                states:[
                    State {
                        name:"text"
                        PropertyChanges {
                            target:messageArea
                            width :row.width - skrepkaWizard.width - stickerButton.width - mic.width - sendButton.width
                            opacity:1
                        }

                        PropertyChanges {
                            target:voiceLabel
                            width:0
                        }

                        PropertyChanges {
                            target:recordButton
                            source:  "image://theme/icon-m-mic"
                        }
                    },   State  {
                        name:"voice"
                        PropertyChanges {
                            target:messageArea
                            width:0
                            opacity:0
                        }
                        PropertyChanges {
                            target:voiceLabel
                            width: row.width - skrepkaWizard.width - stickerButton.width - mic.width - sendButton.width
                        }
                    },  State  {
                        name:"voice-validation"
                        PropertyChanges {
                            target:voiceLabel
                            width: row.width - skrepkaWizard.width - stickerButton.width - mic.width - sendButton.width
                        }
                        PropertyChanges {
                            target:messageArea
                            width:0
                            opacity:0
                        }
                        PropertyChanges {
                            target:recordButton
                            source:"image://theme/icon-m-message"
                        }
                    }
                ]
                transitions: [
                    Transition {
                        from:"text"
                        to:"voice"
                        NumberAnimation {
                            target:messageArea
                            properties:"width"
                            duration:200
                        }
                        NumberAnimation  {
                            target: voiceLabel
                            properties :"width"
                            duration :200
                        }
                    }
                ]
                Component.onCompleted: {
                    var date = new Date()
                    label =  Format.formatDate(date, Formatter.TimeValue)
                }
            }
            Item {
                id:voiceLabel
                property int secondsElapsed: 0
                height:parent.height
                width:0
                Row {
                    width: parent.width
                    anchors.bottom: stickerButton.bottom
                    visible: voiceLabel.width > 0
                    Image {
                        anchors.baseline: parent.baseline
                        visible: voiceLabel.width > 0
                        source:"image://theme/icon-m-call-recording-on-light" //+ voiceLabel.width > 0 ? "icon-m-call-recording-on-dark" : "icon-m-call-recording-on-light"
                    }
                    IconButton {
                        anchors.baseline: parent.baseline
                        visible: attachDrawer.state == 'voice-validation'
                        icon.source:"image://theme/icon-m-play"
                        onClicked:{
                            playMusic.source = audioRec.location
                            playMusic.play()
                        }
                    }
                    Label {
                        anchors.verticalCenter:  parent.verticalCenter
                        color: Theme.highlightColor
                        text: attachDrawer.state == 'voice-validation' && playMusic.state == Audio.playingState ?
                                  Format.formatDuration(playMusic.position / 1000,Formatter.DurationElapsedShort)  +
                                  "/" + Format.formatDuration(audioRec.duration / 1000,Formatter.DurationElapsedShort)
                                : Format.formatDuration(audioRec.duration / 1000,Formatter.DurationElapsedShort)
                    }
                    Label {
                        id:log
                        anchors.verticalCenter:  parent.verticalCenter
                        color: Theme.highlightColor
                        text:audioRec.actualLocation
                    }
                }

                AudioRecorder {
                    id:audioRec
                    onError: console.log("Recording error -" + error)
                }
            }
            Item{
                id:mic
                width:Theme.itemSizeSmall
                height:row.height - Theme.paddingMedium


                Image {
                    id:recordButton
                    source:  "image://theme/icon-m-mic"
                    z:2
                    state:"default"
                    states :[
                        State {
                            name:"default"
                            PropertyChanges {
                                target : recordButton
                                y:0
                            }
                            PropertyChanges {
                                target: recordButton
                                source: "image://theme/icon-m-mic"
                            }
                        },
                        State {
                            name:"moving"
                        },
                        State {
                            name :"fixed"
                            PropertyChanges {
                                target: recordButton
                                source: "image://theme/icon-m-acknowledge"
                                y:0
                            }
                        } ,     State {
                            name :"voice-validation"
                            PropertyChanges {
                                target: recordButton
                                source:"image://theme/icon-m-message"
                                y:0
                            }
                        }
                    ]
                    MouseArea {
                    anchors.fill: parent
                    enabled:  parent.state == "fixed" ||  parent.state == "voice-validation"
                    onClicked: {
                        if(parent.state == "voice-validation")
                        {
                            stick.state = "preparing"
                            recordButton.state = "default"
                        } else {
                        stick.state = "preparing"
                        recordButton.state = "default"
                        audioRec.stopRecording()
                        }
sendVoice(audioRec.location,audioRec.duration/1000)
                    }
                    }



                }
                anchors.rightMargin: Theme.horizontalPageMargin
                Rectangle {
                    width: 46
                    height:Theme.itemSizeSmall
                    radius: 90
                    color: Theme.secondaryColor
                    z:0
                    anchors.fill:lock
                    visible: recordButton.state == "moving"
                }
                Image {
                    id:lock
                    source :recordButton.state == "fixed" ? "image://theme/icon-m-pause?"+Theme.primaryColor : "qrc:/qml/assets/icons/lock_slide_40x80.png"
                    z:1
                    anchors.horizontalCenter: recordButton.horizontalCenter
                    anchors.bottom: recordButton.top
                    visible: recordButton.state != "default" && recordButton.state != "voice-validation"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            audioRec.stopRecording()
                            stick.state = "voice-validation"
                        }
                        enabled:  recordButton.state == "fixed"
                    }
                }
                Item {
                    id:stick
                    MouseArea {
                        anchors.fill:stick
                        enabled: recordButton.state != "fixed" && recordButton.state != "voice-validation"
                        preventStealing:true
                        onPressed:  {
                            stick.state = "ready"
                            audioRec.startRecording()
                        }
                        onPositionChanged: {
                            if(stick.state =="ready") {
                                if(mouse.y >= 0  && mouse.y < height )  {
                                    if (mouse.y < recordButton.height / 2)
                                    {
                                        recordButton.state = "fixed"
                                    }

                                    else if (mouse.y > height - recordButton.height )
                                        recordButton.state = "default"
                                    else
                                    {
                                        recordButton.state = "moving"
                                        recordButton.y  =  mouse.y - height  + recordButton.height
                                    }

                                }

                            }
                        }
                        onReleased:{
                            console.log("released")
                            if (recordButton.state == "moving")
                            {
                                audioRec.stopRecording()
                                stick.state = "preparing"
                                recordButton.state = "default"
                            }
                        }
                    }
                    transitions:[
                        Transition {
                            from:"preparing"
                            to:"ready"
                            NumberAnimation {

                                target:stick
                                properties:"opacity"
                                duration:200
                            }

                        },Transition {
                            from:"ready"
                            to:"preparing"
                            NumberAnimation {
                                target:stick
                                properties:"opacity"
                                duration:200
                            }
                        }
                    ]
                    states: [
                        State {
                            name:"preparing"
                            PropertyChanges {
                                target:stick
                                opacity : 0
                            }
                            PropertyChanges {
                                target : messageArea
                                state: "text"
                            }
                        },
                        State {
                            name:"ready"
                            PropertyChanges {
                                target:stick
                                opacity:1
                            }
                            PropertyChanges {
                                target : messageArea
                                state: "voice"
                            }
                        },
                        State {
                            name:"voice-validation"
                            PropertyChanges {
                                target:stick
                                opacity : 0
                            }
                            PropertyChanges {
                                target : recordButton
                                state: "voice-validation"
                            }
                            PropertyChanges {
                                target : messageArea
                                state: "voice-validation"
                            }
                        }
                    ]
                    width: recordButton.width
                    height: row.height * 2
                    state:"preparing"
                    anchors.bottom:parent.bottom
                }

            }
            IconButton {
                id: sendButton
                icon.source: "image://theme/icon-m-message"
                highlighted: false
                width: visible ? implicitWidth : 0
                visible: !sendByEnter.value || reply_id == "-1"
            }
        }
    }

    MouseArea {
        enabled: attachDrawer.open
        anchors.fill: parent
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
