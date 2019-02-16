import QtQuick 2.0
import Sailfish.Silica 1.0
Dialog {
    id:root
    property string address:""
    property string port:""
    property string username:""
    property string password:""
    property bool http_only:false
    property string secret:""
    property int type:0


Column {
width: parent.width
DialogHeader {
    acceptText: qsTr("Add proxy")
}

ComboBox {
    id:comboBox
    width: parent.width
    label:qsTr("Proxy type")
    currentIndex: type
    menu: ContextMenu {
        MenuItem { text: "SOCKS5" }
        MenuItem { text: "HTTP" }
        MenuItem { text: "MtProto" }
    }
    onCurrentIndexChanged: {
    if(currentIndex == 1)
        loader.sourceComponent = httpComponent
    else if(currentIndex == 0)
        loader.sourceComponent = socks5Component
    else if(currentIndex == 2)
        loader.sourceComponent = mtprotoComponent
    else
        loader.setSource()
    root.type = comboBox.currentIndex
    }
}
TextField {
    id:addressField
    placeholderText: qsTr("Server address")
    label: qsTr("Address")
    text:address
    width: parent.width
    EnterKey.iconSource: "image://theme/icon-m-enter-next"
    EnterKey.onClicked: portField.focus = true
    onTextChanged: root.address = text

}
TextField {
    id:portField
    placeholderText: qsTr("Server port")
    label: qsTr("port")
    text:port
    width: parent.width
    inputMethodHints: Qt.ImhDigitsOnly
    EnterKey.iconSource: "image://theme/icon-m-enter-next"
    EnterKey.onClicked: usernameField.focus = true
    onTextChanged: root.port = text
}
Loader{
id:loader
width: parent.width
sourceComponent: socks5Component
}
}
Component {
id:httpComponent
Column {
    width: parent.width

TextField {
    id:usernameField
    placeholderText: qsTr("Username")
    label: qsTr("username")
    text:username
    width: parent.width
    EnterKey.iconSource: "image://theme/icon-m-enter-next"
    EnterKey.onClicked: passwordField.focus = true
    onTextChanged: root.username = text

}
PasswordField{
    id:passwordField
    width: parent.width
    placeholderText:qsTr("Password")
    label:qsTr("Password")
    text:password
    EnterKey.iconSource: "image://theme/icon-m-enter-accept"
    EnterKey.onClicked:root.accept()
    onTextChanged: root.password = text


}
TextSwitch {
    text: qsTr("HTTP only")
    checked: http_only
}
}
}
Component {
id:socks5Component
Column {
width: parent.width

TextField {
    id:usernameField
    placeholderText: qsTr("Username")
    label: qsTr("username")
    text:username
    width: parent.width
    EnterKey.iconSource: "image://theme/icon-m-enter-next"
    EnterKey.onClicked: passwordField.focus = true
    onTextChanged: root.username = text

}
PasswordField{
    id:passwordField
    width: parent.width
    placeholderText:qsTr("Password")
    label:qsTr("Password")
    text:password
    EnterKey.iconSource: "image://theme/icon-m-enter-accept"
    EnterKey.onClicked:setupProxy()
    onTextChanged: root.password = text

}
}
}

Component {
id:mtprotoComponent
Column {
    width: parent.width

TextField {
    id:secretField
    placeholderText: qsTr("Secret")
    label: qsTr("secret")
    text:secret
    width: parent.width
    EnterKey.iconSource: "image://theme/icon-m-enter-next"
    EnterKey.onClicked: root.accept()
    onTextChanged: root.secret = text

}
}
}
}
