import QtQuick 2.0
import Sailfish.Silica 1.0
import "../js/countries.js" as CountryList
import tdlibQtEnums 1.0

Dialog {
    id: authorizeDialog

    acceptDestination: Qt.resolvedUrl("components/authorization/AreYouSureDialog.qml")
    canAccept: tfphonenumber.text.length>0 &tfcountrycode.text.length>1
    onAcceptPendingChanged: {
        if (acceptPending) {
            acceptDestinationInstance.fullPhoneNumber =tfcountrycode.text + tfphonenumber.text;
        }
    }
    SilicaFlickable{
        anchors.fill: parent
        contentHeight: phonenumber.height

        PullDownMenu{
            MenuItem{
                text: qsTr("Settings")
                onClicked: pageStack.push("SettingsPage.qml",{isLogoutVisible:false})
            }
        }

        Column
        {
            id: phonenumber
            spacing: Theme.paddingLarge
            width: authorizeDialog.width

            PageHeader { title: qsTr("Welcome") }

            Label{
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingMedium; rightMargin: Theme.paddingMedium }
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHCenter
                text:qsTr("Attention: If Telegram is blocked in your country, first setup proxy server in settings via PulleyMenu")
                color:Theme.secondaryColor
                font.pixelSize: Theme.fontSizeSmall
            }

            Label
            {
                id: lblinfo
                text: qsTr("Insert your phone number and press 'Next'")
                font.pixelSize: Theme.fontSizeSmall
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingMedium; rightMargin: Theme.paddingMedium }
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
            }
            ComboBox
            {
                id: cbxcountrycodes
                width: parent.width
                label: qsTr("Country Code")

                menu: ContextMenu {
                    Repeater {
                        model: CountryList.countries

                        MenuItem {
                            text: CountryList.countries[index].country
                        }
                    }
                }

                onCurrentItemChanged: {
                    tfcountrycode.text = "+" + CountryList.countries[currentIndex].code
                    cbxcountrycodes.value = CountryList.countries[currentIndex].country
                }
                Component.onCompleted: {
                    for (var i in CountryList.countries) {
                        if (detectedCountry === CountryList.countries[i].country) {
                            cbxcountrycodes.currentIndex = i
                            break
                        }
                    }
                }
            }

            Row
            {
                id: row
                width: parent.width

                TextField
                {
                    id: tfcountrycode
                    width: font.pixelSize * 5
                    validator: RegExpValidator { regExp: /^\+[0-9]{1,}$/ }
                    inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText | Qt.ImhDigitsOnly
                    onTextChanged: {
                                          var countryCode = text.slice(1)
                                          for(var i=0;i<CountryList.countries.length;i++) {
                                              if (countryCode == CountryList.countries[i].code)
                                                  cbxcountrycodes.currentIndex = i
                                          }
                  }
                    EnterKey.iconSource: "image://theme/icon-m-enter-next"
                    EnterKey.onClicked: tfphonenumber.focus = true
                }

                TextField
                {
                    id: tfphonenumber
                    width: parent.width - tfcountrycode.width
                    placeholderText: qsTr("Phone Number")
                    validator: RegExpValidator { regExp: /^[0-9]{3,}$/ }
                    inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText | Qt.ImhDigitsOnly
                    EnterKey.iconSource: "image://theme/icon-m-enter-accept"
                    EnterKey.onClicked: authorizeDialog.accept()
                }
            }
        }
    }

}
