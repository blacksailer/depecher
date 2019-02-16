import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import "../../items"
Page {
    id:root
    property string settingsUiPath:  "/apps/depecher/ui"
    property string settingsMessagePath:  "/apps/depecher/ui/message"
    ConfigurationValue {
        id:hideNameplate
        key:settingsUiPath + "/hideNameplate"
        defaultValue: false
    }
    ConfigurationValue {
        id:nightMode
        key:settingsUiPath + "/nightMode"
        defaultValue: false
    }
    ConfigurationValue {
        id:nightModeSchedule
        key:settingsUiPath + "/nightModeSchedule"
        defaultValue: false
    }
    ConfigurationValue {
        id:nightModeFrom
        key:settingsUiPath + "/nightModeFrom"
        defaultValue: "1900-01-01T22:00:00"
    }
    ConfigurationValue {
        id:nightModeTill
        key:settingsUiPath + "/nightModeTill"
        defaultValue: "1900-01-01T08:00:00"
    }
    SilicaFlickable {

        anchors.fill: parent
        contentHeight: content.height
        Column {
            id:content
            width:parent.width
            spacing: Theme.paddingSmall
            PageHeader {
                title: qsTr("Appearance")
            }
            ListModel {
                id:messagingModel
                property variant chatType: {type:TdlibState.BasicGroup}
                property string userName: "Pavel Nurov"
                property string action: "Pavel is typing"
                ListElement {
                }
                ListElement {
                    is_outgoing: false
                    author: "Pavel Nurov"
                    sender_photo:false
                    message_type:MessagingModel.TEXT
                    date:124532454
                    content:"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
                    sending_state:TdlibState.Sending_Pending
                    section:1533848400
                }
                ListElement {
                    is_outgoing: true
                    author: "Me"
                    sender_photo:false
                    message_type:MessagingModel.TEXT
                    date:124532484
                    content:"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
                    sending_state:TdlibState.Sending_Read
                    section:1533848400
                }
            }
            ConfigurationValue {
                id:radiusValue
                key:settingsMessagePath +"/radius"
                defaultValue: 0
            }
            ConfigurationValue {
                id:opacityValue
                key:settingsMessagePath +"/opacity"
                defaultValue: 0
            }
            ConfigurationValue {
                id:colorValue
                key:settingsMessagePath +"/color"
                defaultValue: 1//Theme.secondaryColor
            }
            ConfigurationValue {
                id:incomingColorValue
                key:settingsMessagePath +"/incomingColor"
                defaultValue: 5//Theme.highlightDimmerColor
            }
            ConfigurationValue {
                id:oneAligningValue
                key:settingsMessagePath +"/oneAlign"
                defaultValue: false//Theme.highlightDimmerColor
            }

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
                width: parent.width
                height: root.height/2 + Theme.itemSizeMedium - nameplate.height
                clip:true
                model:messagingModel
                topMargin:  -1 * Theme.itemSizeExtraLarge
                spacing: Theme.paddingSmall
                delegate: MessageItem {
}
                SilicaListView {
                    width: parent.width
                   height: root.height/2 + Theme.itemSizeMedium - nameplate.height
                    clip:true
                    model:messagingModel
                    topMargin:  -1 * Theme.itemSizeExtraLarge
                    spacing: Theme.paddingSmall
                    delegate: MessageItem {
                    }
                }


            Separator {
                width: parent.width
                color: Theme.secondaryColor
            }

            Slider {
                id:radiusSlider
                width: parent.width
                minimumValue: 0
                maximumValue: 90
                stepSize:1
                valueText: value
                label: qsTr("Radius")
                value: radiusValue.value
                onValueChanged: radiusValue.value = value
            }
            Slider {
                id:opacitySlider
                width: parent.width
                minimumValue: 0
                maximumValue: 1
                stepSize: 0.1
                value: opacityValue.value
                valueText: value.toFixed(1)
                label: qsTr("Opacity")
                onValueChanged: opacityValue.value = value
            }
            BackgroundItem {
                id: incomingColorPickerButton
                width: parent.width
                Row {
                    x: Theme.horizontalPageMargin
                    width: parent.width - 2*x
                    height: parent.height
                    spacing: Theme.paddingMedium
                    Rectangle {
                        id: incomingColorIndicator
                        width: height
                        height: parent.height
                        color: outcomingColorIndicator.getColor(incomingColorValue.value)
                    }
                    Label {
                        width: Math.min(paintedWidth,parent.width - incomingColorIndicator.width)
                        wrapMode: Text.WordWrap
                        text: qsTr("Incoming message background color")
                        font.pixelSize: Theme.fontSizeSmall
                        color: incomingColorPickerButton.down ? Theme.secondaryHighlightColor : Theme.secondaryColor
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
                onClicked: {
                    var page = pageStack.push("Sailfish.Silica.ColorPickerPage", { color: incomingColorIndicator.color,
                                                  colors:[Theme.primaryColor,Theme.secondaryColor,
                                                      Theme.highlightColor,Theme.highlightBackgroundColor,
                                                      Theme.secondaryHighlightColor,Theme.highlightDimmerColor]})
                    page.colorClicked.connect(function(color) {
                        switch(color) {
                        case Theme.primaryColor:
                            incomingColorValue.value = 0
                            break;
                        case Theme.secondaryColor:
                            incomingColorValue.value = 1
                            break;
                        case Theme.highlightColor:
                            incomingColorValue.value = 2
                            break;
                        case Theme.highlightBackgroundColor:
                            incomingColorValue.value = 3
                            break;
                        case Theme.secondaryHighlightColor:
                            incomingColorValue.value = 4
                            break;
                        case Theme.highlightDimmerColor:
                            incomingColorValue.value = 5
                            break;
                        default:
                            incomingColorValue.value = color
                            break;
                        }
                        pageStack.pop()
                    })
                }
            }

            BackgroundItem {
                id: outcomingColorPickerButton
                width: parent.width
                Row {
                    x: Theme.horizontalPageMargin
                    width: parent.width - 2*x
                    height: parent.height
                    spacing: Theme.paddingMedium
                    Rectangle {
                        id: outcomingColorIndicator
                        width: height
                        height: parent.height
                        color: getColor(colorValue.value)
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
                    Label {
                        width: Math.min(paintedWidth,parent.width - outcomingColorIndicator.width)
                        wrapMode: Text.WordWrap
                        text: qsTr("Outcoming message background color")
                        font.pixelSize: Theme.fontSizeSmall
                        color: outcomingColorPickerButton.down ? Theme.secondaryHighlightColor : Theme.secondaryColor
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
                onClicked: {
                    var page = pageStack.push("Sailfish.Silica.ColorPickerPage", { color: outcomingColorIndicator.color,
                                                  colors:[Theme.primaryColor,Theme.secondaryColor,
                                                      Theme.highlightColor,Theme.highlightBackgroundColor,
                                                      Theme.secondaryHighlightColor,Theme.highlightDimmerColor]
                                              })
                    page.colorClicked.connect(function(color) {
                        switch(color) {
                        case Theme.primaryColor:
                            colorValue.value = 0
                            break;
                        case Theme.secondaryColor:
                            colorValue.value = 1
                            break;
                        case Theme.highlightColor:
                            colorValue.value = 2
                            break;
                        case Theme.highlightBackgroundColor:
                            colorValue.value = 3
                            break;
                        case Theme.secondaryHighlightColor:
                            colorValue.value = 4
                            break;
                        case Theme.highlightDimmerColor:
                            colorValue.value = 5
                            break;
                        default:
                            colorValue.value = color
                            break;

                        }
                        pageStack.pop()
                    })
                }
            }

            TextSwitch {
                width: parent.width -2*x
                x:Theme.horizontalPageMargin
                checked: hideNameplate.value
                automaticCheck: false
                text: qsTr("Minimize nameplate")
                onClicked: {
                    hideNameplate.value = !checked
                    hideNameplate.sync()
                }
            }
            TextSwitch {
                width: parent.width -2*x
                x:Theme.horizontalPageMargin
                checked: oneAligningValue.value
                automaticCheck: false
                text: qsTr("Aways align messages to left")
                onClicked: {
                    oneAligningValue.value = !checked
                    oneAligningValue.sync()
                }
            }
            ExpandingSectionGroup {
                width: parent.width
                ExpandingSection {
                    id: section
                    width: parent.width -2*x
                    x:Theme.horizontalPageMargin
                    title: qsTr("Night Mode")

                    content.sourceComponent: Column {
                        width: section.width
                        TextSwitch {
                            width: parent.width
                            checked: nightMode.value
                            automaticCheck: false
                            enabled: !nightScheduleSwitch.checked
                            text: qsTr("Enable night mode")
                            onClicked: {
                                nightMode.value = !checked
                                nightMode.sync()
                            }
                        }
                        TextSwitch {
                            id:nightScheduleSwitch
                            width: parent.width
                            checked: nightModeSchedule.value
                            automaticCheck: false
                            text: qsTr("Enable schedule")
                            onClicked: {
                                nightModeSchedule.value = !checked
                                nightModeSchedule.sync()
                            }
                        }

                        Row {
                            width: section.width
                            ValueButton {
                                function openTimeDialog() {
                                    var dialog = pageStack.push("Sailfish.Silica.TimePickerDialog", {
                                                                    hourMode: DateTime.TwentyFourHours
                                                                })

                                    dialog.accepted.connect(function() {
                                        nightModeFrom.value = dialog.time
                                        nightModeFrom.sync()
                                    })
                                }

                                label: qsTr("From")
                                value: Format.formatDate(nightModeFrom.value, Formatter.TimeValue)
                                width: parent.width / 2
                                onClicked: openTimeDialog()
                            }
                            ValueButton {
                                function openTimeDialog() {
                                    var dialog = pageStack.push("Sailfish.Silica.TimePickerDialog", {
                                                                    hourMode: DateTime.TwentyFourHours
                                                                })

                                    dialog.accepted.connect(function() {
                                        nightModeTill.value = dialog.time
                                        nightModeTill.sync()
                                    })
                                }

                                label:qsTr("Till")
                                value: Format.formatDate(nightModeTill.value, Formatter.TimeValue)
                                width: parent.width / 2
                                onClicked: openTimeDialog()
                            }
                        }
                    }
                }
            }
            Button {
                width: Theme.buttonWidthMedium
                text:qsTr("Reset to default")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    radiusValue.value = radiusValue.defaultValue
                    opacityValue.value = opacityValue.defaultValue
                    colorValue.value = colorValue.defaultValue
                    incomingColorValue.value = incomingColorValue.defaultValue
                    hideNameplate.value = hideNameplate.defaultValue
                    nightModeTill.value = nightModeTill.defaultValue
                    nightModeFrom.value = nightModeFrom.defaultValue
                    nightMode.value = nightMode.defaultValue
                    nightModeSchedule.value = nightModeSchedule.defaultValue
                    radiusSlider.value = radiusValue.value
                    opacitySlider.value = opacityValue.value
                }
            }

        }
    }
    Component {
        id: colorPickerPage
        ColorPickerPage {}
    }
}
}
