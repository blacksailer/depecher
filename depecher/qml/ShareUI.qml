import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.TransferEngine 1.0
import Nemo.DBus 2.0
import "pages/components"
import "org/blacksailer/depecher/sharechat" 1.0
import "js/mimetypes.js" as Mime
ShareDialog {
    id: root
    allowedOrientations: Orientation.Portrait

    property int viewWidth: root.isPortrait ? Screen.width : Screen.width / 2
    property var chat_ids: []

    property string filepath: source

    property bool searchEnabled: false
    Component.onCompleted:         console.log(filepath,JSON.stringify(content))
    canAccept: true
    onAccepted: {
        if (source == '' && content && 'type' in content)
        {
            shareItem.mimeType = content.type
            if(content.type === 'text/x-url') {
                shareItem.notificationsEnabled = false
                shareItem.userData = {"recipients":chat_ids.join(','), "name":content.linkTitle,
                    "data":content.status }
            }   else
                shareItem.userData = {"recipients":chat_ids.join(','),
                    "name":content.name,
                    "data":content.data}
        }
        else
            shareItem.userData = {"recipients":chat_ids.join(',')}

        shareItem.start()
    }

    ShareChatModel {
        id:model
    }
    SilicaListView {
        anchors.fill: parent
        model: model

        header:  PageHeader {
            title: chat_ids.length == 0 ? qsTr("Choose chat") :  qsTr("%1 selected").arg(chat_ids.length)
        }

        delegate: ChatItemShare {
            id: chatDelegate
            ListView.onAdd: AddAnimation {
                target: chatDelegate
            }

            ListView.onRemove: RemoveAnimation {
                target: chatDelegate
            }

            onClicked: {
                var contains = false
                for( var i = 0; i < chat_ids.length; i++)
                    if ( chat_ids[i] === id)
                        contains = true
                if(!contains)
                {
                    chat_ids.push(id)
                    highlighted = true
                }
                else {
                    for( var i = 0; i < chat_ids.length; i++){
                        if ( chat_ids[i] === id) {
                            highlighted = false
                            chat_ids.splice(i, 1);
                        }
                    }
                }
                console.log(chat_ids)
            }
        }
    }

    SailfishShare {
        id: shareItem
        source: root.filepath
        metadataStripped: true
        serviceId: root.methodId
        userData: {"description": "Depecher"}
        mimeType: Mime.getMimeType(filepath)
    }
}
