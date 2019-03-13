import QtQuick 2.6
import Sailfish.Silica 1.0
import TelegramItems 1.0
import "../js/utils.js" as Utils
import org.nemomobile.notifications 1.0
import Nemo.DBus 2.0
import "items"
import tdlibQtEnums 1.0
import Nemo.Configuration 1.0
import "components"

Page {
    id:root
    property bool isProxyConfiguring: false
    property bool isLogoutVisible: true

    property string connectionStatus: Utils.setState(c_telegramWrapper.connectionState)
    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height
        RemorsePopup {
        id:remorseLogout
        }
        PullDownMenu {
            MenuItem {
            text:qsTr("Log out")
            visible:isLogoutVisible

            onClicked: {
                remorseLogout.execute(qsTr("Logging out"),function() { c_telegramWrapper.logOut();
                    pageStack.replaceAbove(null,Qt.resolvedUrl("AuthorizeDialog.qml")) })

            }
            }
        }

        NotificationPanel{
            id: notificationPanel
            page: root
        }
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
                    disableGetMe:!isLogoutVisible
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
                            pageStack.replace("MessagingPage.qml",{chatId:aboutMe.id})
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
                height: Theme.itemSizeSmall
                Label {
                    text: qsTr("Appearance")
                    anchors.verticalCenter: parent.verticalCenter
                    x:Theme.horizontalPageMargin
                }
                onClicked: pageStack.push(Qt.resolvedUrl("components/settings/AppearancePage.qml"))
            }
            BackgroundItem {
                width: parent.width
                height: Theme.itemSizeSmall
                Label {
                    text: qsTr("Behavior")
                    anchors.verticalCenter: parent.verticalCenter
                    x:Theme.horizontalPageMargin
                }
                onClicked: pageStack.push(Qt.resolvedUrl("components/settings/BehaviorPage.qml"))
            }
            BackgroundItem {
                width: parent.width
                height: Theme.itemSizeSmall
                Label {
                    text: qsTr("Proxy")
                    anchors.verticalCenter: parent.verticalCenter
                    x:Theme.horizontalPageMargin
                }
                onClicked: pageStack.push(Qt.resolvedUrl("components/settings/ProxyPage.qml"))
            }

            BackgroundItem {
                width: parent.width
                height: Theme.itemSizeSmall
                Label {
                    text: qsTr("Daemon settings")
                    anchors.verticalCenter: parent.verticalCenter
                    x:Theme.horizontalPageMargin
                }
                onClicked: {
                    setingsDbus.typedCall("showPage", [{"type": "s", "value": "applications/depecher.desktop"}],
                                          function() {
                                              console.log("opened settings")
                                          },
                                          function() {
                                              console.log("fail to open settings")
                                          })

                }

                DBusInterface {
                    id: setingsDbus

                    bus: DBus.SessionBus
                    service: "com.jolla.settings"
                    path: "/com/jolla/settings/ui"
                    iface: "com.jolla.settings.ui"
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


        }
    }
}
