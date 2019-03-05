import QtQuick 2.0
import Sailfish.Silica 1.0 
import tdlibQtEnums 1.0
import TelegramModels 1.0
import QtMultimedia 5.6
import Nemo.Configuration 1.0


ApplicationWindow
{
    id:rootWindow
    property alias __depecher_audio: playMusic
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations
    _defaultPageOrientations: allowedOrientations
    initialPage: Qt.resolvedUrl("pages/DialogsPage.qml")


    ////        if(c_telegramWrapper.authorizationState !== TdlibState.AuthorizationStateReady)
    ////            pageStack.push(Qt.resolvedUrl("pages/AuthorizeDialog.qml"))
    ////        else
    ////            pageStack.push(Qt.resolvedUrl("pages/DialogsPage.qml"))
    //    }

    Component.onCompleted: {
        var component = Qt.createComponent("Background.qml");
        var wallpaper = component.createObject(rootWindow._wallpaperItem,{});

        if (wallpaper == null) {
            console.log("Error creating object");
        }
    }

    Audio {
        id: playMusic
        audioRole: Audio.MusicRole
        onError: console.log(error,errorString)
    }
    onApplicationActiveChanged: {
        if(Qt.application.active)
        {
            var pages =[];
            var listPages = c_PageStarter.getPages();
            var page_dialog=Qt.resolvedUrl("pages/MessagingPage.qml")
            if(listPages.length>0)
            {
                var page = pageStack.find(function (page) {
                    return page.__chat_page !== undefined;
                });
                if(pageStack.depth > 1)
                    pageStack.popAttached(page,PageStackAction.Immediate)
                page._opened_chat_id = listPages[0].pageParam
                pageStack.pushAttached(page_dialog,{chatId:listPages[0].pageParam})
                pageStack.navigateForward()
            }
        }
    }

    property string settingsUiPath:  "/apps/depecher/ui"
    ConfigurationValue {
        id:nightMode
        key:settingsUiPath + "/nightMode"
        defaultValue: false
    }
    ConfigurationValue {
        id:nightModeSchedule
        key:settingsUiPath + "/nightModeSchedule"
        defaultValue: false
    }
    ConfigurationValue {
        id:nightModeFrom
        key:settingsUiPath + "/nightModeFrom"
        defaultValue: ""
    }
    ConfigurationValue {
        id:nightModeTill
        key:settingsUiPath + "/nightModeTill"
        defaultValue: ""
    }
    Timer {
        id:nightModeScheduleTimer
        interval: 1000 * 2
        repeat: true
        running: nightModeSchedule.value
        onTriggered: {
            // in minutes
            var curr = new Date().getHours() * 60 + new Date().getMinutes()
            var from = new Date(nightModeFrom.value).getHours() * 60 + new Date(nightModeFrom.value).getMinutes()
            var till = new Date(nightModeTill.value).getHours() * 60 + new Date(nightModeTill.value).getMinutes()
            if(from <= till) {
                if(curr >= from && curr < till)
                {
                    nightMode.value = true
                    nightMode.sync()
                }
                else {
                    nightMode.value = false
                    nightMode.sync()
                }
            } else if (from > till) {
                if(curr < till || curr > from)
                {
                    nightMode.value = true
                    nightMode.sync()
                }            else {
                    nightMode.value = false
                    nightMode.sync()
                }

            }

        }
    }
}

