import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

Image {
    id:avata
    property alias source:avata.source
    property alias fallbackText:fallbacktext.text
    property alias fallbackItemVisible: fallbackitem.visible
    width:parent.height-5
    height: width

    layer.enabled:true
    layer.effect: OpacityMask {
        maskSource: Item {
            width: avata.width
            height: avata.height
            Rectangle {
                anchors.centerIn: parent
                width: avata.width
                height: avata.height
                radius: Math.min(width, height)
            }
        }
    }

    Rectangle {
        id: fallbackitem
        anchors.fill: parent
        color: Theme.highlightBackgroundColor
        radius: width * 0.5
        Label {
            id: fallbacktext
            font { bold: true; pixelSize: Theme.fontSizeLarge }
            anchors.centerIn: parent
            color: Theme.primaryColor
        }
    }
}


