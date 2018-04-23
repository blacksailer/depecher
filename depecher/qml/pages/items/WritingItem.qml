import QtQuick 2.0
import Sailfish.Silica 1.0

Drawer{
    id:attachDrawer
    state: "publish"

    property int sendAreaHeight: sendArea.height
    property alias bottomArea: sendArea
    property alias actionButton: sendButton
    property alias text: messageArea.text
    property alias textArea:messageArea
    property int wall_id:0
    property string typeWriter
//    signal addPhotoId(var json,var indx);

    states: [
    State{
            name:"publish"
        },
        State{
        name:"edit"
        }
    ]

//    onAddPhotoId:
//    {
//        var obj = JSON.parse(json)
//        c_attachmentsModelToSend.setPhotoAttachmentId(obj.response[0].id,indx)
//    }
    open:false
    dock:Dock.Bottom
    anchors.fill: parent



    Item{
        id:sendArea
        anchors.bottom: parent.bottom
        width: parent.width
        height: messageArea.height+attachmentstoSend.height+replyArea.height+Theme.paddingSmall
        Item{
            id:replyArea
            width: parent.width
            height: reply_id!=-1?Theme.itemSizeExtraSmall:0
            anchors.bottom: attachmentstoSend.top

            Rectangle{
                id:replyLine
                width:3
                height: parent.height
                color:Theme.secondaryHighlightColor
                anchors.left: parent.left
                anchors.leftMargin: 8

            }
            Column{
                id:data
                anchors.left: replyLine.right
                anchors.leftMargin: Theme.paddingLarge
                anchors.right: removeReplyButton.left
                Label{
                    font.pixelSize: Theme.fontSizeExtraSmall
                    width: parent.width
                    text:author
                    elide: TruncationMode.Fade
                    height:authorsTextLabel.text==""?removeReplyButton.height :implicitHeight
                }
                Label{
                    id:authorsTextLabel
                    font.pixelSize: Theme.fontSizeExtraSmall
                    width: parent.width
                    text:authorsText
                    elide: TruncationMode.Fade
                    visible: authorsText!=""


                }
            }
            IconButton{
                id:removeReplyButton
                icon.source: "image://theme/icon-s-clear-opaque-cross?"+Theme.highlightColor
                anchors.right: parent.right
                anchors.rightMargin: Theme.paddingLarge
                visible: parent.height!=0
                onClicked: {
                    author=""
                    authorsText=""
                    reply_id=-1
                    if(writer.state=="edit")
                        writer.state="publish"
                }
            }
        }
        SilicaListView{
            id:attachmentstoSend
            width:parent.width
            height: attachmentstoSend.count>0?Theme.itemSizeMedium:0
            anchors.bottom: messageArea.top
//            model:c_attachmentsModelToSend
            orientation:Qt.Horizontal
            spacing:5
            delegate: Image{
                width:Theme.itemSizeMedium
                height:width
                sourceSize: Qt.size(width,height)
                IconButton{
                    icon.source: "image://theme/icon-s-clear-opaque-cross?"+Theme.highlightColor
                    anchors.centerIn: parent
                    onClicked: c_attachmentsModelToSend.removeAttachment(index)
                    Component.onCompleted: {
                        switch(type) {
                        case 0: //        PHOTO
                            if(c_source.substring(0,4)!=="http")
                                source="image://nemoThumbnail/"+c_source
                            else
                                source = c_source
                            break;
                        case 1: //        VIDEO
                            if(c_source.substring(0,4)!=="http")
                                source="image://nemoThumbnail/"+c_source
                            else
                                source = c_source
                            break;
                        case 2://        AUDIO
                            source="image://theme/icon-m-file-audio"
                            break;
                        case 3://        DOC
                            source="image://theme/icon-m-document"
                            break;
                        case 4://        WALL
                            source="image://theme/icon-m-other"
                            break;

                        }

                    }
                }
                Rectangle{
                    color:"black"
                    visible: c_status>0
                    opacity: 0.5
                    anchors.fill: parent
                }
                ProgressCircle {
                    id: progressCircle

                    anchors.centerIn: parent
                    value: c_progress
                    visible: c_status>0

                }
            }
        }
        IconButton {
            id:skrepkaWizard
            icon.source: "image://theme/icon-m-attach"
            highlighted: false
            anchors.bottom: messageArea.bottom
            anchors.right:messageArea.left
            anchors.bottomMargin: 25
            onClicked: attachDrawer.open=true
            width:0
            visible: false
        }
        TextArea {
            id:messageArea

            anchors.bottom: parent.bottom
            anchors.right: sendButton.left

            height:  Math.min(Theme.itemSizeHuge,implicitHeight)//Math.max(page.height/5, Math.min(page.height/3,implicitHeight))
            width:parent.width-sendButton.width- skrepkaWizard.width
        }

        IconButton {
            id:sendButton
            icon.source: "image://theme/icon-m-message"
            highlighted: false
            anchors.bottom: messageArea.bottom
            //                anchors.left:messageArea.right
            anchors.right:parent.right
            anchors.bottomMargin: 25

        }
    }


    MouseArea {
        enabled: attachDrawer.open
        anchors.fill: listView
        onClicked: attachDrawer.open = false
    }


    background:Loader{
        id:attachLoader
        anchors.fill: parent
    }

    Connections {
        target: attachLoader.item
        onS_items: {
            console.log(items)
            var types = ["photo","audio","doc","video","wall","place","photoVK","videoVK"];
            for(var i=0;i<items.length;i++)
            {
                console.log(items[i].url);
                var file = items[i].url;
                console.log(file)
                c_attachmentsModelToSend.addAttachment(file,types[items[i].type])
            }
        }
    }

    onOpenedChanged:
    {
        if(opened)
            attachLoader.setSource("AttachComponent.qml")
        else
            attachLoader.sourceComponent=undefined
    }
}
