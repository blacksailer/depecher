import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.TransferEngine 1.0
//import Sailfish.Accounts 1.0
//import com.jolla.settings.accounts 1.0
import Sailfish.Gallery 1.0
import org.nemomobile.thumbnailer 1.0
SilicaFlickable {
    id:root
    property url urlOfSharingItem
    property var data
    property string attachmentId: ""
    property string attachmentPreview:""

    anchors.fill: parent
    contentHeight:vkShareMethodList.height+shareMethodList.height


    FileInfo {
        id: fileInfo
        source: root.urlOfSharingItem
    }

    SilicaListView{
        id:vkShareMethodList
        model:vkShareMethods
        width: parent.width
        height:(vkShareMethods.count+1)*Theme.itemSizeSmall+10
        header: PageHeader {
            //: List header for link sharing method list
            //% "Share link"
            title: qsTrId("Share")
        }

        delegate:BackgroundItem{
            height:Theme.itemSizeSmall

            Label{

                text:value
                x: Theme.paddingLarge
            }
            onClicked: {
                if(share_id==0)
                pageStack.push(Qt.resolvedUrl("../pages/DialogsPage.qml"),{attachmentId:attachmentId,attachmentPreview:attachmentPreview});
            }
        }

    }
    ShareMethodList {
        id: shareMethodList
        width:parent.width
        anchors.top:vkShareMethodList.bottom
        source:urlOfSharingItem

        filter: "image/jpeg"
        content : {
                              "title": "изображение из ВК",
                              "description": "изображение из ВК"
                          }
        /*                ShareMethodList {
                            id: shareMethodList
                            anchors.fill: parent

                            PullDownMenu {
                                MenuItem {
                                    text: qsTr("Сохранить картинку")
         .                           onClicked: {
                                        var picUri = listView.model[listView.currentIndex].photo_1280 ? listView.model[listView.currentIndex].photo_1280 : listView.model[listView.currentIndex].photo_604
                                        console.log(picUri)
                                        vkapi.img_save(picUri)
                                    }
                                }
                            }
                            header: PageHeader {
                                //: List header for link sharing method list
                                //% "Share link"
                                title: qsTrId("Поделиться")
                            }
                            filter: "text/x-url"
                              content: {
                                  "type": "text/x-url",
                                  "status": imagePage.imageUrl,
                                  "linkTitle": "изображение из ВК"
                              }

                            ViewPlaceholder {
                                enabled: shareMethodList.model.count === 0

                                //: Empty state for share link page
                                //% "No sharing accounts available. You can add accounts in settings"
                                text: qsTrId("sailfish_browser-la-no_accounts")
                            }

                        }*/
        /*
        delegate: BackgroundItem {
               id: backgroundItem
               width: root.width

               Label {
                   id: displayNameLabel
                   text: methodId
                   color: backgroundItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                   truncationMode: TruncationMode.Fade
                   x: Theme.paddingLarge
                   anchors.verticalCenter: parent.verticalCenter
                   width: Math.min(implicitWidth, parent.width - 2*Theme.paddingLarge)
               }

               Label {
                   text: userName
                   font.pixelSize: Theme.fontSizeMedium
                   color: backgroundItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                   truncationMode: TruncationMode.Fade
                   anchors {
                       left: displayNameLabel.right
                       leftMargin: Theme.paddingSmall
                       right: parent.right
                       rightMargin: Theme.paddingLarge
                       verticalCenter: parent.verticalCenter
                   }
                   visible: text.length > 0
               }

               onClicked: {                 
                   pageStack.push(shareUIPath, {
                       source: urlOfSharingItem,
                       content: content,
                       methodId: methodId,
                       displayName: displayName,
                       accountId: accountId,
                       accountName: userName
                   })
               }
           }
           */
        ViewPlaceholder {
            enabled: shareMethodList.model.count === 0

            //: Empty state for share link page
            //% "No sharing accounts available. You can add accounts in settings"
            text: qsTrId("sailfish_browser-la-no_accounts")
        }


    }

    ListModel{
        id:vkShareMethods
        ListElement{
            value:"Личным сообщением"
            share_id:0
        }
        ListElement{
            value:"На мою стену  (не реализ)"
            share_id:1
        }
        ListElement{
            value:"В группу  (не реализ)"
            share_id:2
        }
    }
}

