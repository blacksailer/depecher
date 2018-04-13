import QtQuick 2.0
import Sailfish.Silica 1.0
import tdlibQtEnums 1.0
import TelegramModels 1.0
ApplicationWindow
{
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations
    QtObject {
        id: registrationStatus
        readonly property int unknown: 0
        readonly property int notRegistered: 1
        readonly property int registered: 2
        readonly property int error: 3
    }
    ChatsModel{
        id:chatsModel
    }
    Connections {
    target: c_telegramWrapper
    onAuthorizationStateChanged:{
        if(c_telegramWrapper.authorizationState === TdlibState.AuthorizationStateWaitPhoneNumber) {
            pageStack.replace(Qt.resolvedUrl("pages/AuthorizeDialog.qml"))
        }
        if(c_telegramWrapper.authorizationState === TdlibState.AuthorizationStateReady) {
            pageStack.replace(Qt.resolvedUrl("pages/DialogsPage.qml"))
        }
    }
    }
    Component.onCompleted: {
//        if(c_telegramWrapper.authorizationState !== TdlibState.AuthorizationStateReady)
//            pageStack.push(Qt.resolvedUrl("pages/AuthorizeDialog.qml"))
//        else
//            pageStack.push(Qt.resolvedUrl("pages/DialogsPage.qml"))
    }
}

