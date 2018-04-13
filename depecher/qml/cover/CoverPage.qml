import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramModels 1.0
CoverBackground {
    Connections {
    target: c_telegramWrapper
    onConnectionStateChanged:{
        status.text = status.setState(connectionState)
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
            text:chatsModel.totalUnreadCount
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
    color: Theme.highlightColor
    text: setState(c_telegramWrapper.connectionState)
    anchors.horizontalCenter: parent.horizontalCenter
    function setState(state) {
        switch(state){
        case 0:
            return "Waiting for network"
                  case 1:
                      return "Connecting"
                  case 2:
                      return "Connecting to proxy"
                  case 3:
                      return "Updating..."
                  case 4:
                      return "Ready"
                default:
                    return "Uknown"
                  }

    }
}

    }
//    CoverActionList {
//        id: coverAction

//        CoverAction {
//            iconSource: "image://theme/icon-cover-next"
//        }

//        CoverAction {
//            iconSource: "image://theme/icon-cover-pause"
//        }
//    }
}

