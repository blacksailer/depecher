import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import "../../items"
Page {
    id:root
    property string settingsBehaviorPath:  "/apps/depecher/behavior"
    ConfigurationValue {
        id:sendByEnter
        key:settingsBehaviorPath +"/sendByEnter"
        defaultValue: false
    }
    Column{
        id:column
        width: parent.width
        PageHeader{
            title:qsTr("Behavior")
        }
        TextSwitch {
            width: parent.width -2*x
            x:Theme.horizontalPageMargin
            checked: sendByEnter.value
            automaticCheck: false
            text: qsTr("Send message by enter")
            onClicked: {
                sendByEnter.value = !checked
                sendByEnter.sync()
            }

        }

    }

}
