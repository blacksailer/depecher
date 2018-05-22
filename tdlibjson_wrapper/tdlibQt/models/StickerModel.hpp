#ifndef STICKERMODEL_HPP
#define STICKERMODEL_HPP

#include <QAbstractListModel>
#include "../items/TdApi.hpp"
namespace tdlibQt {
class TdlibJsonWrapper;
class StickerModel : public QAbstractListModel
{

    Q_PROPERTY(StickerModelState state READ state WRITE setState NOTIFY stateChanged)
public:
    enum StickerModelState {
        SendState,
        PreviewState,
        TrendingState,
        SettingsState,
        UknownState
    };
    Q_ENUM(StickerModelState)

    StickerModel(QObject *parent = 0);
    StickerModelState state() const;

    // QAbstractItemModel interface
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:

    StickerModelState m_state = UknownState;
    QList<QSharedPointer<stickerSet>> m_stikerSets;
    QList<QSharedPointer<stickerSetInfo>> m_installedStickerSets;
    QList<QSharedPointer<stickerSetInfo>> m_trendingStickerSets;

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
public slots:
    void setState(StickerModelState state);
    void addStickerSet(const QJsonObject &stickerSetObject);

signals:
    void stateChanged(StickerModelState state);



};
} //tdlibQt
Q_DECLARE_METATYPE(tdlibQt::StickerModel::StickerModelState)

#endif // STICKERMODEL_HPP
