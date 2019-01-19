import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import QtMultimedia 5.6
import Nemo.Configuration 1.0
import Nemo.DBus 2.0
import QtQml.Models 2.3
import depecherUtils 1.0

Item {
    width:  messageListItem.width
        height: Theme.itemSizeSmall
        x:Theme.horizontalPageMargin/2
        Rectangle {
            width: joinByLinkLabel.width + 4*Theme.paddingLarge
            height: joinByLinkLabel.height + 1*Theme.paddingLarge
            anchors.centerIn: parent
            
            radius: 90
            gradient: Gradient {
                GradientStop { position: 0.0; color: Theme.rgba(Theme.highlightBackgroundColor, 0.10) }
                GradientStop { position: 1.0; color: Theme.rgba(Theme.highlightBackgroundColor, 0.30) }
            }
            
            Label {
                id: joinByLinkLabel
                anchors.centerIn: parent
                text: qsTr("%1 joined by invite link").arg(author)
                font.pixelSize: Theme.fontSizeTiny
                font.bold: true
            }
        }
    }

