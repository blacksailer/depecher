import QtQuick 2.0
import Sailfish.Silica 1.0
import TelegramModels 1.0
import tdlibQtEnums 1.0
import "../../../js/utils.js" as Utils
import QtMultimedia 5.6
import ".."
Page {
    id:page
    property alias chatId: itemsModel.peerId
    property alias filter: itemsModel.filter
    property alias totalCount: itemsModel.totalCount
    SearchChatMessagesModel {
        id: itemsModel
    }
    SilicaListView {
        id:list
        property var currentFilter

        header: PageHeader {
            title: qsTr("Voice notes")
        }
        anchors.fill: parent
        model: itemsModel
        delegate:         Item {
            width:Utils.getWidth()
            height:contentWrapper.height
            function drawWaveform(ctx,width,height,waveformBytes,position,duration) {
                //https://github.com/DrKLO/Telegram/blob/a724d96e9c008b609fe188d122aa2922e40de5fc/TMessagesProj/src/main/java/org/telegram/ui/Components/SeekBarWaveform.java
                var samplesCount = (waveform.length * 8 / 5);
                var totalBarsCount = width / 3;
                var samplesPerBar = samplesCount / totalBarsCount;
                var barCounter = 0;
                var nextBarNum = 0;
                var barHeight = Theme.itemSizeSmall / 2
                var y = (height - barHeight);
                var barNum = 0;
                var lastBarNum;
                var drawBarCount;
                var thumbX = parseInt(position/duration * width,10);
                ctx.clearRect(0, 0, width, height);
                for (var a = 0; a < samplesCount; a++) {
                    if (a != nextBarNum) {
                        continue;
                    }
                    drawBarCount = 0;
                    lastBarNum = nextBarNum;
                    while (lastBarNum == nextBarNum) {
                        barCounter += samplesPerBar;
                        nextBarNum = parseInt(barCounter,10)
                        drawBarCount++;
                    }

                    var bitPointer = a * 5;
                    var byteNum = bitPointer / 8;
                    var byteBitOffset = bitPointer - byteNum * 8;
                    var currentByteCount = 8 - byteBitOffset;
                    var nextByteRest = 5 - currentByteCount;
                    var value =  ((waveformBytes.charCodeAt(byteNum) >> byteBitOffset) & ((2 << (Math.min(5, currentByteCount) - 1)) - 1));
                    if (nextByteRest > 0 && byteNum + 1 < waveformBytes.length) {
                        value =  value << nextByteRest;
                        value = value | waveformBytes.charCodeAt(byteNum + 1) & ((2 << (nextByteRest - 1)) - 1);
                    }
                    for (var b = 0; b < drawBarCount; b++) {
                        var x = barNum * 3;
                        if (x < thumbX && x + 2 < thumbX) {
                            ctx.fillStyle = Theme.highlightColor;
                            ctx.fillRect(x, y + barHeight - Math.max(1, barHeight * value / 31.0), 2, Math.max(1, barHeight * value / 31.0));
                        } else {
                            ctx.fillStyle = Theme.secondaryHighlightColor;
                            ctx.fillRect(x, y + barHeight - Math.max(1, barHeight * value / 31.0), 2, Math.max(1, barHeight * value / 31.0));
                            //                    if (x < thumbX) {
                            //                        ctx.fillStyle = Theme.highlightColor;
                            //                        ctx.fillRect(x, y + 14 - Math.max(1, barHeight * value / 31.0), thumbX, Math.max(1, barHeight * value / 31.0));
                            //                    }
                        }
                        barNum++;
                    }
                }

            }
            BackgroundItem {
                width: parent.width
                height: parent.height


                Row {
                    id:contentWrapper
                    width:parent.width
                    Column {
                        width:Theme.itemSizeExtraSmall
                        CircleImage {
                            id: userAvatar
                            width: visible ? Theme.itemSizeExtraSmall : 0
                            source: sender_photo ? "image://depecherDb/"+sender_photo : ""
                            fallbackText: author ? author.charAt(0) : ""
                            fallbackItemVisible: sender_photo ? false : true
                        }
                    }
                    Item {
                        width:Theme.paddingLarge
                        height:1
                    }
                    Column {
                        width:parent.width - Theme.itemSizeExtraSmall
                        Label {
                            id: authorName
                            text: author ? author : ""
                            color: pressed ? Theme.highlightColor: Theme.secondaryHighlightColor
                            font.pixelSize: Theme.fontSizeExtraSmall
                            width: Math.min(implicitWidth,parent.width *2/3)
                            truncationMode: TruncationMode.Fade
                        }
                        Row {
                            id: documentRowWrapper
                            width: parent.width
                            spacing: Theme.paddingMedium
                            height: Theme.itemSizeMedium

                            Image {
                                id: playIcon
                                fillMode: Image.PreserveAspectFit
                                source: progress.visible ? "image://theme/icon-m-clear"
                                                         : file_downloading_completed ?
                                                               (__depecher_audio.source == "file://"+content && __depecher_audio.playbackState === Audio.PlayingState)
                                                               ? "image://theme/icon-m-pause"
                                                               : "image://theme/icon-m-play"
                                : "image://theme/icon-m-cloud-download"
                                anchors.verticalCenter: parent.verticalCenter

                                ProgressCircle {
                                    id: progress
                                    anchors.fill: parent
                                    visible: file_is_uploading || file_is_downloading
                                    value : file_is_uploading ? file_uploaded_size / file_downloaded_size :
                                                                file_downloaded_size / file_uploaded_size
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        if(file_is_downloading) {
                                            itemsModel.cancelDownload(index)
                                        }else if (!file_downloading_completed) {
                                            itemsModel.downloadDocument(index)
                                        } else {
                                            if(__depecher_audio.playbackState === Audio.PlayingState)
                                                __depecher_audio.stop()
                                            else {
                                                __depecher_audio.source =  Qt.resolvedUrl(content)
                                                __depecher_audio.play()
                                            }
                                        }
                                    }
                                }

                            }

                            Column {
                                width: parent.width - playIcon.width - parent.spacing
                                spacing: Theme.paddingSmall
                                anchors.verticalCenter: playIcon.verticalCenter

                                Canvas {
                                    id: mycanvas
                                    width: parent.width
                                    height: Theme.itemSizeSmall / 2
                                    Connections {
                                        target:__depecher_audio
                                        onPositionChanged:
                                            mycanvas.requestPaint()
                                    }
                                    Connections {
                                        target: Qt.application
                                        onActiveChanged:
                                            //from cover canvas must be repainted
                                            if(active)
                                                mycanvas.requestPaint()
                                    }
                                    onPaint: {
                                        if(__depecher_audio.playbackState == Audio.PlayingState && __depecher_audio.source == Qt.resolvedUrl(content))
                                            drawWaveform(getContext("2d"),width,height,waveform,__depecher_audio.position,__depecher_audio.duration)
                                        else
                                            drawWaveform(getContext("2d"),width,height,waveform,0,duration)
                                    }
                                }
                                Label {
                                    color: pressed ? Theme.primaryColor : Theme.secondaryColor
                                    font.pixelSize: Theme.fontSizeTiny
                                    text: Format.formatDuration(duration,Formatter.DurationShort)
                                }
                            }
                        }
                    }
                }



            }
        }
    }


}
