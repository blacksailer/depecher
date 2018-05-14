function setState(state) {
    switch(state){
    case 0:
        return qsTr("Waiting for network")
              case 1:
                  return qsTr("Connecting")
              case 2:
                  return qsTr("Connecting to proxy")
              case 3:
                  return qsTr("Updating...")
              case 4:
                  return qsTr("Ready")
            default:
                return qsTr("Uknown")
              }

}
function setAuthState(state) {
/*
        AuthorizationStateWaitTdlibParameters,
        AuthorizationStateWaitEncryptionKey,
        AuthorizationStateWaitPhoneNumber,
        AuthorizationStateWaitCode,
        AuthorizationStateWaitPassword,
        AuthorizationStateLoggingOut,
        AuthorizationStateClosing,
        AuthorizationStateClosed,
        AuthorizationStateReady

  */
    switch(state){
    case 0:
        return qsTr("Waiting for network")
              case 1:
                  return qsTr("Wait lib parameters")
              case 2:
                  return qsTr("Wait encryption key")
              case 3:
                  return qsTr("Wait phone number")
              case 4:
                  return qsTr("Wait code")
              case 5:
                  return qsTr("Wait password")
              case 6:
                  return qsTr("Wait logging out")
              case 7:
                  return qsTr("Wait closing")
              case 8:
                  return qsTr("Wait closed")
              case 8:
                  return qsTr("Ready")
            default:
                return qsTr("Uknown")
              }
}
