#ifndef INFOPROVIDER_HPP
#define INFOPROVIDER_HPP

#include <QObject>
#include <QJsonObject>
#include "tdlibQt/items/TdApi.hpp"
namespace tdlibQt {
class TdlibJsonWrapper;

class InfoProvider : public QObject
{
    Q_OBJECT
    //Begin saveProperty
    Q_PROPERTY(QString error READ error WRITE setError NOTIFY errorChanged)
    Q_PROPERTY(QString avatar READ avatar NOTIFY avatarChanged)
    Q_PROPERTY(double chatId READ chatId WRITE setChatId NOTIFY chatIdChanged)
    Q_PROPERTY(int photoCount READ photoCount WRITE setPhotoCount NOTIFY photoCountChanged)
    Q_PROPERTY(int videoCount READ videoCount WRITE setVideoCount NOTIFY videoCountChanged)
    Q_PROPERTY(int fileCount READ fileCount WRITE setFileCount NOTIFY fileCountChanged)
    Q_PROPERTY(int audioCount READ audioCount WRITE setAudioCount NOTIFY audioCountChanged)
    Q_PROPERTY(int linkCount READ linkCount WRITE setLinkCount NOTIFY linkCountChanged)
    Q_PROPERTY(int voiceCount READ voiceCount WRITE setVoiceCount NOTIFY voiceCountChanged)
    Q_PROPERTY(int muteFor READ muteFor NOTIFY muteForChanged)
    //End saveProperty

    int m_photoCount;

    int m_videoCount;

    int m_fileCount;

    int m_audioCount;

    int m_linkCount;

    int m_groupCount;

    int m_voiceCount;
    double m_chatId = -1;

    QString m_error = "";

    int m_muteFor;

protected:
    TdlibJsonWrapper *m_tdlibJson;
    QSharedPointer<chat> m_chat;
public:
    explicit InfoProvider(QObject *parent = nullptr);
    virtual QString avatar() const;

    int photoCount() const
    {
        return m_photoCount;
    }

    int videoCount() const
    {
        return m_videoCount;
    }

    int fileCount() const
    {
        return m_fileCount;
    }

    int audioCount() const
    {
        return m_audioCount;
    }

    int linkCount() const
    {
        return m_linkCount;
    }

    int groupCount() const
    {
        return m_groupCount;
    }

    int voiceCount() const
    {
        return m_voiceCount;
    }

    double chatId() const
    {
        return m_chatId;
    }

    QString error() const
    {
        return m_error;
    }

    int muteFor() const;

signals:

    void photoCountChanged(int photoCount);

    void videoCountChanged(int videoCount);

    void fileCountChanged(int fileCount);

    void audioCountChanged(int audioCount);

    void linkCountChanged(int linkCount);

    void groupCountChanged(int groupCount);

    void voiceCountChanged(int voiceCount);
    void avatarChanged();

    void chatIdChanged(double chatId);
    void errorChanged(QString error);

    void muteForChanged();

private slots:
    void countReceived(const QJsonObject &countObject);
    void setPhotoCount(int photoCount)
    {
        if (m_photoCount == photoCount)
            return;

        m_photoCount = photoCount;
        emit photoCountChanged(m_photoCount);
    }
    void setVideoCount(int videoCount)
    {
        if (m_videoCount == videoCount)
            return;

        m_videoCount = videoCount;
        emit videoCountChanged(m_videoCount);
    }
    void setFileCount(int fileCount)
    {
        if (m_fileCount == fileCount)
            return;

        m_fileCount = fileCount;
        emit fileCountChanged(m_fileCount);
    }
    void setAudioCount(int audioCount)
    {
        if (m_audioCount == audioCount)
            return;

        m_audioCount = audioCount;
        emit audioCountChanged(m_audioCount);
    }
    void setLinkCount(int linkCount)
    {
        if (m_linkCount == linkCount)
            return;

        m_linkCount = linkCount;
        emit linkCountChanged(m_linkCount);
    }
    void setVoiceCount(int voiceCount)
    {
        if (m_voiceCount == voiceCount)
            return;

        m_voiceCount = voiceCount;
        emit voiceCountChanged(m_voiceCount);
    }
    void setMuteFor(int muteFor)
    {
        if (m_muteFor == muteFor)
            return;

        m_muteFor = muteFor;
        emit muteForChanged();
    }
private slots:
    void processFile(const QJsonObject &fileObject);

protected slots:
    void setError(QString error)
    {
        if (m_error == error)
            return;

        m_error = error;
        emit errorChanged(m_error);
    }
    void setChatId(double chatId);

public slots:

    void changeNotifications(bool mute);
    void joinChat();
    void leaveChat();


};
} //namespace tdlibQt
#endif // INFOPROVIDER_HPP
