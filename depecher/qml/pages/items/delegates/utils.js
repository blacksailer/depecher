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
