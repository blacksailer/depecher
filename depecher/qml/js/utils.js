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
