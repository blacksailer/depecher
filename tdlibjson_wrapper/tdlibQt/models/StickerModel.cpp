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
    //BUG? Lambda functions requires disconnection before dectruction?. Even disconnection doesnt help
    connect(m_client, &TdlibJsonWrapper::stickerSetsReceived,
            this, &StickerModel::stickersSetsReceived);
    connect(m_client, &TdlibJsonWrapper::stickersReceived,
            this, &StickerModel::stickersReceived);
    connect(this, &StickerModel::downloadFileStart,
            this, &StickerModel::getFile);

}

StickerModel::~StickerModel()
{
    m_stikerSets.clear();
    m_installedStickerSets.clear();
    m_StickerSetsSize.clear();
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

StickerModel::StickerModelState StickerModel::modelState() const
{
    return m_state;
}

QHash<int, QByteArray> StickerModel::roleNames() const
{
    QHash<int, QByteArray>  roles;
    roles[ID] = "id";
    roles[IS_ARCHIVED] = "is_archived";
    roles[IS_INSTALLED] = "is_installed";
    roles[IS_MASKS] = "is_masks";
    roles[IS_OFFICIAL] = "is_official";
    roles[IS_VIEWED] = "is_viewed";
    roles[TITLE] = "title";
    roles[NAME] = "name";
    roles[STICKER] = "sticker";
    roles[STICKERS_COUNT] = "stickers_count";
    return roles;
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
    int offset = getOffset(rowIndex);
    int setNumber = getSetIndex(rowIndex);
    qDebug() << rowIndex << offset << setNumber;
    switch (role) {
    case ID:
        return  QString::number(m_stikerSets[setNumber]->id_);
    case IS_ARCHIVED:
        return    m_stikerSets[setNumber]->is_archived_;
    case IS_INSTALLED:
        return   m_stikerSets[setNumber]->is_installed_;
    case IS_MASKS:
        return    m_stikerSets[setNumber]->is_masks_;
    case IS_OFFICIAL:
        return    m_stikerSets[setNumber]->is_official_;
    case IS_VIEWED:
        return    m_stikerSets[setNumber]->is_viewed_;
    case TITLE:
        return   QString::fromStdString(m_stikerSets[setNumber]->title_);
    case NAME:
        return   QString::fromStdString(m_stikerSets[setNumber]->name_);
    case STICKERS_COUNT:
        return m_StickerSetsSize[setNumber];
    case STICKER:
        //    m_installedStickerSets[rowIndex]->covers_;
        if (m_stikerSets[setNumber]->stickers_[rowIndex - offset]->sticker_->local_->is_downloading_completed_)
            return   QString::fromStdString(m_stikerSets[setNumber]->stickers_[rowIndex - offset]->sticker_->local_->path_);
        if (m_stikerSets[setNumber]->stickers_[rowIndex - offset]->thumbnail_->photo_->local_->is_downloading_completed_) {
            emit downloadFileStart(m_stikerSets[setNumber]->stickers_[rowIndex - offset]->sticker_->id_, 12, rowIndex);
            return   QString::fromStdString(m_stikerSets[setNumber]->stickers_[rowIndex - offset]->thumbnail_->photo_->local_->path_);
        }
        emit downloadFileStart(m_stikerSets[setNumber]->stickers_[rowIndex - offset]->thumbnail_->photo_->id_, 12, rowIndex);
        return QVariant();
    default:
        return QVariant();
        break;
    }

    //    m_installedStickerSets[rowIndex]->id_;
    //    m_installedStickerSets[rowIndex]->is_archived_;
    //    m_installedStickerSets[rowIndex]->is_installed_;
    //    m_installedStickerSets[rowIndex]->is_masks_;
    //    m_installedStickerSets[rowIndex]->is_official_;
    //    m_installedStickerSets[rowIndex]->is_viewed_;
    //    m_installedStickerSets[rowIndex]->name_;
    //    m_installedStickerSets[rowIndex]->title_;


}

int StickerModel::getOffset(const int row) const
{
    int offset = 0;
    int rowValue = row;
    for (int i = 0; i < m_StickerSetsSize.size(); i++) {
        if (rowValue >= m_StickerSetsSize.at(i)) {
            offset += m_StickerSetsSize.at(i);
            rowValue -= m_StickerSetsSize.at(i);
        } else
            break;
    }

    return offset;
}

int StickerModel::getSetIndex(const int row) const
{
    if (m_StickerSetsSize.size() < 0)
        return 0;

    int cummulativeSize = 0;
    for (int setIndex = 0; setIndex < m_StickerSetsSize.size(); setIndex++) {
        cummulativeSize += m_StickerSetsSize.at(setIndex);
        if (row < cummulativeSize)
            return setIndex;
    }
}

int StickerModel::rowCount(const QModelIndex &/*parent*/) const
{
    int size = 0;
    if (m_state == SendState)
        for (auto val : m_stikerSets)
            size += val->stickers_.size();
    else
        for (auto val : m_installedStickerSets)
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
    if (stickerSetObj.data()) {
        int cummulativeSize = 0;
        for (int idx = 0; idx < m_StickerSetsSize.size(); idx++)
            cummulativeSize += m_StickerSetsSize.at(idx);
        m_StickerSetsSize.append(stickerSetObj->stickers_.size());

        int first = cummulativeSize;
        int last = cummulativeSize + m_StickerSetsSize.last();
        beginInsertRows(QModelIndex(), first, last);
        m_stikerSets.append(stickerSetObj);
        endInsertRows();
    }
}

void StickerModel::updateFile(const QJsonObject &fileObject)
{

    if (fileObject["@type"].toString() != "updateFile")
        processFile(fileObject["file"].toObject());
}

void StickerModel::processFile(const QJsonObject &fileObject)
{

    auto file = ParseObject::parseFile(fileObject);
    if (m_stickerUpdateQueue.keys().contains(file->id_)) {
        QVector<int> photoRole;
        int rowIndex = m_stickerUpdateQueue[file->id_];
        int setIndex = getSetIndex(rowIndex);
        int offset = getOffset(rowIndex);
        if (m_stikerSets[setIndex]->stickers_[rowIndex - offset]->sticker_->id_ == file->id_)
            m_stikerSets[setIndex]->stickers_[rowIndex - offset]->sticker_ = file;
        if (m_stikerSets[setIndex]->stickers_[rowIndex - offset]->thumbnail_->photo_->id_ == file->id_)
            m_stikerSets[setIndex]->stickers_[rowIndex - offset]->thumbnail_->photo_ = file;
        if (file->local_->is_downloading_completed_)
            photoRole.append(STICKER);
        emit dataChanged(index(m_stickerUpdateQueue[file->id_]),
                         index(m_stickerUpdateQueue[file->id_]), photoRole);
        if (file->local_->is_downloading_completed_)
            m_stickerUpdateQueue.remove(file->id_);
    }

}

void StickerModel::stickersReceived(const QJsonObject &setObject)
{
    if (setObject["@extra"].toString() == "getFavoriteStickers")
        addFavoriteStickers(setObject);
    else
        addRecentStickers(setObject);
}

void StickerModel::stickersSetsReceived(const QJsonObject &setsObject)
{
    if (setsObject["@extra"].toString() == "getTrendingStickerSets")
        addTrendingStickerSets(setsObject);
    else
        addInstalledStickerSets(setsObject);
}

void StickerModel::getFile(const int fileId, const int priority, const int indexItem)
{
    m_client->downloadFile(fileId, priority);
    m_stickerUpdateQueue[fileId] = indexItem;

}
void StickerModel::addFavoriteStickers(const QJsonObject &stickersObject)
{
    auto stickersObj = ParseObject::parseStickers(stickersObject);
    auto resultSet = createStickerSet(tr("Favorite"), tr("Favorite"), stickersObj->stickers_);
    if (resultSet.data()) {
        int cummulativeSize = 0;
        for (int idx = 0; idx < m_StickerSetsSize.size(); idx++)
            cummulativeSize += m_StickerSetsSize.at(idx);
        m_StickerSetsSize.append(resultSet->stickers_.size());

        int first = cummulativeSize;
        int last = cummulativeSize + m_StickerSetsSize.last();
        beginInsertRows(QModelIndex(), first, last);
        m_stikerSets.append(resultSet);
        endInsertRows();
    }
}

void StickerModel::addRecentStickers(const QJsonObject &stickersObjecct)
{
    auto stickersObj = ParseObject::parseStickers(stickersObjecct);
    auto resultSet = createStickerSet(tr("Recent"), tr("Recent"), stickersObj->stickers_);

    if (resultSet.data()) {
        int cummulativeSize = 0;
        for (int idx = 0; idx < m_StickerSetsSize.size(); idx++)
            cummulativeSize += m_StickerSetsSize.at(idx);
        m_StickerSetsSize.append(resultSet->stickers_.size());

        int first = cummulativeSize;
        int last = cummulativeSize + m_StickerSetsSize.last();
        beginInsertRows(QModelIndex(), first, last);
        m_stikerSets.append(resultSet);
        endInsertRows();
    }
}

void StickerModel::setModelState(StickerModel::StickerModelState state)
{
    if (m_state == state)
        return;

    m_state = state;
    beginResetModel();
    m_stikerSets.clear();
    m_installedStickerSets.clear();
    m_StickerSetsSize.clear();
    endResetModel();
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
    emit modelStateChanged(m_state);
}
} //tdlibQt
