import QtQuick 2.0
import Sailfish.Gallery 1.0
import Sailfish.Media 1.0
import QtMultimedia 5.6
import Sailfish.Silica 1.0
Page {
    id:root
    property alias source: mediaPlayer.source
    property url thumbnail
    property alias mimeType: videoPoster.mimeType

    property bool autoPlay: false
    orientation: Orientation.All
    VideoPoster {
        id:videoPoster
        source: root.thumbnail ? root.thumbnail : root.source
        playing:  mediaPlayer.playing
        loaded: mediaPlayer.loaded
        busy: false//!mediaPlayer.hasVideo && mediaPlayer.hasError
        onTogglePlay: mediaPlayer.togglePlay()
        contentWidth: root.width
        contentHeight: root.height
        anchors.centerIn: parent
        overlayMode: mediaPlayer.playbackState == MediaPlayer.StoppedState


    }
    VideoOutput {
        property alias player: mediaPlayer
        visible: player.playbackState != MediaPlayer.StoppedState
        anchors.fill: parent
        source: GalleryMediaPlayer {
            id: mediaPlayer
            active: true
            autoPlay: root.autoPlay
            source: active ? currentItem.source : ""
            onPlayingChanged: {
                if (playing) {
                    // go fullscreen for playback if triggered via Play icon.
                    overlay.hideControls()
                }
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if(overlay.open)
                    overlay.hideControls()
                else
                    overlay.showControls()
            }
        }

    }
    MediaPlayerControlsPanel {
        id:overlay
        z:100
        duration: mediaPlayer.duration / 1000
        position: mediaPlayer.position / 1000
        playing: true
        showMenu: false
        Component.onCompleted: showControls()
        onSliderReleased: {
            mediaPlayer.seek(value * 1000)
        }
        onPreviousClicked: mediaPlayer.seek(0)

        onPlayPauseClicked:  mediaPlayer.togglePlay()

    }
}
