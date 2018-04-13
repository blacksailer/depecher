import QtQuick 2.0
import Sailfish.Silica 1.0
import "../js/countries.js" as CountryList
import tdlibQtEnums 1.0

Dialog {
    id: authorizeDialog

    anchors.fill: parent
    allowedOrientations: Orientation.All
    acceptDestination: Qt.resolvedUrl("components/authorization/AreYouSureDialog.qml")    
    canAccept: tfphonenumber.text.length>0 &tfcountrycode.text.length>1
    onAcceptPendingChanged: {
        if (acceptPending) {
            acceptDestinationInstance.fullPhoneNumber =tfcountrycode.text + tfphonenumber.text;
        }
    }

    Column
    {
        id: phonenumber
        spacing: Theme.paddingLarge
        width: parent.width

        Item { width: parent.width; height: Theme.paddingLarge }

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
                tfcountrycode.text = "+" + CountryList.countries[currentIndex].code;
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
            }

            TextField
            {
                id: tfphonenumber
                width: parent.width - tfcountrycode.width
                placeholderText: qsTr("Phone Number")
                validator: RegExpValidator { regExp: /^[0-9]{3,}$/ }
                inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText | Qt.ImhDigitsOnly
            }
        }
    }
}
