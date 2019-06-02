import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import QtMultimedia 5.6
import Nemo.Configuration 1.0
import Nemo.DBus 2.0
import QtQml.Models 2.3
import depecherUtils 1.0
import "utils.js" as JsUtils


Column {
    id:textColumn

    width: textItem.width


    ConfigurationValue {
        id: fullSizeInChannels
        key:"/apps/depecher/ui/message/fullSizeInChannels"
        defaultValue: false
    }
    states: [
        State {
            name: "fullSizeWithMarginCorrection"
            when: fullSizeInChannels.value && messagingModel.chatType["is_channel"]
            PropertyChanges {
                target: textItem
                width: JsUtils.getWidth() - 2 * textColumn.x
            }
            PropertyChanges {
                target: textColumn
                x: Theme.paddingMedium
                width: JsUtils.getWidth()
            }
        }
    ]

    LinkedLabel {
        id: textItem
        width: messageListItem.width * 2 / 3 - Theme.horizontalPageMargin * 2
        plainText: content ? content : ""
        color: pressed ? Theme.secondaryColor : Theme.primaryColor
        linkColor: pressed ? Theme.secondaryHighlightColor : Theme.highlightColor
        font.pixelSize: Theme.fontSizeSmall
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }

}
