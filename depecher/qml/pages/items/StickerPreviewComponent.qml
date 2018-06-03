import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property alias source: img.source
    property alias emoji: emojiLabel.text
    anchors.fill: parent
    Column {
        width:parent.width

    Label{
        id:emojiLabel
        anchors.horizontalCenter:  parent.horizontalCenter
        font.pixelSize: Theme.fontSizeHuge
    }
    Image {
        id: img
        anchors.horizontalCenter:  parent.horizontalCenter

    }
    }

}
