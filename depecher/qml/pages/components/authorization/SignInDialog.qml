import QtQuick 2.6
import Sailfish.Silica 1.0
import TelegramAuthentication 1.0
import tdlibQtEnums 1.0
import ".."
import "../../../js/utils.js" as Utils
Dialog {
    id:signInDialog
    property string fullPhoneNumber: ""
    property bool canLogin: false
    canAccept: canLogin

    SilicaFlickable{
        anchors.fill: parent
        NotificationPanel{
            id: notificationPanel
            page: signInDialog
        }

        TelegramAuthenticationHandler {
            id:telegramAuthenticationHandler
            property bool forgotPassword: false
            onAuthorizationStateChanged: {
                if(currentAuthorizationState === TdlibState.AuthorizationStateWaitPassword)
                    signInDialog.state = "password"
                if(currentAuthorizationState === TdlibState.AuthorizationStateWaitCode)
                    signInDialog.state = "code"
                if(currentAuthorizationState === TdlibState.AuthorizationStateReady)
                {
                    canLogin=true
                    pageStack.replaceAbove(null,Qt.resolvedUrl("../../DialogsPage.qml"))
                }
            }

            onErrorChanged: {
                notificationPanel.showTextWithTimer(qsTr("Error"),"code:" + error["code"] +"\n" + error["message"])
            }

        }

        PullDownMenu {
            id:pulleyMenuRecovery
            visible: false

            MenuItem{
                text:qsTr("Recover password")
                enabled: telegramAuthenticationHandler.hasRecoveryEmail
                onClicked: {
                    hintLabel.visible = false
                    telegramAuthenticationHandler.recoverPassword()
                    telegramAuthenticationHandler.forgotPassword = true
                    notificationPanel.showTextWithTimer(qsTr("Email is sent"),qsTr("recovery code sent to %1").arg(telegramAuthenticationHandler.emailPattern))

                }
            }

            MenuItem {
                text:qsTr("Show hint")
                onClicked: hintLabel.visible = true
            }
        }
        PageHeader {
            id:header
        title: state == "code" ? qsTr("Enter code") : qsTr("Enter password")
        description: qsTr("Authentication state") +" - "+Utils.setAuthState(telegramAuthenticationHandler.currentAuthorizationState)
        }

        states:[
            State {
                name: "password"
                when: telegramAuthenticationHandler.currentAuthorizationState === 4
                PropertyChanges {
                    target: keyColumn
                    visible:true
                }
                PropertyChanges {
                    target: signin
                    visible:false
                }

                PropertyChanges {
                    target: pulleyMenuRecovery
                    visible:true
                }
            },
            State {
                name: "code"
                when: telegramAuthenticationHandler.currentAuthorizationState === 3
                PropertyChanges {
                    target: signin
                    visible:true
                }

            }
        ]
        Column
        {
            id:keyColumn
            spacing: Theme.paddingMedium
            x:Theme.horizontalPageMargin
            topPadding:Math.max(header.height,(signInDialog.height - imglock.height - lblInfoPass.height - tfPassword.height - hintLabel.height - btnpassword.height - 4 * spacing)/2)
            width: parent.width-2*x
            visible: false
            Image {
                id: imglock
                source: "image://theme/icon-m-device-lock"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Label {
                id: lblInfoPass
                text: telegramAuthenticationHandler.forgotPassword ? qsTr("Enter recovery code. \n Remember! After that 2FA authorization will be disabled") : qsTr("Enter your password")
                font.pixelSize: Theme.fontSizeSmall
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingMedium; rightMargin: Theme.paddingMedium }
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
            }
            PasswordField {
                id: tfPassword
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingMedium; rightMargin: Theme.paddingMedium }
                placeholderText: telegramAuthenticationHandler.forgotPassword ? qsTr("Recovery code") : qsTr("Password")
                inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
            }
            Label {
                id:hintLabel
                visible: false
                text:qsTr("Password hint")+ " - " + telegramAuthenticationHandler.getHint
                font.pixelSize: Theme.fontSizeSmall
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingMedium; rightMargin: Theme.paddingMedium }
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
            }
            Button {
                id: btnpassword
                anchors { horizontalCenter: parent.horizontalCenter }
                text: qsTr("Sign In")
                enabled: tfPassword.text.length > 0
                onClicked: {
                    if(telegramAuthenticationHandler.forgotPassword)
                        telegramAuthenticationHandler.sendRecoveryCode(tfPassword.text)
                    else
                        telegramAuthenticationHandler.checkPassword(tfPassword.text)
                }
            }
        }
        Column
        {
            id: signin
            spacing: Theme.paddingMedium
            x:Theme.horizontalPageMargin
            width: parent.width-2*x
            topPadding:Math.max(header.height,(signInDialog.height - imgwaiting.height - lblinfo.height - tfcode.height - tfRowName.height - btnsignin.height - 4 * spacing)/2)
            visible: true
            Image {
                id: imgwaiting
                source: "image://theme/icon-l-timer"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Label {
                id: lblinfo
                text: qsTr("Wait for the message via %1 containing the activation code and press %2" ).arg(telegramAuthenticationHandler.getType).arg(telegramAuthenticationHandler.isUserRegistered ? qsTr("Sign In") : qsTr("Sign up"))
                font.pixelSize: Theme.fontSizeSmall
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingMedium; rightMargin: Theme.paddingMedium }
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
            }

            TextField  {
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


            Button  {
                id: btnsignin
                anchors { horizontalCenter: parent.horizontalCenter }
                text: telegramAuthenticationHandler.isUserRegistered ? qsTr("Sign In") : qsTr("Sign up")
                enabled: telegramAuthenticationHandler.isUserRegistered ? tfcode.text.length > 0
                                                                        : tfcode.text.length > 0 && tfName.text.length > 0
                                                                          && tfSurName.text.length > 0
                onClicked: {
                    btnsignin.enabled = false;
                    btnsignin.text = qsTr("Sending request...");

                    if (telegramAuthenticationHandler.isUserRegistered)
                        c_telegramWrapper.checkCode(tfcode.text)
                    else
                        c_telegramWrapper.setCodeIfNewUser(tfcode.text,tfSurName.text,tfName.text)
                }
            }
        }
    }
}

