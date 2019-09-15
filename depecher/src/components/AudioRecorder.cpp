#include "AudioRecorder.hpp"
#include <QDir>
#include <QStandardPaths>
#include <QTemporaryFile>
#include <QUrl>
#include <stdio.h>
#include <stdlib.h>
#include <vorbis/vorbisfile.h>
//https://github.com/DrKLO/Telegram/blob/e397bd9afdfd9315bf099f78a903f8754d297d7a/TMessagesProj/jni/audio.c#L603
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
    setCodec(Vorbis);
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

bool AudioRecorder::autoRemove() const
{
    return m_autoRemove;
}

bool AudioRecorder::recording() const
{
    return m_recording;
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
    m_file = new QTemporaryFile(defaultStoragePath + "/XXXXXX.ogg", this);
    m_file->setAutoRemove(false);
    m_file->open();
    setLocation(m_file->fileName());
    m_file->close();
    m_file->deleteLater();

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
    m_recording = true;
    emit recordingChanged(m_recording);
}

void AudioRecorder::stopRecording()
{
    this->stop();
    m_recording = false;
    emit recordingChanged(m_recording);

}

void AudioRecorder::deleteRecording()
{
    if(QFile::exists(m_location))
        QFile::remove(m_location);
}

void AudioRecorder::setAutoRemove(bool autoRemove)
{
    if (m_autoRemove == autoRemove)
        return;

    m_autoRemove = autoRemove;
    m_file->setAutoRemove(m_autoRemove);
    emit autoRemoveChanged(m_autoRemove);
}

static inline void set_bits(char *bytes, int32_t bitOffset, int32_t value) {
    bytes += bitOffset / 8;
    bitOffset %= 8;
    *((int32_t *) bytes) |= (value << bitOffset);
}

QString AudioRecorder::getWaveform()
{
    //https://xiph.org/vorbis/doc/vorbisfile/example.html
//    https://github.com/DrKLO/Telegram/blob/e397bd9afdfd9315bf099f78a903f8754d297d7a/TMessagesProj/jni/audio.c#L603
    QFile qf(m_location);
     qf.open(QIODevice::ReadOnly);
     int fd = qf.handle();
     FILE* f = fdopen(fd, "rb");
     OggVorbis_File vf;
      int eof=0;
      int current_section;

      int code = ov_open(f,&vf,NULL,0);
      if(code == 0) {
          int bufferSize = 1024 * 128;
          char sampleBuffer[bufferSize];
            qint64 totalSamples = ov_pcm_total(&vf,-1);
            const quint32 resultSamples = 100;
            qint32 sampleRate = qMax(1, (qint32) (totalSamples / resultSamples));
            quint16 samples[100];
            for (qint32 i = 0; i < resultSamples; i++)
            samples[i] = 0;
       quint64 sampleIndex = 0;
       quint16 peakSample = 0;

       quint32 index = 0;
       while (!eof) {
            long ret = ov_read(&vf, sampleBuffer, bufferSize, 1, 2,
                                      1, &current_section);
            if (ret == 0) {
                 eof=1;
               } else if (ret < 0) {
                   qWarning() << "Can't get samples for waveform. code - " + ret;
               } else {
                   for (qint32 i = 0; i+1 < ret; i = i+2) {
                       qint16 temp = ((qint16)sampleBuffer[i] << 8) | sampleBuffer[i+1];
                       quint16 sample = (quint16) qAbs(temp);
                       if (sample > peakSample) {
                           peakSample = sample;
                       }
                       if (sampleIndex++ % sampleRate == 0) {
                           if (index < resultSamples) {
                               samples[index++] = peakSample;
                           }
                           peakSample = 0;
                       }
                   }
               }
         }
       ov_clear(&vf);
       qf.close();

       qint64 sumSamples = 0;
              for (qint32 i = 0; i < resultSamples; i++)
                  sumSamples += samples[i];

              quint32 bitstreamLength = (resultSamples * 5) / 8 + 1;

      quint16 peak = (quint16) (sumSamples * 1.8f / resultSamples);
       if (peak < 2500)
           peak = 2500;


       for (qint32 i = 0; i < resultSamples; i++) {
           quint16 sample =  samples[i];
           if (sample > peak)
               samples[i] = peak;
        }




        char *bytes = new char[bitstreamLength + 4];
        memset(bytes, 0, bitstreamLength + 4);

        for (qint32 i = 0; i < resultSamples; i++) {
            qint32 value = qMin(31, qAbs((qint32) samples[i]) * 31 / peak);
            set_bits(bytes, i * 5, value & 31);
        }

        QString resultArray = QString::fromLatin1(bytes,bitstreamLength);

//        std::string resultArray(bytes,bitstreamLength);
        delete[] bytes;

        return resultArray;//QString::fromStdString(resultArray);
      } else
          qDebug() << "Can't get waverofm. code - " << code;
      qf.close();
      return QString();
}



