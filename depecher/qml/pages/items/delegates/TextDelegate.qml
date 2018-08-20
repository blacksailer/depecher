import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import QtMultimedia 5.6
import Nemo.Configuration 1.0
import Nemo.DBus 2.0
import QtQml.Models 2.3
import depecherUtils 1.0

Column{
        id: textColumn
        width: textItem.width
        
        LinkedLabel {
            id: textItem
            width: Math.min(paintedWidth ,Screen.width * 2 /3 - Theme.horizontalPageMargin * 2)//text.length<32 ? paintedWidth : Screen.width * 2 /3 - Theme.horizontalPageMargin * 2
            plainText:content ? content : ""
            color: pressed ? Theme.secondaryColor : Theme.primaryColor
            linkColor: pressed ? Theme.secondaryHighlightColor : Theme.highlightColor
            font.pixelSize: Theme.fontSizeSmall
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }
    }
