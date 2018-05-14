import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id:root
    SilicaListView{
        id:list
        anchors.fill: parent
        model:c_telegramWrapper.contactsModel
        delegate:ListItem{
            width: parent.width
            height:Theme.itemSizeMedium
            Column{
                id:data
                x:Theme.horizontalPageMargin
                width:parent.width-2*x
                Label{
                    text:fullName
                }
                Label{
                    text:status
                }
            }

            onClicked:{
                c_telegramWrapper.chatId=peerId
                //peerType 0 - is User
                    c_telegramWrapper.requestHistory(c_telegramWrapper.chatId,0, 20,0);
                        pageStack.replace("MessagingPage.qml",{peerType:0})
            }
        }
    }
}
