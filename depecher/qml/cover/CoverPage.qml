import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramModels 1.0
import QtMultimedia 5.6
import "../js/utils.js" as Utils
CoverBackground {
    Connections {
    target: c_telegramWrapper
    onConnectionStateChanged:{
        status.text = Utils.setState(connectionState)
    }
    }
    Column{
        width:parent.width
        anchors.centerIn: parent
        Item{
            width:captionUnread.width+counter.width
            height: counter.height
            anchors.horizontalCenter: parent.horizontalCenter

        Label {
            id: counter
            width:paintedWidth
            text:c_telegramWrapper.totalUnreadCount
            color: Theme.primaryColor
            font.pixelSize: Theme.fontSizeExtraLarge*3/2
        }
        Label {
            id:captionUnread
            anchors.left: counter.right
            anchors.top: counter.top
            text:qsTr("Unread \n messages")
            maximumLineCount: 2
            color: Theme.secondaryColor
            font.pixelSize: Theme.fontSizeExtraSmall
        }
        }
    Label {
        id: label
        text: qsTr("Depecher")
        color: Theme.secondaryColor
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Label {
    id:status
    width:parent.width
    color: Theme.highlightColor
    text: Utils.setState(c_telegramWrapper.connectionState)
    horizontalAlignment: Text.AlignHCenter
    wrapMode: Text.WordWrap
    anchors.horizontalCenter: parent.horizontalCenter
}

    }
    CoverActionList {
        id: coverAction
        enabled: rootWindow.__depecher_audio.hasAudio
        CoverAction {
            iconSource: rootWindow.__depecher_audio.playbackState === Audio.PlayingState ? "image://theme/icon-cover-pause"
                                                                                        : "image://theme/icon-cover-play"
            onTriggered:rootWindow.__depecher_audio.playbackState === Audio.PlayingState ?
                            rootWindow.__depecher_audio.pause()
                          : rootWindow.__depecher_audio.play()
        }
}

}

