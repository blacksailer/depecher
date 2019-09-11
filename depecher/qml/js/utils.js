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
function getWidth() {
    switch(page.orientation) {
    case Orientation.Portrait:
    case Orientation.PortraitInverted:
        return Screen.width
    case Orientation.Landscape:
    case Orientation.LandscapeInverted:
        return Screen.height

    }
}
function getHeight() {
    switch(page.orientation) {
    case Orientation.Portrait:
    case Orientation.PortraitInverted:
        return Screen.height
    case Orientation.Landscape:
    case Orientation.LandscapeInverted:
        return Screen.width

    }
}

function formatDate(dateByUnix, shouldShowAsToday) {
    var date = new Date(dateByUnix * 1000)
    var dateMidnight = new Date(date.getTime())
    dateMidnight.setHours(0, 0, 0, 0)
    var dateMidnightByUnix = dateMidnight.getTime()
    var dateYear = date.getFullYear()
    var currentMidnight = new Date()
    currentMidnight.setHours(0, 0, 0, 0)
    var currentMidnightByUnix = currentMidnight.getTime()
    var currentYear = currentMidnight.getFullYear()
    if (dateMidnightByUnix === currentMidnightByUnix)
        return shouldShowAsToday ?
                    qsTr("Today") :
                    Format.formatDate(date, Formatter.TimeValue)
    else if (dateYear === currentYear)
        return Format.formatDate(date, Formatter.DateMediumWithoutYear)
    else
        return Format.formatDate(date, Formatter.DateMedium)
}
