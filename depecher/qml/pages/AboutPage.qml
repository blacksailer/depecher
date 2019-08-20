import QtQuick 2.0
import Sailfish.Silica 1.0
import org.nemomobile.notifications 1.0
import depecherUtils 1.0
import "components"
Page {

    Component.onCompleted:  {
        DNSLookup.lookupServer()
    }

    SilicaFlickable{
        anchors.fill: parent
        contentHeight: column.height
        Connections {
            target: c_telegramWrapper
            onGetChatByLink: {
                var page = pageStack.find(function (page) {
                    return page.__chat_page !== undefined;
                });
                pageStack.replaceAbove(page,"MessagingPage.qml",{chatId:chat_id})
            }
            onErrorReceivedMap: {
                notificationProxy.previewBody = qsTr("Error %1").arg(errorObject["code"] ) +" "+ errorObject["message"]
                notificationProxy.publish()
            }
        }
        Notification {
            id:notificationProxy
            appName: "Depecher"
            icon:"image://theme/icon-lock-warning"
        }

        Column {
            id:column
            width:parent.width
            PageHeader{
                title: qsTr("About")
            }
            Label
            {
                width: parent.width - 2 * x
                x : Theme.horizontalPageMargin
                wrapMode: Text.WordWrap
                font.pixelSize: Theme.fontSizeSmall
                text: qsTr("Depecher - Another Telegram client for Sailfish OS based on tdlib.") + "<br><br>" +
                      qsTr("Features:") + "<br>" +
                      qsTr("- Send/View/Delete messages") + "<br>" +
                      qsTr("- Mute/unmute chats") + "<br>" +
                      qsTr("- View photos") + "<br>" +
                      qsTr("- View animations (gifs)") + "<br>" +
                      qsTr("- View/Send stickers") + "<br>" +
                      qsTr("- Manage stickers from chat") + "<br>" +
                      qsTr("- Uploading/Downloading photos/docs") + "<br>" +
                      qsTr("- Receive notifications") + "<br>" +
                      qsTr("- 2FA authorization enabled") + "<br><br>" +
                      qsTr("Thanks to:") + "<br>" +
                      "- @kaffeine" + "<br>" +
                      "- @chuvilin" + "<br>" +
                      "- @icoderus" + "<br>" +
                      "- @aa13q"
            }
            Label
            {
                width: parent.width - 2 * x
                x : Theme.horizontalPageMargin
                wrapMode: Text.WordWrap
                font.pixelSize: Theme.fontSizeSmall
                text: qsTr("Version") + "-" + Qt.application.version

            }
            SectionHeader{
                text: qsTr("Sources")
            }
            BackgroundItem{
                width: parent.width
                height: Theme.itemSizeMedium
                Row{
                    width:parent.width - 2 * x
                    height: parent.height
                    x:Theme.horizontalPageMargin
                    spacing:Theme.paddingMedium
                    Image {
                        width: parent.height
                        height: width
                        source: "qrc:/qml/assets/icons/git.svg"
                    }

                    Label{
                        width: parent.width - parent.height - parent.spacing
                        anchors.verticalCenter: parent.verticalCenter
                        wrapMode: Text.WrapAnywhere
                        font.pixelSize: Theme.fontSizeSmall

                        text: "https://github.com/blacksailer/depecher"
                        color: parent.parent.pressed ? Theme.highlightColor : Theme.primaryColor

                    }
                }
                onClicked: Qt.openUrlExternally("https://github.com/blacksailer/depecher")
            }
            SectionHeader{
                text: qsTr("Groups in Telegram")
            }

            Label {
                width: parent.width - 2 * x

                x: Theme.horizontalPageMargin
                wrapMode: Text.WordWrap
                font.pixelSize: Theme.fontSizeSmall
                text: qsTr("Here enumerated groups where you can ask any questions (general,dev etc.) related to Sailfish OS.") + "<br>" +
                      qsTr("This groups lives only because of community and by community around Sailfish OS.") +"</p>"
            }
            Label {
                width: parent.width - 2 * x
                x: Theme.horizontalPageMargin
                wrapMode: Text.WordWrap
                color: Theme.secondaryColor
                font.pixelSize: Theme.fontSizeTiny
                text: qsTr("Be aware, after clicking you will join chat.")
            }
            BackgroundItem {
                width: parent.width
                height: Theme.itemSizeMedium
                Row{
                    width:parent.width - 2 * x
                    height: parent.height
                    x:Theme.horizontalPageMargin
                    spacing:Theme.paddingMedium
                    Image {
                        width: parent.height
                        height: width
                        source: "qrc:/qml/assets/icons/en_sailfish.jpg"
                    }
                    Column {
                        width: parent.width - parent.height - parent.spacing
                        Label{
                            width: parent.width
                            text:"Sailfish OS Fan Club"
                            truncationMode: TruncationMode.Fade
                            color: parent.pressed ? Theme.highlightColor : Theme.primaryColor
                        }
                        Label{
                            width: parent.width
                            text:qsTr("English speaking community")
                            truncationMode: TruncationMode.Fade
                            font.pixelSize: Theme.fontSizeSmall
                            color: parent.pressed ? Theme.secondaryHighlightColor : Theme.secondaryColor
                        }
                    }
                }
                RemorsePopup {
                    id:joinPopup
                }
                onClicked: joinPopup.execute(qsTr("Joining chat"), function() {
                    var url = DNSLookup.inviteLink
                    if(url.indexOf("t.me/joinchat") != -1)
                        c_telegramWrapper.joinChatByInviteLink(url,"EnSailfish")
                    else {
                        notificationProxy.previewBody = qsTr("Error to get invite link")
                        notificationProxy.publish()
                    }

                } )

            }
            BackgroundItem {
                width: parent.width
                height: Theme.itemSizeMedium
                Row{
                    width:parent.width - 2 * x
                    height: parent.height
                    x:Theme.horizontalPageMargin
                    spacing:Theme.paddingMedium
                    Image {
                        width: parent.height
                        height: width
                        source: "qrc:/qml/assets/icons/it_sailfish.jpg"
                    }
                    Column {
                        width: parent.width - parent.height - parent.spacing
                        Label{
                            width: parent.width
                            text:"Jolla Community Italian Club"
                            truncationMode: TruncationMode.Fade
                            color: parent.pressed ? Theme.highlightColor : Theme.primaryColor
                        }
                        Label{
                            width: parent.width
                            text:qsTr("Italian speaking community")
                            truncationMode: TruncationMode.Fade
                            font.pixelSize: Theme.fontSizeSmall
                            color: parent.pressed ? Theme.secondaryHighlightColor : Theme.secondaryColor
                        }
                    }
                }
                onClicked: joinPopup.execute(qsTr("Joining chat"), function() {

                        c_telegramWrapper.joinChat(parseFloat("-1001105250707"),"EnSailfish")
                } )

            }
            SectionHeader{
                text: qsTr("Donations")
            }
            BackgroundItem{
                width: parent.width
                height: Theme.itemSizeMedium
                Row{
                    width:parent.width - 2 * x
                    height: parent.height
                    x:Theme.horizontalPageMargin
                    spacing:Theme.paddingMedium
                    Image {
                        width: parent.height
                        height: width
                        source: "qrc:/qml/assets/icons/paypal.svg"
                    }
                    Label{
                        width: parent.width - parent.height - parent.spacing
                        anchors.verticalCenter: parent.verticalCenter
                        wrapMode: Text.WrapAnywhere
                        font.pixelSize: Theme.fontSizeSmall
                        color: parent.parent.pressed ? Theme.highlightColor : Theme.primaryColor
                        text: "https://paypal.me/blacksailer"
                    }
                }
                onClicked: Qt.openUrlExternally("https://www.paypal.me/blacksailer")
            }
            BackgroundItem{
                width: parent.width
                height: Theme.itemSizeMedium
                Row{
                    width:parent.width - 2 * x
                    height: parent.height
                    x:Theme.horizontalPageMargin
                    spacing:Theme.paddingMedium
                    Image {
                        width: parent.height
                        height: width
                        source: "qrc:/qml/assets/icons/rocket.svg"
                    }
                    Label{
                        width: parent.width - parent.height - parent.spacing
                        anchors.verticalCenter: parent.verticalCenter
                        wrapMode: Text.WrapAnywhere
                        font.pixelSize: Theme.fontSizeSmall
                        color: parent.parent.pressed ? Theme.highlightColor : Theme.primaryColor
                        text: "https://rocketbank.ru/ivan.chernenky"
                    }
                }
                onClicked: Qt.openUrlExternally("https://rocketbank.ru/ivan.chernenky")
            }
        }
    }
}
