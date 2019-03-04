import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import "../../items"
import ".."
import "../../../js/utils.js" as Utils

import org.nemomobile.notifications 1.0
import TelegramItems 1.0

Page {
    id:root
    property string connectionStatus: Utils.setState(c_telegramWrapper.connectionState)

    NotificationPanel{
        id: notificationPanel
        page: root
    }
    Notification {
        id:notificationProxy
        appName: "Depecher"
        previewBody: qsTr("Proxy is ready")
    }

    ProxyDAO {
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
anchors.fill: parent
        model: proxyDao
        header:    PageHeader {
            title: qsTr("Proxy")
            description: qsTr("Connection status: ") + root.connectionStatus

        }
        delegate: ListItem {
            id:proxyDelegate
            width: parent.width
            contentHeight: Theme.itemSizeMedium
            Row {
                width: parent.width - 2 * x
                x:Theme.horizontalPageMargin
                height: Theme.itemSizeMedium
                Column {
                    width: parent.width
                    anchors.verticalCenter:  parent.verticalCenter

                    Row {
                        spacing: Theme.paddingMedium
                        Label{
                            id:labelType
                            text:proxy_type
                            font.bold: true
                        }
                        Label {
                            text:server +":"+port
                            width: proxyDelegate.width - 2 * Theme.horizontalPageMargin - labelType.width - Theme.paddingMedium
                            truncationMode: TruncationMode.Fade
                        }
                    }
                    Row {
                        spacing:Theme.paddingMedium
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
                        props["proxyIndex"] = index
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

                        var dialog = pageStack.push("ProxyDialog.qml",props)
                        dialog.accepted.connect(function() {
                            //Socks5
                            if(dialog.type === 0) {
                                proxyDao.editProxy(dialog.proxyIndex,dialog.address,dialog.port,false,{"@type":"proxyTypeSocks5",
                                                      "password":dialog.password,
                                                      "username":dialog.username})
                            }
                            //HTTP
                            else if(dialog.type === 1) {
                                proxyDao.editProxy(dialog.proxyIndex,dialog.address,dialog.port,false,{"@type":"proxyTypeHttp",
                                                      "password":dialog.password,
                                                      "username":dialog.username,
                                                      "http_only":dialog.http_only
                                                  })
                            }
                            //MtProto
                            else if(dialog.type === 2) {
                                proxyDao.editProxy(dialog.proxyIndex,dialog.address,dialog.port,false,{"@type":"proxyTypeMtproto",
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
        PullDownMenu {
            MenuItem {
            text:qsTr("Add proxy")
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                var dialog = pageStack.push("ProxyDialog.qml")
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
        }

    }

}
