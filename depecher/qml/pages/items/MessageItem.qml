import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0

ListItem {
    id:messageListItem
    width:parent.width
    contentHeight: columnWrapper.height
    Component.onCompleted: {console.log(content)}

    Column{
        id:columnWrapper
        width:contentWrapper.width
        height: contentWrapper.height
        anchors.right: is_outgoing ? parent.right : undefined
        anchors.left: is_outgoing ?  undefined : parent.left
        anchors.rightMargin: is_outgoing ? Theme.horizontalPageMargin : 0
        anchors.leftMargin: is_outgoing ?  0 : Theme.horizontalPageMargin
        Row {
            id:contentWrapper
            spacing: Theme.paddingMedium
            width: userAvatar.width + contentLoader.width + spacing
            height: Math.max(userAvatar.height,contentLoader.height)
layoutDirection: is_outgoing ? Qt.RightToLeft : Qt.LeftToRight
            CircleImage {
                id:userAvatar
                width:visible ? 0 : Theme.itemSizeExtraSmall
                anchors.bottom: contentLoader.bottom
                source: sender_photo ? "image://depecherDb/"+sender_photo : ""
                fallbackText: author.charAt(0)
                fallbackItemVisible:  sender_photo ? false : true
                visible: !is_outgoing && message_type != 3 &&
                         messagingModel.chatType !== TdlibState.Channel &&
                         messagingModel.chatType !== TdlibState.Private &&
                         messagingModel.chatType !== TdlibState.Secret
            }
            Loader {
                id:contentLoader
                focus:true
                Component.onCompleted:  {
                    if(message_type == MessagingModel.TEXT)
                        sourceComponent = textContent
                    if(message_type == MessagingModel.PHOTO)
                        sourceComponent = imageContent
                    if(message_type == MessagingModel.STICKER)
                        sourceComponent = stickerContent
                    if(message_type == MessagingModel.SYSTEM_NEW_MESSAGE)
                        sourceComponent = newMessageContent
                    if(message_type == MessagingModel.DOCUMENT)
                        sourceComponent = documentContent
                }
                Component {
                    id:textContent
                    Column{
                        id:textColumn
                        width:textItem.width
                        Row{
                            id:subInfoRow
                            width:parent.width
                            Label {
                                visible: messagingModel.chatType === TdlibState.BasicGroup ?
                                             true :
                                             messagingModel.chatType === TdlibState.Supergroup ? true
                                                                                              : false
                                id:authorName
                                //                                        width:Math.max(parent.width*4/5,implicitWidth)
                                text:author
                                color: pressed ?Theme.highlightColor: Theme.secondaryHighlightColor
                                font.pixelSize: Theme.fontSizeExtraSmall
                                truncationMode: TruncationMode.Fade
                            }
                        }

                        LinkedLabel {
                            id:textItem
                            width: text.length<32 ? paintedWidth : Screen.width * 2 /3 - Theme.horizontalPageMargin * 2
                            plainText:content ? content : ""
                            color: pressed ? Theme.secondaryColor : Theme.primaryColor
                            linkColor: pressed ? Theme.secondaryHighlightColor : Theme.highlightColor
                            font.pixelSize: Theme.fontSizeSmall
                            wrapMode: Text.WordWrap
                        }
                        Separator{
                            color:pressed ? Theme.primaryColor : Theme.secondaryColor
                            width:parent.width/3
                        }
                        Row {
                            id:metaInfoRow
                            width:parent.width
                            layoutDirection: is_outgoing ? Qt.RightToLeft : Qt.LeftToRight
                            Label{
                                function timestamp(dateTime){
                                    var dateTimeDate=new Date(dateTime*1000)

                                    var datetime_day = dateTimeDate.getDay()
                                    var currentDay = new Date().getDay()

                                    if (datetime_day==currentDay)
                                        return Format.formatDate(dateTimeDate, Formatter.TimeValue)
                                    else
                                        return Format.formatDate(dateTimeDate, Formatter.DateMediumWithoutYear)
                                }
                                font.pixelSize: Theme.fontSizeTiny
                                color:pressed ? Theme.primaryColor : Theme.secondaryColor
                                text:timestamp(date)
                            }

                        }
                    }
                }
                Component {
                    id:imageContent
                    Column{
                        width:image.maxWidth
                        Row{
                            id:subInfoRow
                            width:parent.width
                            Label {
                                visible: messagingModel.chatType == TdlibState.BasicGroup ?  true :
                                                                                            messagingModel.chatType == TdlibState.Supergroup ? true
                                                                                                                                             : false
                                id:authorName
                                //                                        width:Math.max(parent.width*4/5,implicitWidth)
                                text:author
                                color: pressed ?Theme.highlightColor: Theme.secondaryHighlightColor
                                font.pixelSize: Theme.fontSizeExtraSmall
                                truncationMode: TruncationMode.Fade
                            }
                        }

                        Image {
                            id:image
                            property int maxWidth: Screen.width-Theme.itemSizeExtraSmall - Theme.paddingMedium - 2*Theme.horizontalPageMargin
                            property int maxHeight: Screen.height/2
                            width: photo_aspect > 1 ? maxWidth : maxHeight * photo_aspect
                            height: photo_aspect > 1 ? maxWidth/photo_aspect : maxHeight
                            fillMode: Image.PreserveAspectFit
                            source:"image://depecherDb/"+content
                            MouseArea{
                                anchors.fill: parent
                                enabled: file_downloading_completed
                                onClicked: pageStack.push("../PicturePage.qml",{imagePath:content})
                            }
                            ProgressCircle {
                                id:progress
                                anchors.centerIn: parent

                                visible: file_is_uploading || file_is_downloading
                                value : file_is_uploading ? file_uploaded_size / file_downloaded_size :
                                                            file_downloaded_size / file_uploaded_size
                            }
                            Image {
                                id: downloadIcon
                                visible: !file_downloading_completed || progress.visible
                                source: progress.visible ? "image://theme/icon-s-clear-opaque-cross"
                                                         : "image://theme/icon-s-update"
                                anchors.centerIn: parent
                                MouseArea{
                                    enabled: parent.visible
                                    anchors.fill: parent
                                    onClicked: {
                                        if(progress.visible)
                                            if(file_is_downloading)
                                                messagingModel.cancelDownload(index)
                                            else
                                                messagingModel.cancelUpload(index)
                                        else
                                            messagingModel.downloadDocument(index)
                                    }
                                }
                            }

                        }
                        LinkedLabel {
                            width: parent.width
                            plainText:file_caption
                            color: pressed ? Theme.secondaryColor :Theme.primaryColor
                            linkColor: pressed ? Theme.secondaryHighlightColor :Theme.highlightColor
                            font.pixelSize: Theme.fontSizeSmall
                            wrapMode: Text.WordWrap
                            visible:  file_caption === "" ? false : true
                        }
                        Separator{
                            color:pressed ? Theme.primaryColor : Theme.secondaryColor
                            width:parent.width/3
                        }
                        Row {
                            id:metaInfoRow
                            width:parent.width
                            layoutDirection: is_outgoing ? Qt.RightToLeft : Qt.LeftToRight
                            Label{
                                function timestamp(dateTime){
                                    var dateTimeDate=new Date(dateTime*1000)

                                    var datetime_day = dateTimeDate.getDay()
                                    var currentDay = new Date().getDay()

                                    if (datetime_day==currentDay)
                                        return Format.formatDate(dateTimeDate, Formatter.TimeValue)
                                    else
                                        return Format.formatDate(dateTimeDate, Formatter.DateMediumWithoutYear)
                                }
                                font.pixelSize: Theme.fontSizeTiny
                                color:pressed ? Theme.primaryColor : Theme.secondaryColor
                                text:timestamp(date)
                            }

                        }

                    }
                }
                Component {
                    id:documentContent
                    Column{
                        property int maxWidth: Screen.width *2/3 - Theme.horizontalPageMargin * 2
                        width:maxWidth

                        Row{
                            id:subInfoRow
                            width:parent.width
                            Label {
                                visible: messagingModel.chatType == TdlibState.BasicGroup ?  true :
                                                                                            messagingModel.chatType == TdlibState.Supergroup ? true
                                                                                                                                             : false
                                id:authorName
                                //                                        width:Math.max(parent.width*4/5,implicitWidth)
                                text:author
                                color: pressed ?Theme.highlightColor: Theme.secondaryHighlightColor
                                font.pixelSize: Theme.fontSizeExtraSmall
                                truncationMode: TruncationMode.Fade
                            }
                        }
BackgroundItem {
    width:parent.width
    height: Theme.itemSizeMedium
    enabled: file_downloading_completed && !file_is_uploading
    onClicked:        Qt.openUrlExternally("file://"+content)


                        Row{
                            id:documentRowWrapper
                            width:parent.width
                            spacing: Theme.paddingMedium
                            height: parent.height
                            Image {
                                id:image
                                fillMode: Image.PreserveAspectFit
                                source:"image://theme/icon-m-file-document"
                                anchors.verticalCenter: parent.verticalCenter

                                ProgressCircle {
                                    id:progress
                                    anchors.fill: parent
                                    visible: file_is_uploading || file_is_downloading
                                    value : file_is_uploading ? file_uploaded_size / file_downloaded_size :
                                                                file_downloaded_size / file_uploaded_size
                                }
                                Image {
                                    id: downloadIcon
                                    visible: !file_downloading_completed || progress.visible
                                    source: progress.visible ? "image://theme/icon-s-clear-opaque-cross"
                                                             : "image://theme/icon-s-update"
                                    anchors.centerIn: parent
                                }
                                MouseArea{
                                    enabled: downloadIcon.visible
                                    anchors.fill: parent
                                    onClicked: {
                                        console.log("CANCEL!!!!!!!!")
                                        if(progress.visible)
                                            if(file_is_downloading)
                                                messagingModel.cancelDownload(index)
                                            else
                                                messagingModel.cancelUpload(index)
                                        else
                                            messagingModel.downloadDocument(index)
                                    }
                                }

                            }

                            Column{
                                width: parent.width - image.width - parent.spacing
                                spacing: Theme.paddingSmall
                                anchors.verticalCenter: image.verticalCenter
                                Label {
                                    width: parent.width
                                    elide: Text.ElideMiddle
                                    color: pressed ? Theme.secondaryColor :Theme.primaryColor
                                    font.pixelSize: Theme.fontSizeSmall
                                    text: document_name
                                }
                                Label {

                                    color: pressed ? Theme.primaryColor :Theme.secondaryColor
                                    font.pixelSize: Theme.fontSizeTiny
                                    text: Format.formatFileSize(file_downloaded_size) + "/"
                                                                       + Format.formatFileSize(file_uploaded_size)
                                }
                            }
                        }
}
                        LinkedLabel {
                            width: documentRowWrapper.width
                            plainText:file_caption
                            color: pressed ? Theme.secondaryColor :Theme.primaryColor
                            linkColor: pressed ? Theme.secondaryHighlightColor :Theme.highlightColor
                            font.pixelSize: Theme.fontSizeSmall
                            wrapMode: Text.WordWrap
                            visible:  file_caption ?  true : false
                        }
                        Separator{
                            color:pressed ? Theme.primaryColor : Theme.secondaryColor
                            width:parent.width/3
                        }
                        Row {
                            id:metaInfoRow
                            width:parent.width
                            layoutDirection: is_outgoing ? Qt.RightToLeft : Qt.LeftToRight
                            Label{
                                function timestamp(dateTime){
                                    var dateTimeDate=new Date(dateTime*1000)

                                    var datetime_day = dateTimeDate.getDay()
                                    var currentDay = new Date().getDay()

                                    if (datetime_day==currentDay)
                                        return Format.formatDate(dateTimeDate, Formatter.TimeValue)
                                    else
                                        return Format.formatDate(dateTimeDate, Formatter.DateMediumWithoutYear)
                                }
                                font.pixelSize: Theme.fontSizeTiny
                                color:pressed ? Theme.primaryColor : Theme.secondaryColor
                                text:timestamp(date)
                            }

                        }

                    }
                }

                Component {
                    id:stickerContent
                    Column{
                        width:messageListItem.width/4*3
                        Row{
                            id:subInfoRow
                            width:parent.width
                            Label {
                                visible: messagingModel.chatType === TdlibState.BasicGroup ?  true :
                                                                                             messagingModel.chatType == TdlibState.Supergroup ? true
                                                                                                                                              : false
                                id:authorName
                                //                                        width:Math.max(parent.width*4/5,implicitWidth)
                                text:author
                                color: pressed ?Theme.highlightColor: Theme.secondaryHighlightColor
                                font.pixelSize: Theme.fontSizeExtraSmall
                                truncationMode: TruncationMode.Fade
                            }
                        }

                        Image {

                            width:parent.width
                            fillMode: Image.PreserveAspectFit
                            source:"image://depecherDb/"+content
                        }
                        Row {
                            id:metaInfoRow
                            width:parent.width
                            layoutDirection: is_outgoing ? Qt.RightToLeft : Qt.LeftToRight
                            Label{
                                function timestamp(dateTime){
                                    var dateTimeDate=new Date(dateTime*1000)

                                    var datetime_day = dateTimeDate.getDay()
                                    var currentDay = new Date().getDay()

                                    if (datetime_day==currentDay)
                                        return Format.formatDate(dateTimeDate, Formatter.TimeValue)
                                    else
                                        return Format.formatDate(dateTimeDate, Formatter.DateMediumWithoutYear)
                                }
                                font.pixelSize: Theme.fontSizeTiny
                                color:pressed ? Theme.primaryColor : Theme.secondaryColor
                                text:timestamp(date)
                            }

                        }

                    }
                }
                Component {
                    id:newMessageContent
                    Item{
                        width: messageListItem.width - 2*Theme.horizontalPageMargin
                        height:Theme.itemSizeSmall
                        Rectangle {
                            width: newMessagesLabel.width + 2* Theme.paddingLarge
                            height: newMessagesLabel.height
                            anchors.centerIn: parent

                            radius: 90
                            color:Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity)
                            Label{
                                id:newMessagesLabel
                                anchors.centerIn: parent
                                text:qsTr("new messages")
                                font.pixelSize: Theme.fontSizeTiny
                            }
                        }
                    }
                }
            }
        }
    }
}
