import QtQuick 2.0
import Sailfish.Silica 1.0
import tdlibQtEnums 1.0
import TelegramModels 1.0
import "items"
import "components"

Dialog {
    id: page
    property string selected_chat_id: ""
    property string from_chat_id: ""
    property var messages: []
    allowedOrientations: Orientation.All
    onAccepted: {
        var page = pageStack.find(function (page) {
            return page.__chat_page !== undefined;
        });
        if(page)
page._opened_chat_id = ""
        pageStack.replaceAbove(page,Qt.resolvedUrl("MessagingPage.qml"),{"chatId":selected_chat_id,
                              "forwardMessages":{
                             "selected_chat_id":selected_chat_id,
                             "from_chat_id":from_chat_id,
                             "messages":messages
                         }})
    }
    canAccept: selected_chat_id !== ""
    ChatsModel{
        id:chatsModel
    }
    SilicaListView {
        anchors.fill: parent
        model:chatsModel
        header:  DialogHeader {
            acceptText:  qsTr("Select chat")
        }

        delegate: ChatItem {
            id: chatDelegate
            highlighted: id === selected_chat_id

            ListView.onAdd: AddAnimation {
                target: chatDelegate
            }

            ListView.onRemove: RemoveAnimation {
                target: chatDelegate
            }

            onClicked: {
                    selected_chat_id = id
            }
        }
    }

}
