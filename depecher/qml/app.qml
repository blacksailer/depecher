import QtQuick 2.0
import Sailfish.Silica 1.0
import tdlibQtEnums 1.0
import TelegramModels 1.0
ApplicationWindow
{
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations
    initialPage: Qt.resolvedUrl("pages/DialogsPage.qml")
//    Component.onCompleted: {
////        if(c_telegramWrapper.authorizationState !== TdlibState.AuthorizationStateReady)
////            pageStack.push(Qt.resolvedUrl("pages/AuthorizeDialog.qml"))
////        else
////            pageStack.push(Qt.resolvedUrl("pages/DialogsPage.qml"))
//    }
}

