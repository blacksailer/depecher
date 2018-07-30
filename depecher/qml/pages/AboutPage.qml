import QtQuick 2.0
import Sailfish.Silica 1.0
import org.nemomobile.notifications 1.0
import "components"
Page {
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
                text:qsTr("Depecher - Another Telegram client for Sailfish OS based on tdlib.

Features:
- Send/View/Delete messages
- Mute/unmute chats
- View photos
- View animations (gifs)
- View/Send stickers
- Manage stickers from chat
- Uploading/Downloading photos/docs
- Receive notifications
- 2FA authorization enabled

Thanks to:
- @kaffeine
- @chuvilin
- @icoderus
- @aa13q
")
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
                text: qsTr("Here enumerated groups where you can ask any questions (general,dev etc.) related to Sailfish OS.
This groups lives only because of community and by community around Sailfish OS.")
            }
            Label {
                width: parent.width - 2 * x
                x: Theme.horizontalPageMargin
                wrapMode: Text.WordWrap
                color: Theme.secondaryColor
                font.pixelSize: Theme.fontSizeTiny
                text: qsTr("Be aware, after clicking you will join chat. Leaving chats not supported for now.")
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
                    c_telegramWrapper.joinChatByInviteLink("https://t.me/joinchat/AWx9iUE-U9pZ_NeJlxXs0w","EnSailfish")
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
