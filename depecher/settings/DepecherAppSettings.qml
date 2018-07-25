import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.DBus 2.0
import QtQml 2.2
import Nemo.Configuration 1.0
 import Sailfish.Pickers 1.0

Page {
    id: root

    property string tdlibSettingsPath: "/apps/depecher/tdlib"
    property bool depecherRunning
    property bool depecherAutostart
    property bool ready: true

    ConfigurationValue {
        id:filesDirectoryValue
        key: tdlibSettingsPath + "/files_directory"
        defaultValue: ""
    }
    ConfigurationValue {
        id:useFileDatabaseValue
        key: tdlibSettingsPath + "/use_file_database"
        defaultValue: true
    }
    ConfigurationValue {
        id:useChatInfoDatabaseValue
        key: tdlibSettingsPath + "/use_chat_info_database"
        defaultValue: true
    }
    ConfigurationValue {
        id:useMessageDatabaseValue
        key: tdlibSettingsPath + "/use_message_database"
        defaultValue: true
    }
    ConfigurationValue {
        id:enableStorageOptimizerValue
        key: tdlibSettingsPath + "/enable_storage_optimizer"
        defaultValue: true
    }

    DBusInterface {
        id: depecherService

        bus: DBus.SessionBus
        service: "org.freedesktop.systemd1"
        iface: "org.freedesktop.systemd1.Unit"
        signalsEnabled: true

        function updateProperties() {
            var status = depecherService.getProperty("ActiveState")
            depecherSystemdStatus.status = status
            if (path !== "") {
                root.depecherRunning = status === "active"
            } else {
                root.depecherRunning = false
            }
        }
        onPathChanged: updateProperties()
    }
    DBusInterface {
        id: manager

        bus: DBus.SessionBus
        service: "org.freedesktop.systemd1"
        path: "/org/freedesktop/systemd1"
        iface: "org.freedesktop.systemd1.Manager"
        signalsEnabled: true

        signal unitNew(string name)
        onUnitNew: {
            if (name == "depecher.service") {
                pathUpdateTimer.start()
            }
        }

        signal unitRemoved(string name)
        onUnitRemoved: {
            if (name == "depecher.service") {
                depecherService.path = ""
                pathUpdateTimer.stop()
            }
        }

        signal unitFilesChanged()
        onUnitFilesChanged: {
            updateAutostart()
        }

        Component.onCompleted: {
            updatePath()
            updateAutostart()
        }
        function updateAutostart() {
            manager.typedCall("GetUnitFileState", [{"type": "s", "value": "depecher.service"}],
                              function(state) {
                                  console.log(state)
                                  if (state !== "disabled" && state !== "invalid") {
                                      root.depecherAutostart = true
                                  } else {
                                      root.depecherAutostart = false
                                  }
                              },
                              function() {
                                  root.depecherAutostart = false
                              })
        }
        function setAutostart(isAutostart) {
            if(isAutostart)
                enableDepecherUnit()
            else
                disableDepecherUnit()
        }
        function enableDepecherUnit() {
            manager.typedCall( "EnableUnitFiles",[{"type":"as","value":["depecher.service"]},
                                                  {"type":"b","value":false},
                                                  {"type":"b","value":false}],
                              function(carries_install_info,changes){
                                  root.depecherAutostart = true
                                  console.log(carries_install_info,changes)
                              },
                              function() {
                                  console.log("Enabling error")
                              }
                              )
        }
        function disableDepecherUnit() {
            manager.typedCall( "DisableUnitFiles",[{"type":"as","value":["depecher.service"]},
                                                   {"type":"b","value":false}],
                              function(changes){
                                  root.depecherAutostart = false
                                  console.log(changes)
                              },
                              function() {
                                  console.log("Disabling error")
                              }
                              )
        }
        function startDepecherUnit() {
            manager.typedCall( "StartUnit",[{"type":"s","value":"depecher.service"},
                                            {"type":"s","value":"fail"}],
                              function(job) {
                                  console.log("job started - ", job)
                                  depecherService.updateProperties()
                             runningUpdateTimer.start()
                              },
                              function() {
                                  console.log("job started failure")
                              })
        }
        function stopDepecherUnit() {
            manager.typedCall( "StopUnit",[{"type":"s","value":"depecher.service"},
                                           {"type":"s","value":"replace"}],
                              function(job) {
                                  console.log("job stopped - ", job)
                                  depecherService.updateProperties()
                              },
                              function() {
                                  console.log("job stopped failure")
                              })
        }
        function updatePath() {
            manager.typedCall("GetUnit", [{ "type": "s", "value": "depecher.service"}], function(unit) {
                depecherService.path = unit
            }, function() {
                depecherService.path = ""
            })
        }
    }


    Timer {
        // starting and stopping can result in lots of property changes
        id: runningUpdateTimer
        interval: 1000
        repeat: true
        onTriggered:
            depecherService.updateProperties()
    }

    Timer {
        // stopping service can result in unit appearing and disappering, for some reason.
        id: pathUpdateTimer
        interval: 100
        onTriggered: manager.updatePath()
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: content.height + Theme.paddingMedium
        width: parent.width

        Column {
            id:content
            width:parent.width
            PageHeader {
                id: header
                title: qsTr("Depecher settings")
            }
            TextSwitch {
                id: autostart
                //% "Start Depecher on bootup"
                text: qsTr("Start Depecher on bootup")
                description: qsTr("When this is off, you won't get Depecher app on boot")
                enabled: root.ready
                automaticCheck: false
                checked: root.depecherAutostart
                onClicked: {
                    manager.setAutostart(!checked)
                }
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2*Theme.horizontalPageMargin
                text: qsTr("Start/stop Depecher daemon. Stopping Depecher daemon will also stop receiving notifications")
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryHighlightColor
            }
            Label {
                id: depecherSystemdStatus
                property string status: "invalid"
                x: Theme.horizontalPageMargin
                width: parent.width - 2*Theme.horizontalPageMargin
                text: qsTr("Depecher current status") + " - " + status
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryHighlightColor
            }
            Item {
                width: 1
                height: Theme.paddingLarge
            }
            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: Theme.paddingLarge

                Button {
                    enabled: root.ready && !root.depecherRunning
                    text: qsTr("Start daemon")
                    width: (content.width - 2*Theme.horizontalPageMargin - parent.spacing) / 2
                    onClicked: manager.startDepecherUnit()
                }

                Button {
                    enabled: root.ready && root.depecherRunning
                    //% "Stop"
                    text: qsTr("Stop daemon")
                    width: (content.width - 2*Theme.horizontalPageMargin - parent.spacing) / 2
                    onClicked: manager.stopDepecherUnit()
                }
            }

            SectionHeader {
                text: qsTr("Library settings")
            }

            TextField {
                id: filesDirectoryField
                width: parent.width - 2 * x
                height: Theme.itemSizeMedium
                x:Theme.horizontalPageMargin
                label: qsTr("Path to files directory")
                validator: RegExpValidator {
                    regExp: /^(\/[\w^\- ]+)+\/?$/
                }
                visible: useFileDatabaseValue.value

                AddAnimation{}
                placeholderText: label
                text:filesDirectoryValue.value
                onTextChanged: filesDirectoryValue.value = text
            }

            TextSwitch {
                id: useFileDatabaseSwitcher
                text: qsTr("Use file database")
                description: qsTr("If set to true, information about downloaded and uploaded files will be saved between application restarts.")
                automaticCheck: false
                checked: useFileDatabaseValue.value
                onClicked: {
                    useFileDatabaseValue.value = !checked
                    if(!useFileDatabaseValue.value) {
                        useChatInfoDatabaseValue.value = false
                        useMessageDatabaseValue.value = false
                    }
                }
            }
            TextSwitch {
                id: useChatInfoDatabaseSwitcher
                text: qsTr("Use chat info database")
                description: qsTr("If set to true, the library will maintain a cache of users, basic groups, supergroups, channels and secret chats.")
                enabled: useFileDatabaseValue.value
                automaticCheck: false
                checked: useChatInfoDatabaseValue.value
                onClicked: {
                    useChatInfoDatabaseValue.value = !checked
                    if(!useChatInfoDatabaseValue.value) {
                        useMessageDatabaseValue.value = false
                    }
                }
            }
            TextSwitch {
                id: useMessageDatabaseSwitcher
                text: qsTr("Use message database")
                description: qsTr("If set to true, the library will maintain a cache of chats and messages.")
                enabled: useChatInfoDatabaseValue.value
                automaticCheck: false
                checked: useMessageDatabaseValue.value
                onClicked: {
                    useMessageDatabaseValue.value = !checked
                }
            }
            TextSwitch {
                id: enableStorageOptimizerSwitcher
                text: qsTr("Enable storage optimizer")
                description: qsTr("If set to true, old files will automatically be deleted.")
                automaticCheck: false
                checked: enableStorageOptimizerValue.value
                onClicked: {
                    enableStorageOptimizerValue.value = !checked
                }
            }
        }
    }
}
