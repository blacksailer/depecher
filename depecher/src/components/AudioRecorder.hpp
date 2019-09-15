#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include <QObject>
#include <QtMultimedia/QAudioRecorder>

class QTemporaryFile;

class AudioRecorder : public QAudioRecorder
{
    Q_OBJECT
    Q_PROPERTY(QString location READ location NOTIFY locationChanged)
    Q_PROPERTY(bool autoRemove READ autoRemove WRITE setAutoRemove NOTIFY autoRemoveChanged)
    Q_PROPERTY(AudioRecorder::AudioCodec codec READ codec WRITE setCodec NOTIFY codecChanged)
    Q_PROPERTY(bool recording READ recording NOTIFY recordingChanged)

public:
    explicit AudioRecorder(QObject *parent = nullptr);
    ~AudioRecorder();
    enum AudioCodec
    {
        Vorbis,
        Speex,
        PCM,
        FLAC
    };
    Q_ENUM(AudioCodec)
    Q_ENUM(QMediaRecorder::State)

    QString location() const;
    AudioRecorder::AudioCodec codec() const;

    bool autoRemove() const;

    bool recording() const;

private:
    struct CodecSetting
    {
        QString codec;
        QString extension;
        QString container;
    };
    static const QString defaultStoragePath;
    QHash<AudioCodec, CodecSetting> codecSettingsMap;
    QString m_location;
    void setLocation(const QString &location);

    AudioRecorder::AudioCodec m_codec;
    QTemporaryFile *m_file;




    bool m_autoRemove  = false;

    bool m_recording;

public slots:
void setCodec(AudioRecorder::AudioCodec codec);
void startRecording();
void stopRecording();
void deleteRecording();
void setAutoRemove(bool autoRemove);
QString getWaveform();

signals:

    void locationChanged(QString location);
    void codecChanged(AudioRecorder::AudioCodec codec);

    void autoRemoveChanged(bool autoRemove);
    void recordingChanged(bool recording);
};

#endif // AUDIORECORDER_H
