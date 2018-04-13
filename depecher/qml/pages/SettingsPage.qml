import QtQuick 2.0
import Sailfish.Silica 1.0
Page {
    id:root

    SilicaFlickable{
        anchors.fill: parent
        Column{
            width: parent.width
            Button{
                text:qsTr("LogOut")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    c_telegramWrapper.logOut()
                    pageStack.replaceAbove(null,Qt.resolvedUrl("AuthorizeDialog.qml"));
                }
            }
        }
    }

}
