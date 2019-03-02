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
    SilicaFlickable{
        anchors.fill: parent
        contentHeight: column.height
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
                onProxyLinkChanged:{
                    notificationProxy.previewBody = qsTr("Link copied to clipboard")
                    notificationProxy.publish()
                    Clipboard.text = proxyLink
                }

                onErrorChanged: {
                    notificationPanel.showTextWithTimer(qsTr("Error"),"code:" + error["code"] +"\n" + error["message"])
                }
            }
            SilicaListView {
                width: parent.width
                height:Math.min(Theme.itemSizeMedium * count,Theme.itemSizeMedium * 4)
                model: proxyDao
                delegate: ListItem {
                    id:proxyDelegate
                    width: parent.width
                    contentHeight: Theme.itemSizeMedium
                    Row {
                        width: parent.width
                        height: Theme.itemSizeMedium
                        Column {
                            width: parent.width
                            anchors.verticalCenter:  parent.verticalCenter

                            Row {
                                spacing: Theme.paddingLarge
                                Label{
                                    text:proxy_type
                                    font.bold: true
                                }
                                Label {
                                    text:server +":"+port
                                }
                            }
                            Row {
                                spacing:Theme.paddingLarge
                                Label {
                                    text:is_enabled ? qsTr("Enabled") : qsTr("Disabled")
                                    font.pixelSize: Theme.fontSizeExtraSmall
                                }
                                Label {
                                    id:dateLabel
                                    text:Format.formatDate(new Date(last_used_date*1000), Formatter.DurationElapsedShort)
                                    font.pixelSize: Theme.fontSizeExtraSmall
                                }
                                Label {
                                    text:ping + " s"
                                    font.pixelSize: Theme.fontSizeExtraSmall
                                }
                            }
                        }
                    }
                    onClicked: console.log(last_used_date,new Date())

                    menu: ContextMenu {
                        MenuItem {
                            text: "Disable"
                            onClicked: proxyDao.disableProxy(index)
                            visible:is_enabled
                        }
                        MenuItem {
                            text: "Enable"
                            onClicked: proxyDao.enableProxy(index)
                            visible: !is_enabled
                        }
                        MenuItem {
                            text: "Copy"
                            onClicked: proxyDao.getProxyLink(index)
                        }
                        MenuItem {
                            text: "Edit"
                            onClicked: {
                                var props = {}
                                props["address"] = server
                                props["port"] = port
                                if (proxy_type === "SOCKS5") {
                                    props["username"] = username
                                    props["password"] = password
                                    props["type"] = 0
                                }
                                if (proxy_type === "HTTP") {
                                    props["username"] = username
                                    props["password"] = password
                                    props["http_only"] = http_only
                                    props["type"] = 1

                                }
                                if (proxy_type === "MtProto")
{
                                    props["secret"] = secret
                                props["type"] = 2
}

                                var dialog = pageStack.push("components/settings/ProxyDialog.qml",props)
                                dialog.accepted.connect(function() {
                                    //Socks5
                                    if(dialog.type === 0) {
                                        proxyDao.addProxy(dialog.address,dialog.port,false,{"@type":"proxyTypeSocks5",
                                                              "password":dialog.password,
                                                              "username":dialog.username})
                                    }
                                    //HTTP
                                    else if(dialog.type === 1) {
                                        proxyDao.addProxy(dialog.address,dialog.port,false,{"@type":"proxyTypeHttp",
                                                              "password":dialog.password,
                                                              "username":dialog.username,
                                                              "http_only":dialog.http_only
                                                          })
                                    }
                                    //MtProto
                                    else if(dialog.type === 2) {
                                        proxyDao.addProxy(dialog.address,dialog.port,false,{"@type":"proxyTypeMtproto",
                                                              "secret":dialog.secret})

                                    }
                                })
                            }
                        }
                        MenuItem {
                            text: qsTr("Remove")
                            onClicked:              remorseDelete.execute(proxyDelegate, "Deleting", function() { proxyDao.removeProxy(index) } )
                        }
                    }
RemorseItem{id:remorseDelete}

                    Component.onCompleted: proxyDao.pingProxy(index)
                }

            }
            Button{
                text:qsTr("Add proxy")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    var dialog = pageStack.push("components/settings/ProxyDialog.qml")
                    dialog.accepted.connect(function() {
                        //Socks5
                        if(dialog.type === 0) {
                            proxyDao.addProxy(dialog.address,dialog.port,false,{"@type":"proxyTypeSocks5",
                                                  "password":dialog.password,
                                                  "username":dialog.username})
                        }
                        //HTTP
                        else if(dialog.type === 1) {
                            proxyDao.addProxy(dialog.address,dialog.port,false,{"@type":"proxyTypeHttp",
                                                  "password":dialog.password,
                                                  "username":dialog.username,
                                                  "http_only":dialog.http_only
                                              })
                        }
                        //MtProto
                        else if(dialog.type === 2) {
                            proxyDao.addProxy(dialog.address,dialog.port,false,{"@type":"proxyTypeMtproto",
                                                  "secret":dialog.secret})

                        }
                    })
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

                RemorsePopup {
                id:remorseLogout
                }
                onClicked: {
                    remorseLogout.execute(qsTr("Logging out"),function() { c_telegramWrapper.logOut();
                        pageStack.replaceAbove(null,Qt.resolvedUrl("AuthorizeDialog.qml")) })

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
