import QtQuick 2.0
import Sailfish.Silica 1.0
Page {
    SilicaFlickable{
        anchors.fill: parent
        contentHeight: column.height
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
                text:"Depecher - Another Telegram client for Sailfish OS based on tdlib.

Features:
- View messages
- View photos
- View stickers
- Send messages
- Receive notifications

No daemon yet.
No two-factor auth yet.

Thanks to:
- @kaffeine
- @chuvilin
- @icoderus
- @aa13q
"
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
