import QtQuick 2.0
import Sailfish.Silica 1.0
import tdlibQtEnums 1.0
import TelegramModels 1.0
ApplicationWindow
{
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations
    initialPage: Qt.resolvedUrl("pages/DialogsPage.qml")

    ////        if(c_telegramWrapper.authorizationState !== TdlibState.AuthorizationStateReady)
    ////            pageStack.push(Qt.resolvedUrl("pages/AuthorizeDialog.qml"))
    ////        else
    ////            pageStack.push(Qt.resolvedUrl("pages/DialogsPage.qml"))
    //    }
    onApplicationActiveChanged: {
        if(Qt.application.active)
        {
            var pages =[];
            var listPages = c_PageStarter.getPages();
            var page_dialog=Qt.resolvedUrl("pages/MessagingPage.qml")
            if(listPages.length>0)
            {
                pageStack.pushAttached(page_dialog,{chatId:listPages[0].pageParam})
                pageStack.navigateForward()
            }
        }
    }
}

