import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import "../../items"
import ".."

import org.nemomobile.notifications 1.0


Page {
    NotificationPanel{
        id: notificationPanel
        page: root
    }
    Notification {
        id:notificationProxy
        appName: "Depecher"
        previewBody: qsTr("Proxy is ready")
    }
}
