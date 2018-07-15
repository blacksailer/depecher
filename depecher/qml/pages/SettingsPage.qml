import QtQuick 2.6
import Sailfish.Silica 1.0
import TelegramItems 1.0
import "../js/utils.js" as Utils
import org.nemomobile.notifications 1.0
import "items"
import tdlibQtEnums 1.0
import Nemo.Configuration 1.0
Page {
    id:root
    property bool isProxyConfiguring: false
    property bool isLogoutVisible: true
    property string settingsPath:  "/apps/depecher"
    ConfigurationValue {
        id:sendByEnter
        key:settingsPath +"/sendByEnter"
        defaultValue: false
    }
    property string connectionStatus: Utils.setState(c_telegramWrapper.connectionState)
    SilicaFlickable{
        anchors.fill: parent
        contentHeight: column.height

        Notification {
            id:notificationProxy
            appName: "Depecher"
            previewBody: qsTr("Proxy is ready")
        }
        Connections {
            target: c_telegramWrapper
            onConnectionStateChanged:{
                connectionStatus = Utils.setState(connectionState)
                if(connectionStatus === "Ready" && isProxyConfiguring)
                {
                    isProxyConfiguring = false;
                    notificationProxy.publish()
                }
            }
        }

        Column{
            id:column
            width: parent.width
            PageHeader{
                title:qsTr("Settings")
            }
            Column {
                    width:parent.width - 2 * x
                    x: Theme.horizontalPageMargin
                    topPadding:  Theme.paddingMedium
                    spacing: Theme.paddingLarge
                    visible:isLogoutVisible

                    Row{
                        width: parent.width
                        CircleImage {
                            id: avatar
                            width:height
                            height: 135
                            source: aboutMe.photoPath ? "image://depecherDb/"+aboutMe.photoPath : ""
                            fallbackText: aboutMe.firstName.charAt(0)
                            fallbackItemVisible: aboutMe.photoPath ? false : true
                        }
                    }
                    AboutMeDAO{
                    id:aboutMe
                    }
                    Row{
                        width:parent.width
                        Column{
                            width:parent.width-button.width
                            Label{
                                text:aboutMe.fullName
                                color:Theme.highlightColor
                            }
                            Label{
                                text:aboutMe.phoneNumber
                                color:Theme.secondaryHighlightColor

                            }
                        }
                        IconButton{
                            id:button
                            icon.source: "image://theme/icon-s-cloud-upload?" + (pressed
                                                                                 ? Theme.highlightColor
                                                                                 : Theme.primaryColor)
                            onClicked:{
                                var chatType = {};
                                chatType["type"] = TdlibState.Private
                                pageStack.replace("MessagingPage.qml",{userName:aboutMe.fullName,
                                                      chatId:aboutMe.id,chatType:chatType,
                                               lastReadMessage:0,lastMessageId:0})
                            }
                        }
                    }
                    Item{
                        //bottomPadding
                        width: parent.width
                        height: 1
                    }

                }
            SectionHeader {
                text: qsTr("Settings")
            }
            BackgroundItem {
                width: parent.width
                height: Theme.itemSizeMedium
                Label {
                text: qsTr("Appearance")
                anchors.verticalCenter: parent.verticalCenter
                x:Theme.horizontalPageMargin
                }
                onClicked: pageStack.push(Qt.resolvedUrl("components/settings/AppearancePage.qml"))


            }

            TextSwitch {
                width: parent.width -2*x
                x:Theme.horizontalPageMargin
                checked: sendByEnter.value
                automaticCheck: false
                text: qsTr("Send message by enter")
                onClicked: {
                    sendByEnter.value = !checked
                    sendByEnter.sync()
                }

            }

            SectionHeader {
                text: qsTr("Socks5 proxy")
            }
            Row{
                width: parent.width -2 *x
                x: Theme.horizontalPageMargin
                BusyIndicator{
                    id:busyIndicatorConnection
                    size: BusyIndicatorSize.Small
                    visible: isProxyConfiguring
                    running: isProxyConfiguring
                }
                Label{
                    width: parent.width - busyIndicatorConnection.width
                    wrapMode: Text.WordWrap
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.secondaryColor
                    text: qsTr("Connection status: ") + root.connectionStatus
                }
            }
            ProxyDAO{
                id:proxyDao
            }
            TextField {
                id:addressField                
                placeholderText: qsTr("Server address")
                label: qsTr("Address. Set empty to disable proxy")
                width: parent.width
                text:proxyDao.address
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: portField.focus = true
            }
            TextField {
                id:portField                
                placeholderText: qsTr("Server port")
                label: qsTr("port")
                text:proxyDao.port
                width: parent.width
                inputMethodHints: Qt.ImhDigitsOnly
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: usernameField.focus = true
            }
            TextField {
                id:usernameField
                placeholderText: qsTr("Username")
                label: qsTr("username")
                text:proxyDao.username
                width: parent.width
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: passwordField.focus = true
            }
            PasswordField{
                id:passwordField
                width: parent.width
                text:proxyDao.password
                placeholderText:qsTr("Password")
                label:qsTr("Password")
                EnterKey.iconSource: "image://theme/icon-m-enter-accept"
                EnterKey.onClicked:setupProxy()
                
            }
            Button{
                text:qsTr("Set proxy")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    setupProxy()
                }
            }
            SectionHeader {
                text: qsTr("General")
            }
            BackgroundItem {
                width: parent.width
                height: Theme.itemSizeMedium
                Column {
                    width: parent.width
                Label{
                    text:qsTr("About program")
                    x: Theme.horizontalPageMargin
                    color: parent.pressed ? Theme.highlightColor : Theme.primaryColor
                }
                Label{
                    text:qsTr("Credits and stuff")
                    x: Theme.horizontalPageMargin
                    font.pixelSize: Theme.fontSizeSmall
                    color: parent.pressed ? Theme.secondaryHighlightColor : Theme.secondaryColor
                }
                }

                onClicked: pageStack.push("AboutPage.qml")
            }
      Item {
          //for spacing purposes
      width: parent.width
      height: Theme.paddingMedium
      }

            Button{
                id:logoutButton
                text:qsTr("Log out")
                visible:isLogoutVisible
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    c_telegramWrapper.logOut()
                    pageStack.replaceAbove(null,Qt.resolvedUrl("AuthorizeDialog.qml"));
                }
            }
            Item {
                //for spacing purposes
            width: parent.width
            height: Theme.paddingMedium
            }

        }
    }
    function setupProxy(){
        if(addressField.text != "")
            isProxyConfiguring = true;
        proxyDao.setProxy(addressField.text.trim(),portField.text.trim(),usernameField.text.trim(),passwordField.text.trim())
    }
}
