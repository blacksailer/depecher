import QtQuick 2.6
import Sailfish.Silica 1.0
Label {
    property string content
    textFormat: Text.RichText
    text: "<style>a:link { color: " + Theme.highlightColor + "; }</style>" +
             content
    color: pressed ? Theme.secondaryColor : Theme.primaryColor
    linkColor: pressed ? Theme.secondaryHighlightColor : Theme.highlightColor
    onLinkActivated: {
        console.log(link.substring(0,4),link)
        if(link.substring(0,4) == "user")
            pageStack.push(Qt.resolvedUrl("../../UserPage.qml"),{username:link.substring(6)})
        else if(link.substring(0,7) == "id_user")
            pageStack.push(Qt.resolvedUrl("../../UserPage.qml"),{user_id:parseInt(link.substring(8))})
            else
        Qt.openUrlExternally(link)
    }
    font.pixelSize: Theme.fontSizeSmall
    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
}
