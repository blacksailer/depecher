import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property alias source: img.source
    property alias emoji: emojiLabel.text
    width: parent.width
    height: emojiLabel.height + img.height + 2*Theme.paddingMedium

    Label{
        id:emojiLabel
        anchors.horizontalCenter:  parent.horizontalCenter
        anchors.topMargin: Theme.paddingMedium
        font.pixelSize: Theme.fontSizeHuge
    }
    Image {
        id: img
        anchors.horizontalCenter:  parent.horizontalCenter
        anchors.top: emojiLabel.bottom
        anchors.topMargin: Theme.paddingMedium

    }

}
