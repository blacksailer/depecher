function setState(state) {
    switch(state){
    case 0:
        return "Waiting for network"
              case 1:
                  return "Connecting"
              case 2:
                  return "Connecting to proxy"
              case 3:
                  return "Updating..."
              case 4:
                  return "Ready"
            default:
                return "Uknown"
              }

}
