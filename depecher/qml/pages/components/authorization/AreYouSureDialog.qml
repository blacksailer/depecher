import QtQuick 2.0
import Sailfish.Silica 1.0
import tdlibQtEnums 1.0
import "../../../js/utils.js" as Utils
Dialog {
    id:areYouSureDialog
    property string fullPhoneNumber: ""
    property string connectionStatus: Utils.setState(c_telegramWrapper.connectionState)
    acceptDestination: Qt.resolvedUrl("SignInDialog.qml")
    acceptDestinationAction: PageStackAction.Replace
    canAccept: c_telegramWrapper.connectionState === TdlibState.ConnectionStateReady
    onAcceptPendingChanged: {
        if (acceptPending) {
            c_telegramWrapper.setPhoneNumber(fullPhoneNumber);
        }
    }
    Connections {
        target: c_telegramWrapper
        onConnectionStateChanged:{
           connectionStatus = Utils.setState(connectionState)
        }
    }

    Column{
        width: parent.width-2*x
        x:Theme.horizontalPageMargin
        spacing:Theme.paddingLarge
        PageHeader{}
        Label{
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
visible: connectionStatus != "Ready"
            wrapMode: Text.WordWrap
            font.pixelSize: Theme.fontSizeExtraSmall
        text:qsTr("To continue connection to Telegram is needed")
        color:"red"
        }
        Label{
            width: parent.width
            horizontalAlignment: Text.AlignHCenter

            wrapMode: Text.WordWrap
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.secondaryColor
            text: qsTr("Connection status: ")+ connectionStatus
        }

        Label{
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            text:qsTr("Is phone correct?")
            color:Theme.primaryColor

        }
        Label{
            text:fullPhoneNumber
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            color:Theme.secondaryColor
        }
    }
}
