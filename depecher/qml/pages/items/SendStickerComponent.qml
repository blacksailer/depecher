import QtQuick 2.0
import Sailfish.Silica 1.0


Item {
    id:root
    anchors.fill: parent
    Column {
        width: parent.width
        height: parent.height
        ListView {
            width: parent.width
            height: Theme.itemSizeSmall
            model: 5
            orientation:ListView.Horizontal
            delegate: Image {
                anchors.fill: parent
                source: "image://theme/icon-s-alarm"
                MouseArea {
                    anchors.fill: parent
                }
            }
        }
        SilicaGridView {
            id:stickersGrid
            anchors.fill: parent
            model: 7

        }
    }
}
