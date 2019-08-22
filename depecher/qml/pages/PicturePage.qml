//Based on work of user - @dysk0
//https://github.com/dysk0/harbour-pingviini/blob/b8f62a15b86b8021ea37c426fa6da6ac6191e81f/qml/pages/ImageFullScreen.qml
import QtQuick 2.5
import Sailfish.Silica 1.0
import depecherUtils 1.0
import org.nemomobile.notifications 1.0

Page {
    id:root
    property alias imagePath: imagePreview.source
    property int remoteFileId
    allowedOrientations: Orientation.All
    backNavigation: drawer.opened
    FileWorker{
        id:fileWorker
    }
    Notification{
        id:imageSave
        appName: "Depecher"
        previewBody: qsTr("Image saved to gallery!")
    }
    Drawer {
        id:drawer
        anchors.fill: parent
        dock: root.isLandscape ? Dock.Left : Dock.Top
        Flickable {
            id: imageFlickable
            anchors.fill: parent
            contentWidth: imageContainer.width; contentHeight: imageContainer.height
            clip: true
            onHeightChanged: if (imagePreview.status === Image.Ready) imagePreview.fitToScreen();
            Item {
                id: imageContainer
                width: Math.max(imagePreview.width * imagePreview.scale, imageFlickable.width)
                height: Math.max(imagePreview.height * imagePreview.scale, imageFlickable.height)

                Image {
                    id: imagePreview

                    property real prevScale

                    function fitToScreen() {
                        scale = Math.min(imageFlickable.width / width, imageFlickable.height / height, 1)
                        pinchArea.minScale = scale
                        prevScale = scale
                    }

                    anchors.centerIn: parent
                    fillMode: Image.PreserveAspectFit
                    cache: true
                    asynchronous: true
                    sourceSize.width:  root.width;
                    smooth: false

                    onScaleChanged: {
                        if ((width * scale) > imageFlickable.width) {
                            var xoff = (imageFlickable.width / 2 + imageFlickable.contentX) * scale / prevScale;
                            imageFlickable.contentX = xoff - imageFlickable.width / 2
                        }
                        if ((height * scale) > imageFlickable.height) {
                            var yoff = (imageFlickable.height / 2 + imageFlickable.contentY) * scale / prevScale;
                            imageFlickable.contentY = yoff - imageFlickable.height / 2
                        }
                        prevScale = scale
                    }
                }
            }

            PinchArea {
                id: pinchArea
                opacity: 0.3
                property real minScale: 1.0
                property real maxScale: 3.0

                anchors.fill: parent
                enabled: imagePreview.status === Image.Ready
                pinch.target: imagePreview
                pinch.minimumScale: minScale * 0.5 // This is to create "bounce back effect"
                pinch.maximumScale: maxScale * 1.5 // when over zoomed

                onPinchFinished: {
                    imageFlickable.returnToBounds()
                    if (imagePreview.scale < pinchArea.minScale) {
                        bounceBackAnimation.to = pinchArea.minScale
                        bounceBackAnimation.start()
                    }
                    else if (imagePreview.scale > pinchArea.maxScale) {
                        bounceBackAnimation.to = pinchArea.maxScale
                        bounceBackAnimation.start()
                    }
                }
                NumberAnimation {
                    id: bounceBackAnimation
                    target: imagePreview
                    duration: 250
                    property: "scale"
                    from: imagePreview.scale
                }
                MouseArea {
                    anchors.fill: parent
                    enabled: true//imagePreview.status === Image.Ready
                    onClicked: drawer.open = !drawer.open
                }
            }

        }

        background: SilicaFlickable {
            anchors.fill: parent
            PullDownMenu {
                MenuItem {
                    text: qsTr("Save to gallery")
                    onClicked: {
                        fileWorker.savePictureToGallery(imagePath)
                        imageSave.publish()
                    }
                }
            }
            ViewPlaceholder {
                enabled: true
                anchors.centerIn: parent
                text: qsTr("Share function will be here soon")
            }
        }
    }
}
