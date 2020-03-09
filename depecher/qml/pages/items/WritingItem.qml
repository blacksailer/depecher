import QtQuick 2.0
import QtQml 2.2
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0
import QtGraphicalEffects 1.0
import depecherUtils 1.0
import TelegramModels 1.0
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
    property alias chatMembersList: chatMembersList
    property string reply_id: "0"
    property string edit_message_id: "0"

    property string typeWriter
    signal sendVoice(var location,var duration, var waveform)
    signal sendFiles(var files)
    signal setFocusToEdit()
    signal replyAreaCleared()

    property string settingsUiPath:  "/apps/depecher/ui"
    property string settingsBehaviorPath:  "/apps/depecher/behavior"
    ConfigurationValue {
        id:sendByEnter
        key:settingsBehaviorPath +"/sendByEnter"
        defaultValue: false
    }

    ConfigurationValue {
        id: showVoiceMessageButton
        key: settingsUiPath + "/showVoiceMessageButton"
        defaultValue: true
    }

    ConfigurationValue {
        id:showCurrentTimeLabel
        key:settingsUiPath + "/showCurrentTimeLabel"
        defaultValue: true
        onValueChanged: {
            if (value) {
                var date = new Date()
                labelTime.text =  Format.formatDate(date, Formatter.TimeValue)
            }
        }
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
    backgroundSize: isPortrait ? height/2 : height * 2/3

    Item {
        id: sendArea
        anchors.bottom: parent.bottom
        z:1
        width: parent.width
        height: chatMembersList.height + replyArea.height + messageArea.height + returnButton.height + labelTime.height + labelTime.anchors.bottomMargin + Theme.paddingSmall

        Rectangle {
            width: parent.width
            height: chatMembersList.height
            color: Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity)
            opacity: chatMembersList.opacity
        }
        SilicaListView {
            id: chatMembersList
            width: parent.width
            height: opacity ? Math.min(3, count)*Theme.itemSizeExtraSmall : 0
            opacity: 0
            clip: true
            currentIndex: -1
            focus: false
            highlightRangeMode: ListView.ApplyRange

            // currentIndex is invalid after EnterKey is clicked
            property int sourceIndex: -1

            onCurrentIndexChanged: {
                if (currentIndex != -1)
                    sourceIndex = filterChatMembersModel.sourceIndex(currentIndex)
            }

            onCountChanged: {
                if (count != 0)
                    sourceIndex = filterChatMembersModel.sourceIndex(currentIndex)
            }

            Behavior on height { NumberAnimation { duration: 150} }

            delegate: BackgroundItem {
                width: chatMembersList.width
                height: Theme.itemSizeExtraSmall
                highlighted: index == chatMembersList.currentIndex
                Row {
                    width: parent.width - 2 * x
                    height: parent.height
                    anchors.verticalCenter: parent.verticalCenter
                    x: Theme.horizontalPageMargin
                    Item {
                        height: parent.height
                        width: height
                        CircleImage {
                            id:userPhoto
                            source: avatar ? avatar : ""
                            fallbackItemVisible: avatar == undefined
                            fallbackText:name.charAt(0)
                            anchors.centerIn: parent
                        }
                    }

                    Item {
                        width: Theme.paddingLarge
                        height: Theme.paddingLarge
                    }
                    Label {
                        property string mText: name + (username ? " @" + username : "")
                        text: textArea.text.length ?
                                  Theme.highlightText(mText, filterChatMembersModel.search, Theme.highlightColor) : mText
                        font.pixelSize: Theme.fontSizeSmall
                        color: Theme.primaryColor
                        width: parent.width - userPhoto.width
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
                onClicked: {
                    delegateTimer.start()
                    if (model.username.length)
                        textArea.text = "@" + model.username + " "
                    else
                        textArea.text = model.name + " "
                }
            }
            VerticalScrollDecorator {
                flickable: chatMembersList
            }

            Timer {
                id: delegateTimer
                interval: 0
                onTriggered: {
                    textArea.cursorPosition = textArea.text.length
                    restoreFocusTimer.start()
                }
            }
        }


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
            anchors.bottom: row.top
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
            anchors.bottom: labelTime.top
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

                    anchors.bottom: parent.bottom

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
                    anchors.bottom: parent.bottom

                }
                TextArea {
                    id: messageArea
                    onTextChanged: {
                        if (filterChatMembersModel && text.indexOf("@") == 0 && text.indexOf(" ") < 0) {
                            state = "searchMember"
                        } else if (text === "") {
                            state ="text"
                            messageArea.forceActiveFocus()
                        } else if(text != "") {
                            state ="typing"
                        }
                    }

                    height: Math.min(Theme.itemSizeHuge ,implicitHeight)
                    font.pixelSize: Theme.fontSizeMedium
                    //Hiding last line of text. Bug of Silica?
                    labelVisible: false

                    Component.onCompleted: {
                        if (showCurrentTimeLabel.value) {
                            var date = new Date()
                            labelTime.text =  Format.formatDate(date, Formatter.TimeValue)
                        }
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
                                visible: showVoiceMessageButton.value && reply_id != "-1"
                                y:stickerButton.y
                            }
                            PropertyChanges {
                                target:sendButton
                                visible: reply_id == "-1"
                            }
                        },
                        State {
                            name:"typing"
                            PropertyChanges {
                                target:messageArea
                                width :row.width - sendButton.width - stickerButton.width
                                opacity:1
                            }
                            PropertyChanges {
                                target:stickerButton
                                visible:true
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
                                width: row.width
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
                                visible:false
                            }
                            PropertyChanges {
                                target:labelTime
                                x: Theme.horizontalPageMargin
                            }
                        },
                        State  {
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
                                width: row.width
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

                        },
                        State  {
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
                        },
                        State {
                            name: "searchMember"
                            extend: "typing"
                            PropertyChanges {
                                target: filterChatMembersModel
                                search: text.substr(1)
                            }
                            PropertyChanges {
                                target: chatMembersList
                                model: filterChatMembersModel
                            }
                            PropertyChanges {
                                target: chatMembersList
                                opacity: 1
                            }
                            PropertyChanges {
                                target: chatMembersList
                                currentIndex: 0
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
                            NumberAnimation  {
                                target: labelTime
                                properties :"x"
                                duration :200
                            }
                        },
                        Transition {
                            from: "*"
                            to: "searchMember"
                            reversible: true
                            NumberAnimation {
                                target: chatMembersList
                                properties: "opacity"
                                duration: 150
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
                anchors.bottom: parent.bottom
            }
        }
        Label {
            id:labelTime
            property int leftMarginOne: stickerButton.visible ? stickerButton.width : 0
            property int leftMarginTwo: skrepkaWizard.visible ? skrepkaWizard.width : 0
            font: Theme.fontSizeTiny

            x: leftMarginTwo + leftMarginOne + Theme.horizontalPageMargin
            anchors.leftMargin: Theme.horizontalPageMargin
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Theme.paddingMedium
            visible: showCurrentTimeLabel.value && messageArea.visible
            height: visible ? undefined : 0
            Timer {
                interval: 60*1000
                repeat: true
                running: showCurrentTimeLabel.value
                onTriggered: {
                    var date = new Date()
                    labelTime.text =  Format.formatDate(date, Formatter.TimeValue)
                }
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
