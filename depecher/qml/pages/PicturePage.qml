import QtQuick 2.5
import Sailfish.Silica 1.0
import depecherUtils 1.0
import Nemo.Notifications 1.0
Page {
    id:root
    property alias imagePath: image.source
    allowedOrientations: Orientation.All
    SilicaFlickable{
        anchors.fill: parent
        FileWorker{
        id:fileWorker
        }
        Notification{
        id:imageSave
        appName: "Depecher"
        previewBody: "Saved!"
        }
        PullDownMenu{
            MenuItem{
                text:qsTr("Save to gallery")
                onClicked: {
                    fileWorker.savePictureToGallery(imagePath)
                    imageSave.publish()
                }
            }
        }

        Image{
            id: image
            width:parent.width
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            PinchArea {
                anchors.fill: parent
                pinch.target: parent
                pinch.minimumScale: 1
                pinch.maximumScale: 4
            }

        }
    }

}
