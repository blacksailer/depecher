import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramAuthentication 1.0
import "../../../js/utils.js" as Utils
Dialog {
    id:signInDialog
    property string fullPhoneNumber: ""
    property bool signBtnPressed: false
    property int authError: 0
    canAccept: signBtnPressed
    Connections {
        target: c_telegramWrapper
        onConnectionStateChanged:{
           var connectionStatus = Utils.setState(connectionState)
        }
    }
    onAcceptPendingChanged: {
        if (acceptPending) {
            pageStack.replaceAbove(null,Qt.resolvedUrl("../../DialogsPage.qml"));
        }
    }
    TelegramAuthenticationHandler{
        id:telegramAuthenticationHandler
    }
    Column
    {
        id: signin
        spacing: Theme.paddingMedium
        x:Theme.horizontalPageMargin
        width: parent.width-2*x

        PageHeader { width: parent.width; height: Theme.paddingLarge }

        Image
        {
            id: imgwaiting
            source: "image://theme/icon-l-timer"
            anchors.horizontalCenter: parent.horizontalCenter
        }


        Label
        {
            id: lblinfo
            text: qsTr("Wait for the message via " + telegramAuthenticationHandler.getType + " containing the activation code and press " + btnsignin.text)
            font.pixelSize: Theme.fontSizeSmall
            anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingMedium; rightMargin: Theme.paddingMedium }
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
        }

        Label
        {
            id: txterrormsg
            font { bold: true; underline: true; pixelSize: Theme.fontSizeSmall }
            color: Theme.secondaryHighlightColor
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.Wrap
        }

        TextField
        {
            id: tfcode
            anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingMedium; rightMargin: Theme.paddingMedium }
            placeholderText: qsTr("Code")
            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText | Qt.ImhDigitsOnly
        }
        Column {
            id:tfRowName
            width:parent.width
            visible: !telegramAuthenticationHandler.isUserRegistered
            TextField
            {
                id: tfName
                width:parent.width
                placeholderText: qsTr("First Name")
            }
            TextField
            {
                id: tfSurName
                width:parent.width
                placeholderText: qsTr("Surname")
            }
        }


        Button
        {
            id: btnsignin
            anchors { horizontalCenter: parent.horizontalCenter }
            text: telegramAuthenticationHandler.isUserRegistered ? qsTr("Sign In") : qsTr("Sign up")
            enabled: telegramAuthenticationHandler.isUserRegistered ? tfcode.text.length > 0
                                                                   : tfcode.text.length > 0 && tfName.text.length > 0
                                                                     && tfSurName.text.length > 0
            onClicked: {
                signBtnPressed = true;
                btnsignin.enabled = false;
                btnsignin.text = qsTr("Sending request...");

                if (telegramAuthenticationHandler.isUserRegistered)
                    c_telegramWrapper.setCode(tfcode.text)
                else
                    c_telegramWrapper.setCodeIfNewUser(tfcode.text,tfSurName.text,tfName.text)

                signInDialog.accept()

            }
        }
    }
}
