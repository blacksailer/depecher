#ifndef SEARCHCHATMESSAGESMODEL_HPP
#define SEARCHCHATMESSAGESMODEL_HPP

#include <QtCore>
#include "tdlibQt/items/TdApi.hpp"
#include "tdlibQt/include/TdlibNamespace.hpp"
#include "MessagingModel.hpp"
namespace tdlibQt {
class SearchChatMessagesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(double peerId READ peerId WRITE setPeerId NOTIFY peerIdChanged)
    Q_PROPERTY(int totalCount READ totalCount WRITE setTotalCount NOTIFY totalCountChanged)
    Q_PROPERTY(tdlibQt::Enums::SearchFilter filter READ filter WRITE setFilter NOTIFY filterChanged)
    Q_PROPERTY(bool fetching READ fetching WRITE setFetching NOTIFY fetchingChanged)
    Q_PROPERTY(bool reachedHistoryEnd READ reachedHistoryEnd WRITE setReachedHistoryEnd NOTIFY reachedHistoryEndChanged)
    TdlibJsonWrapper *m_tdlibJson;
    QList<QSharedPointer<message>> m_messages;
    tdlibQt::Enums::SearchFilter m_filter = tdlibQt::Enums::SearchFilter::Empty;

    const QString m_extra =  "SearchChatMessagesModel %1";

    double m_peerId;

    bool m_fetching = false;

    bool m_reachedHistoryEnd = false;
    QMap<int, int> m_messagePhotoQueue;

    void appendMessage(const QJsonObject &messageObject);
    void prependMessage(const QJsonObject &messageObject);
    int m_totalCount = -1;
    static QString getLinks(const QString &data, const std::vector<QSharedPointer<textEntity> > &markup);

public:
    explicit SearchChatMessagesModel(QObject *parent = nullptr);
    enum MessageRole {
        ID,
        SENDER_USER_ID,
        SENDER_PHOTO,
        AUTHOR,
        ACTION,
        MEMBER_STATUS,
        CHAT_ID,
        IS_OUTGOING,
        CAN_BE_EDITED,
        CAN_BE_FORWARDED,
        CAN_BE_DELETED_ONLY_FOR_YOURSELF,
        CAN_BE_DELETED_FOR_ALL_USERS,
        IS_CHANNEL_POST,
        CONTAINS_UNREAD_MENTION,
        DATE,
        EDIT_DATE,
        REPLY_TO_MESSAGE_ID,
        MEDIA_ALBUM_ID,
        MEDIA_PREVIEW,
        CONTENT,
        FILE_CAPTION,
        RICH_FILE_CAPTION,
        PHOTO_ASPECT,
        DOCUMENT_NAME,
        DURATION,
        WAVEFORM,
        AUDIO_DURATION,
        AUDIO_TITLE,
        AUDIO_PERFORMER,
        FILE_IS_DOWNLOADING,
        FILE_IS_UPLOADING,
        FILE_DOWNLOADING_COMPLETED,
        FILE_UPLOADING_COMPLETED,
        FILE_DOWNLOADED_SIZE,
        FILE_UPLOADED_SIZE,
        FILE_TYPE,
        STICKER_SET_ID,
        LINKS,
        SECTION //Custom
    };

signals:

    void filterChanged(tdlibQt::Enums::SearchFilter filter);

    void peerIdChanged(double peerId);

    void fetchingChanged(bool fetching);

    void reachedHistoryEndChanged(bool reachedHistoryEnd);
    void downloadFileStart(int file_id_, int priority_, int indexItem) const;

    void totalCountChanged(int totalCount);

private slots:
    void addMessages(const QJsonObject &messagesObject);
    void updateFile(const QJsonObject &fileObject);
    void processFile(const QJsonObject &fileObject);
    void onMessageContentEdited(const QJsonObject &updateMessageContentObject);
public:
    void fetchMore(const QModelIndex &parent) override;
    bool canFetchMore(const QModelIndex &parent) const override;

    // MessagingModel interface
    tdlibQt::Enums::SearchFilter filter() const;

public slots:
    void setFilter(const tdlibQt::Enums::SearchFilter filter);

    void downloadDocument(const int rowIndex);
    void cancelDownload(const int rowIndex);

    void setPeerId(double peerId);
    void setFetching(bool fetching)
    {
        if (m_fetching == fetching)
            return;

        m_fetching = fetching;
        emit fetchingChanged(m_fetching);
    }

    void setReachedHistoryEnd(bool reachedHistoryEnd)
    {
        if (m_reachedHistoryEnd == reachedHistoryEnd)
            return;

        m_reachedHistoryEnd = reachedHistoryEnd;
        emit reachedHistoryEndChanged(m_reachedHistoryEnd);
    }

    void setTotalCount(int totalCount);

public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant dataContent(const int rowIndex) const;
    QVariant dataFileMeta(const int rowIndex, int role) const;

    double peerId() const;

    QHash<int, QByteArray> roleNames() const override;
    bool fetching() const
    {
        return m_fetching;
    }
    bool reachedHistoryEnd() const
    {
        return m_reachedHistoryEnd;
    }
    int totalCount() const
    {
        return m_totalCount;
    }
};
} // namespace tdlibQt
#endif // SEARCHCHATMESSAGESMODEL_HPP
