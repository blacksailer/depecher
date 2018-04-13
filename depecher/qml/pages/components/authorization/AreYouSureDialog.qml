import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id:areYouSureDialog
    property string fullPhoneNumber: ""
    acceptDestination: Qt.resolvedUrl("SignInDialog.qml")
    acceptDestinationAction: PageStackAction.Replace
    onAcceptPendingChanged: {
        if (acceptPending) {
            c_telegramWrapper.setPhoneNumber(fullPhoneNumber);
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
