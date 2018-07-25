import QtQuick 2.0
import Sailfish.Silica 1.0
import tdlibQtEnums 1.0
import TelegramModels 1.0
import "items"
import "components"


Page {
    id: page
    allowedOrientations: Orientation.All
    ChatsModel{
        id:chatsModel
    }

    property string titleHeader: "Depecher"
    //for search in pageStack
    property bool __chat_page: true
    property string _opened_chat_id: ""

    SilicaListView {
        anchors.fill: parent
        model:chatsModel
        header:  PageHeader {
            title: titleHeader
        }

        PullDownMenu {
            MenuItem {
                text:qsTr("Reset dialogs")
                onClicked: chatsModel.reset()
            }
            MenuItem {
                text:qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
            }
        }

        delegate: ChatItem {
            id: chatDelegate

            ListView.onAdd: AddAnimation {
                target: chatDelegate
            }

            ListView.onRemove: RemoveAnimation {
                target: chatDelegate
            }

            onClicked:{
                var page = pageStack.find(function (page) {
                    return page.__messaging_page !== undefined
                });
                if(_opened_chat_id !== id)
                {
                    _opened_chat_id = id
                    pageStack.pushAttached("MessagingPage.qml",{chatId:id})
                }
                pageStack.navigateForward()
            }
        }
    }


    Connections {
        target: c_telegramWrapper
        onErrorReceivedMap:{
            if(errorObject["code"] === 401)
                pageStack.replace(Qt.resolvedUrl("AuthorizeDialog.qml"))
        }
    }
}
