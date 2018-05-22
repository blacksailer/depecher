#include "StickerModel.hpp"
#include <QDebug>
#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/ParseObject.hpp"
namespace tdlibQt {

StickerModel::StickerModel(QObject *parent) : QAbstractListModel(parent),
    m_client(TdlibJsonWrapper::instance())
{
    connect(m_client, &TdlibJsonWrapper::stickerSetReceived,
            this, &StickerModel::addStickerSet);
    connect(m_client, &TdlibJsonWrapper::stickerSetsReceived,
    [this](const QJsonObject & setsObject) {
        if (setsObject["@extra"].toString() == "getTrendingStickerSets")
            addTrendingStickerSets(setsObject);
        else
            addInstalledStickerSets(setsObject);
    });
    connect(m_client, &TdlibJsonWrapper::stickersReceived,
    [this](const QJsonObject & setObject) {
        if (setObject["@extra"].toString() == "getFavoriteStickers")
            addFavoriteStickers(setObject);
        else
            addRecentStickers(setObject);
    });
}

void StickerModel::getAttachedStickerSets(const int file_id)
{
    m_client->getAttachedStickerSets(file_id);
}

void StickerModel::getStickerSet(const qint64 set_id)
{
    m_client->getStickerSet(set_id);
}

void StickerModel::getFavoriteStickers()
{
    m_client->getFavoriteStickers();
}

void StickerModel::getRecentStickers()
{
    m_client->getRecentStickers();
}

void StickerModel::getInstalledStickers(const bool is_masks)
{
    m_client->getInstalledStickerSets(is_masks);
}

void StickerModel::addTrendingStickerSets(const QJsonObject &stickerSetsObject)
{
    auto stickerSetsObj = ParseObject::parseStickerSets(stickerSetsObject);
    for (QSharedPointer<stickerSetInfo> val : stickerSetsObj->sets_)
        m_trendingStickerSets.append(val);
}

QSharedPointer<stickerSet> StickerModel::createStickerSet(const QString &name, const QString &title,
        const std::vector<QSharedPointer<sticker> > &stickers)
{
    if (stickers.size() == 0)
        return QSharedPointer<stickerSet>(nullptr);

    QSharedPointer<stickerSet> resultSet = QSharedPointer<stickerSet>(new stickerSet);
    resultSet->name_ = name.toStdString();
    resultSet->title_ = title.toStdString();
    resultSet->stickers_ = stickers;

    return resultSet;
}

StickerModel::StickerModelState StickerModel::state() const
{
    return m_state;
}

QHash<int, QByteArray> StickerModel::roleNames() const
{

}

QVariant StickerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() > rowCount())
        return QVariant();
    if (index.row() < 0)
        return QVariant();
    int rowIndex = index.row();
//    m_stikerSets[rowIndex]->id_;
//    m_stikerSets[rowIndex]->is_archived_;
//    m_stikerSets[rowIndex]->is_installed_;
//    m_stikerSets[rowIndex]->is_masks_;
//    m_stikerSets[rowIndex]->is_official_;
//    m_stikerSets[rowIndex]->is_viewed_;
//    m_stikerSets[rowIndex]->name_;
//    m_stikerSets[rowIndex]->title_;


//    m_installedStickerSets[rowIndex]->id_;
//    m_installedStickerSets[rowIndex]->is_archived_;
//    m_installedStickerSets[rowIndex]->is_installed_;
//    m_installedStickerSets[rowIndex]->is_masks_;
//    m_installedStickerSets[rowIndex]->is_official_;
//    m_installedStickerSets[rowIndex]->is_viewed_;
//    m_installedStickerSets[rowIndex]->name_;
//    m_installedStickerSets[rowIndex]->title_;

    int offset = 0;
//    if(rowIndex > 0 && < m_stikerSets)
// | 0 .. k | k+1 .. q | q+1 ..w | ..
//      1       2           3
// if i >= 0 && i < k => 1
// if i >= k + 1 && i < q => 2
// . . . . . . . . . . . . . .
// if i >= m + 1 i && < total => n

    m_stikerSets[rowIndex-offset]->stickers_[rowIndex]->thumbnail_->photo_->local_->path_;
//    m_installedStickerSets[rowIndex]->covers_;
    switch (role) {
    default:
        return QVariant();
        break;
    }
}

int StickerModel::rowCount(const QModelIndex &/*parent*/) const
{
    int size = 0;
    if (m_state == SendState)
        for ( auto val : m_stikerSets )
        size += val->stickers_.size();
    else
        for ( auto val : m_installedStickerSets )
        size += val->covers_.size();
    return size;
}


void StickerModel::addInstalledStickerSets(const QJsonObject &stickerSetsObject)
{
    auto stickerSetsObj = ParseObject::parseStickerSets(stickerSetsObject);
    for (QSharedPointer<stickerSetInfo> val : stickerSetsObj->sets_) {
        m_installedStickerSets.append(val);
        if (m_state == SendState)
            getStickerSet(val->id_);
    }
}

void StickerModel::addStickerSet(const QJsonObject &stickerSetObject)
{
    auto stickerSetObj = ParseObject::parseStickerSet(stickerSetObject);
    beginInsertRows(QModelIndex(), 0, 0);
    m_stikerSets.append(stickerSetObj);
    endInsertRows();
}

void StickerModel::addFavoriteStickers(const QJsonObject &stickersObject)
{
    auto stickersObj = ParseObject::parseStickers(stickersObject);
    auto resultSet = createStickerSet(tr("Favorite"), tr("Favorite"), stickersObj->stickers_);
    if (resultSet.data()) {
        beginInsertRows(QModelIndex(), 0, 0);
        m_stikerSets.append(resultSet);
        endInsertRows();
    }
}

void StickerModel::addRecentStickers(const QJsonObject &stickersObjecct)
{
    auto stickersObj = ParseObject::parseStickers(stickersObjecct);
    auto resultSet = createStickerSet(tr("Recent"), tr("Recent"), stickersObj->stickers_);
    if (resultSet.data()) {
        beginInsertRows(QModelIndex(), 0, 0);
        m_stikerSets.append(resultSet);
        endInsertRows();
    }
}

void StickerModel::setState(StickerModel::StickerModelState state)
{
    if (m_state == state)
        return;

    m_state = state;

    m_stikerSets.clear();
    m_installedStickerSets.clear();

    switch (m_state) {
    case SendState:
        getFavoriteStickers();
        getRecentStickers();
        getInstalledStickers();
        break;
    case PreviewState:
//        getStickerSet();
        break;
    case SettingsState:

    case TrendingState:
    default:
        break;
    }
    emit stateChanged(m_state);
}
} //tdlibQt
