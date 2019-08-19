import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import "../../../js/utils.js" as Utils
import QtMultimedia 5.6
import "../delegates"
Page {
    id:page
    property alias chatId: itemsModel.peerId
    property alias filter: itemsModel.filter
    property alias totalCount: itemsModel.totalCount
    SearchChatMessagesModel {
        id: itemsModel
    }
SilicaListView {
    id:list
    header: PageHeader {
        title:   qsTr("Links")

    }
    model:itemsModel
    anchors.fill: parent
    delegate:   Column {
        width:Utils.getWidth() - 2 * x
        x: Theme.horizontalPageMargin
        Label {
        width:parent.width
        maximumLineCount: 3
        font.pixelSize: Theme.fontSizeSmall
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        textFormat: Text.PlainText
        truncationMode: TruncationMode.Fade
        text:content
        }
        Label {
            width:parent.width
            textFormat: Text.RichText
            text: "<style>a:link { color: " + Theme.highlightColor + "; }</style>" +
                     links
            color: pressed ? Theme.secondaryColor : Theme.primaryColor
            linkColor: pressed ? Theme.secondaryHighlightColor : Theme.highlightColor
            onLinkActivated: {
                Qt.openUrlExternally(link)
            }
            font.pixelSize: Theme.fontSizeSmall
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }
    }
}
}



