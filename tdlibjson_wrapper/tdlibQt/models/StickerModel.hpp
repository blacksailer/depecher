#ifndef STICKERMODEL_HPP
#define STICKERMODEL_HPP

#include <QAbstractListModel>
#include "../items/TdApi.hpp"
namespace tdlibQt {
class TdlibJsonWrapper;
class StickerModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(StickerModelState modelState READ modelState WRITE setModelState NOTIFY modelStateChanged)
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
        STICKER
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

    // QAbstractItemModel interface
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:

    StickerModelState m_state = UknownState;
    QList<QSharedPointer<stickerSet>> m_stikerSets;
    QList<QSharedPointer<stickerSetInfo>> m_installedStickerSets;
    QList<QSharedPointer<stickerSetInfo>> m_trendingStickerSets;
    QList<int> m_StickerSetsSize;
    QMap<int, int> m_stickerUpdateQueue;

    TdlibJsonWrapper *m_client;

    int getOffset(const int row) const;
    int getSetIndex(const int row) const;

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
public slots:
    void setModelState(StickerModelState state);
    void addStickerSet(const QJsonObject &stickerSetObject);
    void updateFile(const QJsonObject &fileObject);
    void processFile(const QJsonObject &fileObject);
    void stickersReceived(const QJsonObject &setObject);
    void stickersSetsReceived(const QJsonObject &setsObject);
private slots:
    void getFile(const int fileId, const int priority, const int indexItem);


signals:
    void modelStateChanged(StickerModelState state);
    void downloadFileStart(int file_id_, int priority_, int indexItem) const;


};
} //tdlibQt
Q_DECLARE_METATYPE(tdlibQt::StickerModel::StickerModelState)

#endif // STICKERMODEL_HPP
