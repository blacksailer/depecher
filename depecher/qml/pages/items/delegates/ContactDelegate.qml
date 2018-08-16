import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import QtMultimedia 5.6
import Nemo.Configuration 1.0
import Nemo.DBus 2.0
import QtQml.Models 2.3
import depecherUtils 1.0

BackgroundItem {
        property int maxWidth: Screen.width *2/3 - Theme.horizontalPageMargin * 2
        width: maxWidth
        height: Theme.itemSizeMedium
        DBusInterface {
            id: manager
            
            bus: DBus.SessionBus
            service: "com.jolla.contacts.ui"
            path: "/com/jolla/contacts/ui"
            iface: "com.jolla.contacts.ui"
        }
        
        Column{
            width: parent.width
            Label {
                text: content["first_name"] + " " + content["last_name"]
            }
            Label {
                font.pixelSize: Theme.fontSizeSmall
                text: content["phone_number"]
            }
            FileWorker {
                id:fileWorker
            }
        }
        onClicked: {
            var path = fileWorker.openContact(content["first_name"],content["last_name"],
                                              content["phone_number"],content["user_id"])
            manager.typedCall( "importContactFile",[{"type":"s","value":"file://"+path}],
                              function(){
                                  console.log("Import fine!")
                              },
                              function() {
                                  console.log("Importing error")
                              }
                              )
            
        }
    }

