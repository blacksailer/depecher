#ifndef STICKERMODEL_HPP
#define STICKERMODEL_HPP

#include <QAbstractItemModel>
#include "../items/TdApi.hpp"
namespace tdlibQt {
class TdlibJsonWrapper;
class StickerModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(StickerModelState modelState READ modelState WRITE setModelState NOTIFY modelStateChanged)
    Q_PROPERTY(QString set_id READ set_id WRITE setSet_id NOTIFY set_idChanged)
public:
    enum DataRoles {
        ID,
        IS_ARCHIVED,
        IS_INSTALLED,
        IS_MASKS,
        IS_OFFICIAL,
        IS_VIEWED,
        NAME,
        TITLE,
        STICKERS_COUNT,
        SET_STICKER_THUMBNAIL,
        STICKER,
        EMOJI,
        STICKER_FILE_ID
    };
    enum StickerModelState {
        SendState,
        PreviewState,
        TrendingState,
        SettingsState,
        UknownState
    };
    Q_ENUM(StickerModelState)

    StickerModel(QObject *parent = 0);
    ~StickerModel();
    StickerModelState modelState() const;

private:

    StickerModelState m_state = UknownState;
    QList<QSharedPointer<stickerSet>> m_stikerSets;
    QList<QSharedPointer<stickerSetInfo>> m_installedStickerSets;
    QList<QSharedPointer<stickerSetInfo>> m_trendingStickerSets;
    QMap<int, QModelIndex> m_stickerUpdateQueue;

    TdlibJsonWrapper *m_client;


    void getAttachedStickerSets(const int file_id);
    void getStickerSet(const qint64 set_id);
    void getFavoriteStickers();
    void getRecentStickers();
    void getInstalledStickers(const bool is_masks = false);

    void addInstalledStickerSets(const QJsonObject &stickerSetsObject);
    void addTrendingStickerSets(const QJsonObject &stickerSetsObject);
    void addFavoriteStickers(const QJsonObject &stickersObject);
    void addRecentStickers(const QJsonObject &stickersObjecct);

    QSharedPointer<stickerSet> createStickerSet(const QString &name, const QString &title,
            const std::vector<QSharedPointer<sticker>> &stickers);
    QString m_set_id;

public slots:
    void setModelState(StickerModelState state);
    void addStickerSet(const QJsonObject &stickerSetObject);
    void updateFile(const QJsonObject &fileObject);
    void processFile(const QJsonObject &fileObject);
    void stickersReceived(const QJsonObject &setObject);
    void stickersSetsReceived(const QJsonObject &setsObject);
    void changeStickerSet(const QString &setId, const bool isInstalled = false, const bool isArchived = false);

    QVariant getStickerUrl(const int setIndex, const int stickerIndex);
    QVariant getStickerEmoji(const int setIndex, const int stickerIndex);
    QVariant getStickersCount(const int setIndex);
    void setSet_id(QString set_id);

private slots:
    void getFile(const int fileId, const int priority, const QModelIndex indexItem);


signals:
    void modelStateChanged(StickerModelState state);
    void downloadFileStart(int file_id_, int priority_, QModelIndex indexItem) const;



    // QAbstractItemModel interface
    void set_idChanged(QString set_id);

public:
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    int columnCount(const QModelIndex &parent) const override;
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    QString set_id() const;
};
} //tdlibQt
Q_DECLARE_METATYPE(tdlibQt::StickerModel::StickerModelState)

#endif // STICKERMODEL_HPP
