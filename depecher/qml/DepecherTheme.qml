import QtQuick 2.1
import QtQuick.Window 2.1 as QtQuick
import Sailfish.Silica 1.0
import Sailfish.Silica.private 1.0
import Nemo.Configuration 1.0
//Rectangle {
//anchors.fill: parent
//color: "#121617"
//}

Wallpaper {
    id: wallpaper
    property string settingsUiPath:  "/apps/depecher/ui"
    ConfigurationValue {
        id:nightMode
        key:settingsUiPath + "/nightMode"
        defaultValue: false
    }
    Connections {
        target: nightMode
        onValueChanged: {
            if(nightMode.value)
                wallpaper.source = "qrc:/qml/assets/background/dark.jpg"
            else
                wallpaper.source = ""
        }
    }
    anchors.fill: parent
    rotation: parent.rotation
    state: rotation
//    source: Qt.resolvedUrl('file:///home/nemo/Pictures/Depecher/250821999_404787.jpg')

    states: [
        State {
            name: "0"
            PropertyChanges {
                target: wallpaper
                windowRotation: 0
            }
        },
        State {
            name: "180"
            PropertyChanges {
                target: wallpaper
                windowRotation: 180
            }
        },
        State {
            name: "270"
            PropertyChanges {
                target: wallpaper
                windowRotation: 270
            }
        },
        State {
            name: "90"
            PropertyChanges {
                target: wallpaper
                windowRotation: 90
                width: page.height
                height: page.width
            }
        }
    ]
Component.onCompleted:   {
      if(nightMode.value)
           wallpaper.source = "qrc:/qml/assets/background/dark.jpg"
}
}
