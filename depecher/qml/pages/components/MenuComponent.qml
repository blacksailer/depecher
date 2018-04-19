import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramItems 1.0
import "../items"

SilicaListView{
    anchors.fill: parent
    model:menuModel
    header: Column{
        width:parent.width
        Item{
            //topPadding
            width: parent.width
            height: Theme.paddingMedium
        }
        spacing: Theme.paddingLarge
        Row{
            width: parent.width
            Item {
                width: Theme.paddingSmall
                height: 1
            }
            CircleImage {
                id: avatar
                width:height
                height: 135
                source: aboutMe.photoPath ? "image://depecherDb/"+aboutMe.photoPath : ""
                fallbackText: aboutMe.firstName.charAt(0)
                fallbackItemVisible: aboutMe.photoPath ? false : true
            }
        }
        AboutMeDAO{
        id:aboutMe
        }
        Row{
            width:parent.width
            Item {
                width: Theme.paddingSmall
                height: 1
            }
            Column{
                width:parent.width-button.width
                Label{
                    text:aboutMe.fullName
                    color:Theme.highlightColor
                }
                Label{
                    text:aboutMe.phoneNumber
                    color:Theme.secondaryHighlightColor

                }
            }
            IconButton{
                id:button
                icon.source: "image://theme/icon-s-cloud-upload?" + (pressed
                                                                     ? Theme.highlightColor
                                                                     : Theme.primaryColor)
                onClicked:{
                    pageStack.push("../MessagingPage.qml",{userName:aboutMe.fullName,chatId:aboutMe.id,chatType:0,
                                   lastReadMessage:0,lastMessageId:0})
                }
            }
        }
        Separator{
        width:parent.width
        color:Theme.primaryColor
        }
        Item{
            //bottomPadding
            width: parent.width
            height: 1
        }

    }

    delegate:BackgroundItem {
        width:parent.width
        height:Theme.itemSizeExtraSmall
        Row{
            width:parent.width
            anchors.verticalCenter:  parent.verticalCenter
            spacing: Theme.paddingSmall
            Item {
                width: Theme.paddingSmall
                height:1
            }
            Image {
                id:iconSmall
                width: height
                height: textLabel.height*2/3
                source: "image://theme/"+menuIcon+ "?"+(parent.parent.pressed
                                                        ? Theme.highlightColor
                                                        : Theme.primaryColor)
            }
            Label{
                id:textLabel
                text:menuText
                anchors.verticalCenter:  iconSmall.verticalCenter
            }
        }
        onClicked:{

            pageStack.push(menuPage)

        }
    }
    ListModel{
        id:menuModel
//        ListElement{
//            menuText:qsTr("New Group")
//            menuIcon: "icon-s-group-chat"
//            menuPage:""
//        }
//        ListElement{
//            menuText:qsTr("New Secret Chat")
//            menuIcon:"icon-s-secure"
//            menuPage:""
//        }
//        ListElement{
//            menuText:qsTr("New Channel")
//            menuIcon:"icon-m-media-radio"
//            menuPage:""
//        }
//        ListElement{
//            menuText:qsTr("Contacts")
//            menuIcon:"icon-m-media-artists"
//            menuPage:"ContactsPage.qml"
//        }
        ListElement{
            menuText:qsTr("Settings")
            menuIcon:"icon-s-setting"
            menuPage:"../SettingsPage.qml"
        }
    }
}
