import QtQuick 2.6
import Sailfish.Silica 1.0
import TelegramModels 1.0
import "items"

Page {
    id:root
    SilicaFlickable {
        anchors.fill: parent
        PullDownMenu {
            MenuItem {
                text: qsTr("Search")
                onClicked: list.showSearch = true
            }
        }

        Column {
            id:header
            width:parent.width
            PageHeader {
                title: qsTr("Contacts")
            }

            SearchField {
                id:searchField
                width: parent.width
                height: list.showSearch ? implicitHeight : 0
                opacity: list.showSearch ? 1 : 0
                onTextChanged: {
                    filterModel.setFilterFixedString(text)
                }

                Connections {
                    target: list
                    onShowSearchChanged: {
                        searchField.forceActiveFocus()
                    }
                }

                Behavior on height {
                    NumberAnimation { duration: 300 }
                }
                Behavior on opacity {
                    NumberAnimation { duration: 300 }
                }
            }
        }
        SilicaListView {
            id:list
            width: parent.width
            anchors.top: header.bottom
            anchors.bottom: parent.bottom
            property bool showSearch: false
            clip:true
            model:FilterContactsModel {
                id:filterModel
                sortRole:2
                source:ContactsModel {

                }

                Component.onCompleted: sortModel(Qt.AscendingOrder)
            }
            delegate:ListItem {
                width: parent.width
                contentHeight:Theme.itemSizeMedium
                Row {
                    width:parent.width-2*x
                    x:Theme.horizontalPageMargin
                    height: parent.height
                    anchors.verticalCenter: parent.verticalCenter
                    CircleImage {
                        id:avatar
                        width: parent.height - 2 * Theme.paddingSmall
                        source: photo ? photo : ""
                        fallbackText: last_name == ""? first_name.charAt(0) :last_name.charAt(0)
                        fallbackItemVisible: photo ? false : true
                        anchors.verticalCenter: parent.verticalCenter


                    }
                    Item {
                        width:Theme.paddingMedium
                        height:1
                    }
                    Column{
                        id:data
                        width:parent.width-avatar.width
                        anchors.verticalCenter: avatar.verticalCenter
                        Label{
                            id:text
                            width:parent.width
                            elide: Text.ElideRight
                            text:last_name + " "  + first_name
                            color: pressed?Theme.secondaryHighlightColor:Theme.highlightColor
                            font.pixelSize: Theme.fontSizeSmall
                        }
                        Label{
                            text:status
                            color: Theme.secondaryColor
                            font.pixelSize: Theme.fontSizeExtraSmall

                        }
                    }
                }

                onClicked: {
                    pageStack.replace("MessagingPage.qml",{chatId:user_id})

                }
            }
        }
    }
}
