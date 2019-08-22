import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import "../js/utils.js" as Utils
import QtMultimedia 5.6
import "items/filter_delegates"
Page {
    id:page
    property alias chatId: itemsModel.peerId
    property alias filter: itemsModel.filter
    property alias totalCount: itemsModel.totalCount
    SearchChatMessagesModel {
        id: itemsModel
    }
    Connections {
        target: loader.item
        onDownloadDocument: console.log(index)
    }

    Loader {
        id:loader
        anchors.fill: parent
        function onDownloadDocument(index) {
            console.log("CLICK")
        itemsModel.downloadDocument(index)
        }
        onLoaded: {
            loader.item.downloadDocument.connect(onDownloadDocument)
        }
        source: {}
        Component.onCompleted: {
            switch(filter) {
            case TdlibState.Photo:
                setSource("items/filter_delegates/PhotoView.qml",{model:itemsModel,currentFilter:filter})
                break
            case TdlibState.Video:
                setSource("items/filter_delegates/VideoView.qml",{model:itemsModel,currentFilter:filter})
                break
            case TdlibState.Audio:
                setSource("items/filter_delegates/AudioView.qml",{model:itemsModel,currentFilter:filter})
                break
            case TdlibState.Document:
                setSource("items/filter_delegates/DocumentView.qml",{model:itemsModel,currentFilter:filter})
                break
            case TdlibState.Url:
                setSource("items/filter_delegates/LinkView.qml",{model:itemsModel,currentFilter:filter})
                break
            case TdlibState.VoiceNote:
                setSource("items/filter_delegates/VoiceView.qml",{model:itemsModel,currentFilter:filter})
                break

            }
        }
    }

}
