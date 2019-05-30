import QtQuick 2.0
import Sailfish.Silica 1.0
import depecherUtils 1.0
import QtMultimedia 5.6

Item {
    id:rootItem
    width: buttonWidth
    property alias buttonWidth: mic.width
    height: Theme.itemSizeSmall
    state:"default"
    states: [
    State {
        name:"default"
        PropertyChanges {
                target : recordButton
                source: "image://theme/icon-m-mic"
                x:0
            }
            PropertyChanges {
                target:stick
                opacity : 0
            }
            PropertyChanges {
                target:voiceLabel
                opacity : 0
            }
        },
    State {
        name:"pressed"
        PropertyChanges {
            target : recordButton
            source: "image://theme/icon-m-mic"
        }
        PropertyChanges {
            target:stick
            opacity:1
        }
        PropertyChanges {
            target:voiceLabel
            opacity : 1
        }
      },
    State {
        name:"moving"
        PropertyChanges {
            target : recordButton
            source: "image://theme/icon-m-mic"
        }
        PropertyChanges {
            target:stick
            opacity:1
        }
      },
    State {
        name:"fixed"
        PropertyChanges {
            target: recordButton
            source: "image://theme/icon-m-acknowledge"
            x: 0

        }
        PropertyChanges {
            target:stick
            opacity: 0
        }
     },
    State {
        name:"voice-validation"
        PropertyChanges {
            target: recordButton
            source:"image://theme/icon-m-message"
            x: 0
        }
        PropertyChanges {
            target:stick
            opacity:1
        }
    }
    ]
    transitions:[
        Transition {
            from:"default"
            to:"pressed"
            NumberAnimation {
                target:stick
                properties:"opacity"
                duration:300
            }
            NumberAnimation {
                target:voiceLabel
                properties:"opacity"
                duration:300
            }
            onRunningChanged: {
                if ((rootItem.state == "pressed" || rootItem.state == "moving") && (!running))
                {
                    audioRec.startRecording()
                }
            }

        },Transition {
            from:"*"
            to:"default"
            NumberAnimation {
                target:stick
                properties:"opacity"
                duration:300
            }
        }
    ]
Row {
    width: parent.width
    height:parent.height

    Item {
        id:voiceLabel
        property int secondsElapsed: 0
        height:parent.height
        width:rootItem.width == buttonWidth ? 0  : rootItem.width - mic.width - Theme.horizontalPageMargin
        Row {
            width: parent.width
            anchors.bottom: rootItem.bottom
            visible: voiceLabel.width > 0
            Item {
            width: Theme.horizontalPageMargin
            height: 1
            }
            IconButton {
                id:clearButton
                anchors.baseline: parent.baseline
                width: recordButton.width
                height: recordButton.height
                visible: voiceLabel.width > 0
                icon.source:rootItem.state == 'voice-validation' ? "image://theme/icon-m-clear" : "image://theme/icon-m-call-recording-on-light" //+ voiceLabel.width > 0 ? "icon-m-call-recording-on-dark" : "icon-m-call-recording-on-light"
                onClicked:{
                    if(rootItem.state == 'voice-validation' || rootItem.state == "fixed")
                    {
                        if (rootItem.state == "fixed")
                            audioRec.stopRecording()
                        audioRec.deleteRecording()
                        rootItem.state = "default"

                    }
                }
            }
            IconButton {
                id:playButton
                anchors.baseline: parent.baseline
                width: recordButton.width
                height: recordButton.height
                visible: rootItem.state == 'voice-validation'
                icon.source: __depecher_audio.playbackState == Audio.PlayingState ? "image://theme/icon-m-pause" : "image://theme/icon-m-play"
                onClicked:{
                    if(__depecher_audio.playbackState != Audio.PlayingState)
                    {
                        __depecher_audio.source = audioRec.location
                        __depecher_audio.play()
                    } else {
                        __depecher_audio.stop()
                    }
                }
            }
            Item {
            width: Theme.paddingMedium
            height: 1
            }
            Label {
                anchors.verticalCenter:  parent.verticalCenter
                color: Theme.highlightColor
                text: rootItem.state == 'voice-validation' && __depecher_audio.playbackState == Audio.PlayingState ?
                          Format.formatDuration(__depecher_audio.position / 1000,Formatter.DurationElapsedShort)  +
                          "/" + Format.formatDuration(__depecher_audio.duration / 1000,Formatter.DurationElapsedShort)
                        : __depecher_audio.source == Qt.resolvedUrl(audioRec.location) ?
                              Format.formatDuration(__depecher_audio.duration / 1000, Formatter.DurationElapsedShort)
                            : Format.formatDuration(audioRec.duration / 1000, Formatter.DurationElapsedShort)
            }
        }
        AudioRecorder {
            id:audioRec
            onError: console.log("Recording error -" + error)
        }
    }
    Item{
        id:mic
        width:recordButton.width
        height:parent.height
        Image {
            id:recordButton
            source:  "image://theme/icon-m-mic"
            y:Theme.paddingSmall
            z:2
            MouseArea {
                anchors.fill: parent
                enabled:  rootItem.state == "fixed" ||  rootItem.state == "voice-validation"
                onClicked: {
                    if(rootItem.state == "voice-validation") {
                        rootItem.state = "default"
                    } else {
                        rootItem.state = "default"
                        audioRec.stopRecording()
                    }
                    if( __depecher_audio.source == Qt.resolvedUrl(audioRec.location))
                        if (__depecher_audio.duration > 500)
                            sendVoice(audioRec.location,__depecher_audio.duration/1000,audioRec.getWaveform())
                        else
                            audioRec.deleteRecording()
                    else
                        if (audioRec.duration > 500)
                            sendVoice(audioRec.location,audioRec.duration/1000,audioRec.getWaveform())
                        else
                            audioRec.deleteRecording()
                }
            }
        }
        Rectangle {
            width: 46
            height:Theme.itemSizeSmall
            radius: 90
            color: Theme.secondaryColor
            z:0
            anchors.fill:lock
            visible: rootItem.state == "moving" || rootItem.state == "pressed"
        }
        Image {
            id:lock
            source :rootItem.state == "fixed" ? "image://theme/icon-m-pause?"+Theme.primaryColor : "qrc:/qml/assets/icons/lock_slide_80x40.png"
            z:1
            anchors.verticalCenter: recordButton.verticalCenter
            anchors.right: recordButton.left
            visible: rootItem.state != "default" && rootItem.state != "voice-validation"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    audioRec.stopRecording()
                    rootItem.state = "voice-validation"
                }
                enabled:  rootItem.state == "fixed"
            }
        }
        Item {
            id:stick
            width: recordButton.width
            height: recordButton.height
            anchors.right: parent.right
            MouseArea {
                anchors.fill:stick
                enabled: rootItem.state != "fixed" && rootItem.state != "voice-validation"
                preventStealing:false
                onPressed:  {
                    preventStealing=true
                    rootItem.state = "pressed"
                    recordButton.x = mouse.x - width
                }
                onPositionChanged: {
                    if (rootItem.state == "pressed" || rootItem.state =="moving") {
                        rootItem.state = "moving"
                        if (mouse.x < - width)
                            rootItem.state = "fixed"
                        else if (mouse.x - width > 0    )
                            recordButton.x = 0
                        else
                            recordButton.x = mouse.x - width
                    }
                }
                onReleased: {
                    preventStealing=false
                    if(audioRec.recording) {
                         if (rootItem.state != "fixed") {
                            audioRec.stopRecording()
                            rootItem.state = "default"
                            if (audioRec.duration > 500)
                                sendVoice(audioRec.location,audioRec.duration/1000,audioRec.getWaveform())
                            else
                                audioRec.deleteRecording()
                        }
                    } else {
                            rootItem.state = "default"
                    }
                }
            }
        }
    }
    Item {
        width: Theme.horizontalPageMargin
        height:parent.height
    }
}
}
