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
    QHash<int, QByteArray>  roles;
    roles[ID] = "id";
    roles[IS_ARCHIVED] = "is_archived";
    roles[IS_INSTALLED] = "is_installed";
    roles[IS_MASKS] = "is_masks";
    roles[IS_OFFICIAL] = "is_official";
    roles[IS_VIEWED] = "is_viewed";
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
        return   QString::fromStdString(m_stikerSets[setNumber]->stickers_[rowIndex - offset]->thumbnail_->photo_->local_->path_);
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
        if (rowValue > m_StickerSetsSize.at(i)) {
            offset += m_StickerSetsSize.at(i);
            rowValue -= offset;
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
    m_StickerSetsSize.append(stickerSetObj->stickers_.size());
    beginInsertRows(QModelIndex(), m_stikerSets.size(), m_stikerSets.size());
    m_stikerSets.append(stickerSetObj);
    endInsertRows();
}

void StickerModel::updateFile(const QJsonObject &fileObject)
{

    if (fileObject["@type"].toString() != "updateFile")
        return;
    auto file = ParseObject::parseFile(fileObject["file"].toObject());
//    if (stickerUpdateQueue.keys().contains(file->id_)) {
//        QVector<int> photoRole;
//        if (messages[messagePhotoQueue[file->id_]]->content_->get_id() == messagePhoto::ID) {
//            auto messagePhotoPtr = static_cast<messagePhoto *>
//                                   (messages[messagePhotoQueue[file->id_]]->content_.data());
//            for (quint32 i = 0 ; i < messagePhotoPtr->photo_->sizes_.size(); i++) {
//                if (messagePhotoPtr->photo_->sizes_[i]->photo_->id_ == file->id_) {
//                    messagePhotoPtr->photo_->sizes_[i]->photo_ = file;
//                    break;
//                }
//            }
//        }
//        if (file->local_->is_downloading_completed_)
//            photoRole.append(CONTENT);
//        photoRole.append(FILE_DOWNLOADED_SIZE);
//        photoRole.append(FILE_UPLOADED_SIZE);
//        photoRole.append(FILE_IS_DOWNLOADING);
//        photoRole.append(FILE_IS_UPLOADING);
//        photoRole.append(FILE_DOWNLOADING_COMPLETED);
//        photoRole.append(FILE_UPLOADING_COMPLETED);
//        photoRole.append(MESSAGE_TYPE);
//        emit dataChanged(index(messagePhotoQueue[file->id_]),
//                         index(messagePhotoQueue[file->id_]), photoRole);
//        if (file->local_->is_downloading_completed_ && file->remote_->is_uploading_completed_)
//            messagePhotoQueue.remove(file->id_);

//    }
}
void StickerModel::addFavoriteStickers(const QJsonObject &stickersObject)
{
    auto stickersObj = ParseObject::parseStickers(stickersObject);
    auto resultSet = createStickerSet(tr("Favorite"), tr("Favorite"), stickersObj->stickers_);
    m_StickerSetsSize.append(resultSet->stickers_.size());
    if (resultSet.data()) {
        beginInsertRows(QModelIndex(), m_stikerSets.size(), m_stikerSets.size());
        m_stikerSets.append(resultSet);
        endInsertRows();
    }
}

void StickerModel::addRecentStickers(const QJsonObject &stickersObjecct)
{
    auto stickersObj = ParseObject::parseStickers(stickersObjecct);
    auto resultSet = createStickerSet(tr("Recent"), tr("Recent"), stickersObj->stickers_);
    m_StickerSetsSize.append(resultSet->stickers_.size());
    if (resultSet.data()) {
        beginInsertRows(QModelIndex(), m_stikerSets.size(), m_stikerSets.size());
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
    m_StickerSetsSize.clear();

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
