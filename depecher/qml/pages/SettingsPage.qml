import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramItems 1.0
import "../js/utils.js" as Utils
import Nemo.Notifications 1.0
Page {
    id:root
    property bool isProxyConfiguring: false
    property bool isLogoutVisible: true
    property string connectionStatus: Utils.setState(c_telegramWrapper.connectionState)
    SilicaFlickable{
        anchors.fill: parent
        contentHeight: column.height

        Notification {
            id:notificationProxy
            appName: "Depecher"
            previewBody: qsTr("Proxy is ready")
        }
        Column{
            id:column
            width: parent.width
            PageHeader{
                title:qsTr("Settings")
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
                    text: qsTr("Connection status: "+ root.connectionStatus)
                }
            }
            ProxyDAO{
                id:proxyDao
            }
            TextField {
                id:addressField
                x: Theme.horizontalPageMargin
                
                placeholderText: qsTr("Server address")
                label: qsTr("Address. Set empty to disable proxy")
                width: parent.width
                text:proxyDao.address
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: portField.focus = true
            }
            TextField {
                id:portField
                x: Theme.horizontalPageMargin
                
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
                x: Theme.horizontalPageMargin
                
                
                placeholderText: qsTr("Username")
                label: qsTr("username")
                text:proxyDao.username
                width: parent.width
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: passwordField.focus = true
            }
            PasswordField{
                id:passwordField
                x: Theme.horizontalPageMargin
                
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
                Label{
                    text:qsTr("About")
                    x: Theme.horizontalPageMargin
                    color: parent.pressed ? Theme.highlightColor : Theme.primaryColor
                    anchors.verticalCenter: parent.verticalCenter
                }
                onClicked: pageStack.push("AboutPage.qml")
            }
            Item{
            //move button logout down
                width: parent.width
                height:Theme.itemSizeMedium
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
        }
    }
    function setupProxy(){
        if(addressField.text != "")
            isProxyConfiguring = true;
        proxyDao.setProxy(addressField.text.trim(),portField.text.trim(),usernameField.text.trim(),passwordField.text.trim())
    }
}
