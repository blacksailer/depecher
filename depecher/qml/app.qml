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
            for(var i =0; i< listPages.length;i++)
            {
                    var page_dialog=Qt.resolvedUrl("pages/MessagingPage.qml")
                    pages.push({page:page_dialog,properties:{chatId:listPages[i].pageParam}});
                    break;

            }
            if(pages.length>0)
                pageStack.push(pages)
        }
    }
}

