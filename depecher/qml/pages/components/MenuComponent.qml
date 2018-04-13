import QtQuick 2.0
import Sailfish.Silica 1.0

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
            Rectangle{
                width:Theme.itemSizeMedium
                height: width
                radius: 90
                color:"red"
            }
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
                    text:c_selfItem.name
                    color:Theme.highlightColor
                }
                Label{
                    text:c_selfItem.peerId
                    color:Theme.secondaryHighlightColor

                }
            }
            IconButton{
                id:button
                icon.source: "image://theme/icon-s-cloud-upload?" + (pressed
                                                                     ? Theme.highlightColor
                                                                     : Theme.primaryColor)
                onClicked:{
                    pageStack.push("MessagingPage.qml",{peerType:-1,chatId:c_selfItem.peerId})
                }
            }
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
        onClicked: pageStack.push(menuPage)
    }
    ListModel{
        id:menuModel
        ListElement{
            menuText:qsTr("New Group")
            menuIcon: "icon-s-group-chat"
            menuPage:""
        }
        ListElement{
            menuText:qsTr("New Secret Chat")
            menuIcon:"icon-s-secure"
            menuPage:""
        }
        ListElement{
            menuText:qsTr("New Channel")
            menuIcon:"icon-m-media-radio"
            menuPage:""
        }
        ListElement{
            menuText:qsTr("Contacts")
            menuIcon:"icon-m-media-artists"
            menuPage:"ContactsPage.qml"
        }
        ListElement{
            menuText:qsTr("Settings")
            menuIcon:"icon-s-setting"
            menuPage:"../SettingsPage.qml"
        }
    }
}
