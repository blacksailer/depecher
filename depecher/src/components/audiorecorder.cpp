#include "audiorecorder.h"
#include <QDir>
#include <QStandardPaths>
#include <QTemporaryFile>
#include <QUrl>


const QString AudioRecorder::defaultStoragePath = QStandardPaths::writableLocation(QStandardPaths::TempLocation);

AudioRecorder::AudioRecorder(QObject *parent) :     QAudioRecorder(parent),
    codecSettingsMap {
        { Vorbis, {"audio/vorbis", ".ogg",  "ogg"} },
        { Speex,  {"audio/speex",  ".oga",  "ogg"} },
        { PCM,    {"audio/PCM",    ".wav",  "wav"} },
        { FLAC,   {"audio/FLAC",   ".flac", "raw"} }
    }
{
    this->setAudioInput("pulseaudio:");
    setCodec(PCM);

    m_file = new QTemporaryFile(defaultStoragePath + "/XXXXXX.wav", this);
    m_file->open();
    setLocation(m_file->fileName());
    m_file->close();
}

AudioRecorder::~AudioRecorder()
{
    stopRecording();
}

QString AudioRecorder::location() const
{
    return m_location;
}


AudioRecorder::AudioCodec AudioRecorder::codec() const
{
    return m_codec;
}

void AudioRecorder::setLocation(const QString &location)
{
    if (m_location == location)
        return;

    m_location = location;
    emit locationChanged(m_location);
}

void AudioRecorder::setCodec(AudioRecorder::AudioCodec codec)
{
    if (m_codec == codec)
        return;

    m_codec = codec;
    emit codecChanged(m_codec);
}

void AudioRecorder::startRecording()
{
    if(this->state() != QMediaRecorder::StoppedState)
    {
        return;
    }

    QAudioEncoderSettings encoderSettings;
    CodecSetting codec = codecSettingsMap[this->codec()];

    encoderSettings.setCodec(codec.codec);
    encoderSettings.setEncodingMode(QMultimedia::ConstantBitRateEncoding);
    encoderSettings.setQuality(QMultimedia::HighQuality);

    int selectedSampleRate = 16000;
    encoderSettings.setSampleRate(selectedSampleRate);


    this->setEncodingSettings(encoderSettings);
    this->setOutputLocation(QUrl(location()));
    this->setContainerFormat(codec.container);

    this->record();
}

void AudioRecorder::stopRecording()
{
    this->stop();
}



