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

    Drawer {
        id:drawer
        anchors.fill: parent
        dock:Dock.Left
        backgroundSize: parent.width*2/3
        SilicaListView {
            anchors.fill: parent
            opacity: drawer.open ? 0.5 : 1
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
                    c_telegramWrapper.openChat(id)
                    pageStack.push("MessagingPage.qml",{userName:title,chatId:id,chatType:type,
                                       lastReadMessage:last_message_inbox_id,
                                       lastOutboxId:last_message_outbox_id,lastMessageId:last_message_id})
                }
            }
        }

        MouseArea {
            anchors.fill: parent
            enabled: drawer.open
            onClicked: drawer.hide()
        }

        background: MenuComponent{
            id:menuList
        }
    }
}
