#include "SearchChatMessagesModel.hpp"
#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/ParseObject.hpp"
#include "../NotificationManager.hpp"
#include "singletons/UsersModel.hpp"
#include <QDebug>

namespace tdlibQt {
constexpr int MESSAGE_LIMIT = 20;
SearchChatMessagesModel::SearchChatMessagesModel(QObject *parent) : QAbstractListModel(parent)
{
    m_tdlibJson = TdlibJsonWrapper::instance();
    connect(m_tdlibJson, &TdlibJsonWrapper::newMessages,
            this, &SearchChatMessagesModel::addMessages);
    connect(m_tdlibJson, &tdlibQt::TdlibJsonWrapper::updateFile,
            this, &SearchChatMessagesModel::updateFile);
    connect(m_tdlibJson, &tdlibQt::TdlibJsonWrapper::fileReceived,
            this, &SearchChatMessagesModel::processFile);
    connect(m_tdlibJson, &tdlibQt::TdlibJsonWrapper::updateMessageContent,
            this, &SearchChatMessagesModel::onMessageContentEdited);
    connect(this, &SearchChatMessagesModel::downloadFileStart,
    [this](int fileId, int priority, int indexItem) {
        m_tdlibJson->downloadFile(fileId, priority);
        m_messagePhotoQueue[fileId] = indexItem;
    });

}
void SearchChatMessagesModel::prependMessage(const QJsonObject &messageObject)
{
    auto messageItem = ParseObject::parseMessage(messageObject);

    m_messages.prepend(messageItem);

    bool is_uploading = data(index(0), FILE_IS_UPLOADING).toBool();
    bool is_downloading = data(index(0), FILE_IS_DOWNLOADING).toBool();
    if (is_downloading || is_uploading) {
        int fileId = -1;
        if (messageItem->content_->get_id() == messageDocument::ID) {
            auto messageDocumentPtr = static_cast<messageDocument *>
                                      (messageItem->content_.data());
            fileId = messageDocumentPtr->document_->document_->id_;
        }
        if (messageItem->content_->get_id() == messagePhoto::ID) {
            auto messagePhotoPtr = static_cast<messagePhoto *>
                                   (messageItem->content_.data());
            int sizesCount = messagePhotoPtr->photo_->sizes_.size();
            fileId = messagePhotoPtr->photo_->sizes_[sizesCount - 1]->photo_->id_;
        }
        if (messageItem->content_->get_id() == messageVideo::ID) {
            auto messageVideoPtr = static_cast<messageVideo *>
                                   (messageItem->content_.data());
            fileId = messageVideoPtr->video_->video_->id_;
        }
        if (messageItem->content_->get_id() == messageVideoNote::ID) {
            auto messageVideoPtr = static_cast<messageVideoNote *>
                                   (messageItem->content_.data());
            fileId = messageVideoPtr->video_note_->video_->id_;
        }
        if (fileId > 0)
            m_messagePhotoQueue[fileId] = 0;

    }
    if (m_messagePhotoQueue.keys().size() > 0) {
        for (int key : m_messagePhotoQueue.keys())
            m_messagePhotoQueue[key]++;
    }
}

QString SearchChatMessagesModel::getLinks(const QString &data, const std::vector<QSharedPointer<textEntity>> &markup)
{
    if (markup.size() == 0)
        return data;

    QList<QPair<int, int>> positions;

    for (int i = 0; i < markup.size(); ++i)
        positions.append(QPair<int, int>(markup[i]->offset_, markup[i]->length_));

    QStringList textParts;
    QStringList links;

    for (int i = 0; i < positions.size(); ++i) {
        auto pair = positions[i];
        textParts.append(data.mid(pair.first, pair.second));
    }

    for (int i = 0; i < markup.size(); ++i) {
        switch (markup[i]->type_->get_id()) {
        case textEntityTypeUrl::ID: {
            if (textParts[i].left(4) == "http")
                textParts[i] = textParts[i].prepend("<a href=\"" + textParts[i] + "\">");
            else
                textParts[i] = textParts[i].prepend("<a href=\"" + QUrl::fromUserInput(textParts[i]).toString() + "\">");
            textParts[i] = textParts[i].append("</a>");
            links.append(textParts[i]);
            break;
        }

        case textEntityTypeTextUrl::ID: {
            auto tmp = static_cast<textEntityTypeTextUrl *>(markup[i]->type_.data());
            textParts[i] = textParts[i].prepend(QString("<a href=\"%1\">").arg(QString::fromStdString(tmp->url_)));
            textParts[i] = textParts[i].append("</a>");
            links.append(textParts[i]);
            break;
        }
        break;
        case textEntityTypeHashtag::ID:
        case textEntityTypeItalic::ID:
        case textEntityTypeBold::ID:
        case textEntityTypeEmailAddress::ID:
        case textEntityTypeMention::ID:
        case textEntityTypeBotCommand::ID:
        case textEntityTypeMentionName::ID:
        case textEntityTypePhoneNumber::ID:
        case textEntityTypeCashtag::ID:
        case textEntityTypeCode::ID:
        case textEntityTypePre::ID:
        case textEntityTypePreCode::ID:
            break;
        default:
            break;
        }
    }

    return links.join("<br>");
}

void SearchChatMessagesModel::appendMessage(const QJsonObject &messageObject)
{
    auto messageItem = ParseObject::parseMessage(messageObject);
    if ((qint64)peerId() != messageItem->chat_id_)
        return;

    m_messages.append(messageItem);

    bool is_downl_or_upl = data(index(rowCount(QModelIndex()) - 1), FILE_IS_UPLOADING).toBool()
                           || data(index(rowCount(QModelIndex()) - 1), FILE_IS_DOWNLOADING).toBool();

    if (is_downl_or_upl) {
        int fileId = -1;
        if (messageItem->content_->get_id() == messageDocument::ID) {
            auto messageDocumentPtr = static_cast<messageDocument *>
                                      (messageItem->content_.data());
            fileId = messageDocumentPtr->document_->document_->id_;
        }
        if (messageItem->content_->get_id() == messagePhoto::ID) {
            auto messagePhotoPtr = static_cast<messagePhoto *>
                                   (messageItem->content_.data());
            int sizesCount = messagePhotoPtr->photo_->sizes_.size();
            fileId = messagePhotoPtr->photo_->sizes_[sizesCount - 1]->photo_->id_;
        }
        if (messageItem->content_->get_id() == messageVoiceNote::ID) {
            auto messageVoiceNotePtr = static_cast<messageVoiceNote *>
                                       (messageItem->content_.data());
            fileId = messageVoiceNotePtr->voice_note_->voice_->id_;
        }
        if (messageItem->content_->get_id() == messageAudio::ID) {
            auto messageAudioPtr = static_cast<messageAudio *>
                                   (messageItem->content_.data());
            fileId = messageAudioPtr->audio_->audio_->id_;
        }
        if (fileId > 0)
            m_messagePhotoQueue[fileId] = m_messages.size() - 1;
    }
}

void SearchChatMessagesModel::addMessages(const QJsonObject &messagesObject)
{
    int totalCount = messagesObject["total_count"].toInt();
    QString extra = messagesObject["@extra"].toString("");

    QJsonArray messagesArray = messagesObject["messages"].toArray();
    if (ParseObject::getInt64(messagesArray[0].toObject()["chat_id"]) == peerId()) {
        if (totalCount == m_messages.size())
            setReachedHistoryEnd(true);

        //Oldest
        if (extra == m_extra.arg("prepend")) {
            beginInsertRows(QModelIndex(), 0, messagesArray.size() - 1);
            for (int i = messagesArray.size() - 1; i >= 0; i--) {
                prependMessage(messagesArray[i].toObject());
            }
            endInsertRows();
//            //Notifying view to update previous last item. fetchOlder issue
//            m_indexToUpdate = totalCount;

//            QTimer::singleShot(500, this, [this]() {
//                emit dataChanged(index(m_indexToUpdate), index(m_indexToUpdate), QVector<int>());
//            });

        } else if (extra == m_extra.arg("append")) {
            beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()) + messagesArray.size() - 1);
            for (int i = 0; i < messagesArray.size(); i++)
                appendMessage(messagesArray[i].toObject());
            endInsertRows();
        }  else if (extra == m_extra.arg(m_peerId)) {
            beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()) + messagesArray.size() - 1);
            for (int i = 0; i < messagesArray.size(); i++)
                appendMessage(messagesArray[i].toObject());
            endInsertRows();
        }



        setFetching(false);
    }
}
void SearchChatMessagesModel::onMessageContentEdited(const QJsonObject &updateMessageContentObject)
{
    qint64 chatId = ParseObject::getInt64(updateMessageContentObject["chat_id"]);
    if ((qint64)peerId() != chatId)
        return;
    qint64 messageId = ParseObject::getInt64(updateMessageContentObject["message_id"]);
    auto newContent  = ParseObject::parseMessageContent(updateMessageContentObject["new_content"].toObject());
    for (int i = 0 ; i < m_messages.size(); i++) {
        if (m_messages[i]->id_ == messageId) {
            m_messages[i]->content_ = newContent;
            QVector<int> roles;
            roles.append(CONTENT);
            roles.append(FILE_CAPTION);
            emit dataChanged(index(i + 1), index(i + 1), roles);
            break;
        }
    }
}

void SearchChatMessagesModel::updateFile(const QJsonObject &fileObject)
{
    if (fileObject["@type"].toString() == "updateFile")
        processFile(fileObject["file"].toObject());
}

void SearchChatMessagesModel::processFile(const QJsonObject &fileObject)
{
    auto file = ParseObject::parseFile(fileObject);

    if (m_messagePhotoQueue.keys().contains(file->id_)) {
        QVector<int> photoRole;
        if (m_messages[m_messagePhotoQueue[file->id_]]->content_->get_id() == messagePhoto::ID) {
            auto messagePhotoPtr = static_cast<messagePhoto *>
                                   (m_messages[m_messagePhotoQueue[file->id_]]->content_.data());
            for (quint32 i = 0 ; i < messagePhotoPtr->photo_->sizes_.size(); i++) {
                if (messagePhotoPtr->photo_->sizes_[i]->photo_->id_ == file->id_) {
                    messagePhotoPtr->photo_->sizes_[i]->photo_ = file;
                    break;
                }
            }
        }
        if (m_messages[m_messagePhotoQueue[file->id_] ]->content_->get_id() == messageVideo::ID) {
            auto contentVideoPtr = static_cast<messageVideo *>
                                   (m_messages[m_messagePhotoQueue[file->id_]]->content_.data());
            if (contentVideoPtr->video_->video_->id_ == file->id_)
                contentVideoPtr->video_->video_ = file;
            else if (contentVideoPtr->video_->thumbnail_->photo_->id_ == file->id_)
                contentVideoPtr->video_->thumbnail_->photo_ = file;

        }
        if (m_messages[m_messagePhotoQueue[file->id_] ]->content_->get_id() == messageVideoNote::ID) {
            auto contentVideoNotePtr = static_cast<messageVideoNote *>
                                       (m_messages[m_messagePhotoQueue[file->id_]]->content_.data());
            if (contentVideoNotePtr->video_note_->video_->id_ == file->id_)
                contentVideoNotePtr->video_note_->video_ = file;
            else if (contentVideoNotePtr->video_note_->thumbnail_->photo_->id_ == file->id_)
                contentVideoNotePtr->video_note_->thumbnail_->photo_ = file;

        }
        if (m_messages[m_messagePhotoQueue[file->id_]]->content_->get_id() == messageSticker::ID) {
            auto messageStickerPtr = static_cast<messageSticker *>
                                     (m_messages[m_messagePhotoQueue[file->id_]]->content_.data());
            if (messageStickerPtr->sticker_->sticker_->id_ == file->id_)
                messageStickerPtr->sticker_->sticker_ = file;
        }
        if (m_messages[m_messagePhotoQueue[file->id_]]->content_->get_id() == messageDocument::ID) {
            auto messageDocumentPtr = static_cast<messageDocument *>
                                      (m_messages[m_messagePhotoQueue[file->id_]]->content_.data());
            if (messageDocumentPtr->document_->document_->id_ == file->id_)
                messageDocumentPtr->document_->document_ = file;
        }
        if (m_messages[m_messagePhotoQueue[file->id_]]->content_->get_id() == messageVoiceNote::ID) {
            auto messageVoiceNotePtr = static_cast<messageVoiceNote *>
                                       (m_messages[m_messagePhotoQueue[file->id_]]->content_.data());
            if (messageVoiceNotePtr->voice_note_->voice_->id_ == file->id_)
                messageVoiceNotePtr->voice_note_->voice_ = file;
        }
        if (m_messages[m_messagePhotoQueue[file->id_]]->content_->get_id() == messageAudio::ID) {
            auto messageAudioPtr = static_cast<messageAudio *>
                                   (m_messages[m_messagePhotoQueue[file->id_]]->content_.data());
            if (messageAudioPtr->audio_->audio_->id_ == file->id_)
                messageAudioPtr->audio_->audio_ = file;
        }
        if (m_messages[m_messagePhotoQueue[file->id_]]->content_->get_id() == messageAnimation::ID) {
            auto  messageAnimationPtr = static_cast<messageAnimation *>
                                        (m_messages[m_messagePhotoQueue[file->id_]]->content_.data());
            if (messageAnimationPtr->animation_->animation_->id_ == file->id_)
                messageAnimationPtr->animation_->animation_ = file;
            if (messageAnimationPtr->animation_->thumbnail_->photo_->id_ == file->id_)
                messageAnimationPtr->animation_->thumbnail_->photo_ = file;

        }


        if (file->local_->is_downloading_completed_) {
            photoRole.append(CONTENT);
            photoRole.append(MEDIA_PREVIEW);
        }
        photoRole.append(FILE_DOWNLOADED_SIZE);
        photoRole.append(FILE_UPLOADED_SIZE);
        photoRole.append(FILE_IS_DOWNLOADING);
        photoRole.append(FILE_IS_UPLOADING);
        photoRole.append(FILE_DOWNLOADING_COMPLETED);
        photoRole.append(FILE_UPLOADING_COMPLETED);
        //        photoRole.append(MESSAGE_TYPE);
        emit dataChanged(index(m_messagePhotoQueue[file->id_]),
                         index(m_messagePhotoQueue[file->id_]), photoRole);
        if (file->local_->is_downloading_completed_ && file->remote_->is_uploading_completed_)
            m_messagePhotoQueue.remove(file->id_);

    }
}

void SearchChatMessagesModel::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent)
    if (!fetching()) {
        setFetching(true);
        if (rowCount(QModelIndex()) == 0)
            m_tdlibJson->searchChatMessages(peerId(), 0, "",
                                            0, 0, MESSAGE_LIMIT, filter(), m_extra.arg(m_peerId));
        else
            m_tdlibJson->searchChatMessages(peerId(), m_messages.last()->id_, "",
                                            0, 0, MESSAGE_LIMIT, filter(), m_extra.arg("append"));
    }
}

bool SearchChatMessagesModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_messages.size() < m_totalCount;
}

Enums::SearchFilter SearchChatMessagesModel::filter() const
{
    return m_filter;
}

void SearchChatMessagesModel::setPeerId(double peerId)
{
    if (qFuzzyCompare(m_peerId, peerId))
        return;

    m_peerId = peerId;

    emit peerIdChanged(peerId);
}

void SearchChatMessagesModel::setTotalCount(int totalCount)
{
    if (m_totalCount == totalCount)
        return;
    beginResetModel();
    m_totalCount = totalCount;
    endResetModel();
    emit totalCountChanged(m_totalCount);
}


void SearchChatMessagesModel::setFilter(Enums::SearchFilter filter)
{
    if (m_filter == filter)
        return;

    m_filter = filter;
    beginResetModel();
    m_messages.clear();
    endResetModel();
    emit filterChanged(filter);
}

void SearchChatMessagesModel::downloadDocument(const int rowIndex)
{
    int fileId = -1;
    int messageIndex = rowIndex;
    if (m_messages[messageIndex ]->content_->get_id() == messageDocument::ID) {
        auto contentDocumentPtr = static_cast<messageDocument *>
                                  (m_messages[messageIndex ]->content_.data());
        fileId = contentDocumentPtr->document_->document_->id_;
    }
    if (m_messages[messageIndex ]->content_->get_id() == messageVoiceNote::ID) {
        auto contentDocumentPtr = static_cast<messageVoiceNote *>
                                  (m_messages[messageIndex ]->content_.data());
        fileId = contentDocumentPtr->voice_note_->voice_->id_;
    }
    if (m_messages[messageIndex ]->content_->get_id() == messageAudio::ID) {
        auto contentDocumentPtr = static_cast<messageAudio *>
                                  (m_messages[messageIndex ]->content_.data());
        fileId = contentDocumentPtr->audio_->audio_->id_;
    }
    if (m_messages[messageIndex ]->content_->get_id() == messagePhoto::ID) {
        auto contentDocumentPtr = static_cast<messagePhoto *>
                                  (m_messages[messageIndex ]->content_.data());
        int sizesCount = contentDocumentPtr->photo_->sizes_.size();
        fileId = contentDocumentPtr->photo_->sizes_[sizesCount - 1]->photo_->id_;
    }
    if (m_messages[messageIndex ]->content_->get_id() == messageAnimation::ID) {
        auto contentAnimationPtr = static_cast<messageAnimation *>
                                   (m_messages[messageIndex ]->content_.data());
        fileId = contentAnimationPtr->animation_->animation_->id_;
    }
    if (m_messages[messageIndex ]->content_->get_id() == messageVideo::ID) {
        auto contentVideoPtr = static_cast<messageVideo *>
                               (m_messages[messageIndex ]->content_.data());
        fileId = contentVideoPtr->video_->video_->id_;
    }
    if (m_messages[messageIndex ]->content_->get_id() == messageVideoNote::ID) {
        auto contentVideoPtr = static_cast<messageVideoNote *>
                               (m_messages[messageIndex ]->content_.data());
        fileId = contentVideoPtr->video_note_->video_->id_;
    }
    if (fileId > -1)
        emit downloadFileStart(fileId, 10, messageIndex);
}

void SearchChatMessagesModel::cancelDownload(const int rowIndex)
{
    int fileId = -1;
    int messageIndex = rowIndex;
    if (m_messages[messageIndex]->content_->get_id() == messageDocument::ID) {
        auto contentDocumentPtr = static_cast<messageDocument *>
                                  (m_messages[messageIndex]->content_.data());
        fileId = contentDocumentPtr->document_->document_->id_;
    }
    if (m_messages[messageIndex]->content_->get_id() == messageVoiceNote::ID) {
        auto contentDocumentPtr = static_cast<messageVoiceNote *>
                                  (m_messages[messageIndex]->content_.data());
        fileId = contentDocumentPtr->voice_note_->voice_->id_;
    }
    if (m_messages[messageIndex]->content_->get_id() == messageAudio::ID) {
        auto contentDocumentPtr = static_cast<messageAudio *>
                                  (m_messages[messageIndex]->content_.data());
        fileId = contentDocumentPtr->audio_->audio_->id_;
    }
    if (m_messages[messageIndex]->content_->get_id() == messagePhoto::ID) {
        auto contentDocumentPtr = static_cast<messagePhoto *>
                                  (m_messages[messageIndex]->content_.data());
        int sizesCount = contentDocumentPtr->photo_->sizes_.size();
        fileId = contentDocumentPtr->photo_->sizes_[sizesCount - 1]->photo_->id_;
    }
    if (m_messages[messageIndex ]->content_->get_id() == messageVideo::ID) {
        auto contentVideoPtr = static_cast<messageVideo *>
                               (m_messages[messageIndex ]->content_.data());
        fileId = contentVideoPtr->video_->video_->id_;
    }
    if (m_messages[messageIndex ]->content_->get_id() == messageVideoNote::ID) {
        auto contentVideoPtr = static_cast<messageVideoNote *>
                               (m_messages[messageIndex ]->content_.data());
        fileId = contentVideoPtr->video_note_->video_->id_;
    }
    m_tdlibJson->cancelDownloadFile(fileId);
}

int SearchChatMessagesModel::rowCount(const QModelIndex &parent) const
{
    return m_messages.size();
}

QVariant SearchChatMessagesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() < 0 || index.row() > rowCount(QModelIndex()))
        return QVariant();

    int rowIndex = index.row();

    switch (role) {
    case CONTENT:
        return dataContent(rowIndex);
    case ID: //int64
        return QString::number(m_messages[rowIndex]->id_);
    case SENDER_USER_ID: //int64
        return QString::number(m_messages[rowIndex]->sender_user_id_);
    case AUTHOR:
        return UsersModel::instance()->getUserFullName(m_messages[rowIndex]->sender_user_id_);
    case SENDER_PHOTO: {
        auto profilePhotoPtr = UsersModel::instance()->getUserPhoto(m_messages[rowIndex]->sender_user_id_);
        if (profilePhotoPtr.data()) {
            if (profilePhotoPtr->small_.data()) {
                if (profilePhotoPtr->small_->local_->is_downloading_completed_)
                    return QString::fromStdString(profilePhotoPtr->small_->local_->path_);
            }
        }
        return QVariant();
    }
    case CHAT_ID: //int64
        return QString::number(m_messages[rowIndex]->chat_id_);
    case IS_OUTGOING:
        return m_messages[rowIndex]->is_outgoing_;
    case CAN_BE_EDITED:
        return m_messages[rowIndex]->can_be_edited_;
    case CAN_BE_FORWARDED:
        return m_messages[rowIndex]->can_be_forwarded_;
    case CAN_BE_DELETED_ONLY_FOR_YOURSELF:
        return m_messages[rowIndex]->can_be_deleted_only_for_self_;
    case CAN_BE_DELETED_FOR_ALL_USERS:
        return m_messages[rowIndex]->can_be_deleted_for_all_users_;
    case IS_CHANNEL_POST:
        return m_messages[rowIndex]->is_channel_post_;
    case CONTAINS_UNREAD_MENTION:
        return m_messages[rowIndex]->contains_unread_mention_;
    case DATE:
        return m_messages[rowIndex]->date_;
    case EDIT_DATE:
        return m_messages[rowIndex]->edit_date_;
    case MEDIA_ALBUM_ID:
        return QString::number(m_messages[rowIndex]->media_album_id_);
    case RICH_FILE_CAPTION: {
        if (m_messages[rowIndex]->content_->get_id() == messagePhoto::ID) {
            auto contentPhotoPtr = static_cast<messagePhoto *>
                                   (m_messages[rowIndex]->content_.data());
            auto entities = contentPhotoPtr->caption_->entities_;
            return MessagingModel::makeRichText(QString::fromStdString(contentPhotoPtr->caption_->text_), entities);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageDocument::ID) {
            auto contentDocumentPtr = static_cast<messageDocument *>
                                      (m_messages[rowIndex]->content_.data());
            auto entities = contentDocumentPtr->caption_->entities_;
            return MessagingModel::makeRichText(QString::fromStdString(contentDocumentPtr->caption_->text_), entities);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageAnimation::ID) {
            auto contentAnimationPtr = static_cast<messageAnimation *>
                                       (m_messages[rowIndex]->content_.data());
            auto entities = contentAnimationPtr->caption_->entities_;
            return MessagingModel::makeRichText(QString::fromStdString(contentAnimationPtr->caption_->text_), entities);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVoiceNote::ID) {
            auto contentVoicePtr = static_cast<messageVoiceNote *>
                                   (m_messages[rowIndex]->content_.data());
            auto entities = contentVoicePtr->caption_->entities_;
            return MessagingModel::makeRichText(QString::fromStdString(contentVoicePtr->caption_->text_), entities);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageAudio::ID) {
            auto contentAudioPtr = static_cast<messageAudio *>
                                   (m_messages[rowIndex]->content_.data());
            auto entities = contentAudioPtr->caption_->entities_;
            return MessagingModel::makeRichText(QString::fromStdString(contentAudioPtr->caption_->text_), entities);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVideo::ID) {
            auto contentVideoPtr = static_cast<messageVideo *>
                                   (m_messages[rowIndex]->content_.data());
            auto entities = contentVideoPtr->caption_->entities_;
            return MessagingModel::makeRichText(QString::fromStdString(contentVideoPtr->caption_->text_), entities);
        }

        return QVariant();
    }
    case FILE_CAPTION: {
        if (m_messages[rowIndex]->content_->get_id() == messagePhoto::ID) {
            auto contentPhotoPtr = static_cast<messagePhoto *>
                                   (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentPhotoPtr->caption_->text_);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageDocument::ID) {
            auto contentDocumentPtr = static_cast<messageDocument *>
                                      (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentDocumentPtr->caption_->text_);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageAnimation::ID) {
            auto contentAnimationPtr = static_cast<messageAnimation *>
                                       (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentAnimationPtr->caption_->text_);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVoiceNote::ID) {
            auto contentVoicePtr = static_cast<messageVoiceNote *>
                                   (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentVoicePtr->caption_->text_);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageAudio::ID) {
            auto contentAudioPtr = static_cast<messageAudio *>
                                   (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentAudioPtr->caption_->text_);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVideo::ID) {
            auto contentVideoPtr = static_cast<messageVideo *>
                                   (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentVideoPtr->caption_->text_);
        }

        return QVariant();
    }
    case PHOTO_ASPECT: {
        if (m_messages[rowIndex]->content_->get_id() == messagePhoto::ID) {
            auto contentPhotoPtr = static_cast<messagePhoto *>
                                   (m_messages[rowIndex]->content_.data());
            if (contentPhotoPtr->photo_->sizes_.back()->type_ != "i")
                return (float)contentPhotoPtr->photo_->sizes_.back()->width_ / (float)
                       contentPhotoPtr->photo_->sizes_.back()->height_;
            else {
                int sizeCount = contentPhotoPtr->photo_->sizes_.size();
                if (sizeCount == 1)
                    return 1;
                return (float)contentPhotoPtr->photo_->sizes_[sizeCount - 2]->width_ / (float)
                       contentPhotoPtr->photo_->sizes_[sizeCount - 2]->height_;
            }
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVideo::ID) {
            auto contentVideoPtr = static_cast<messageVideo *>
                                   (m_messages[rowIndex]->content_.data());
            return (float)contentVideoPtr->video_->thumbnail_->width_ / (float)
                   contentVideoPtr->video_->thumbnail_->height_;
        }
        if (m_messages[rowIndex]->content_->get_id() == messageAnimation::ID) {
            auto contentAnimationPtr = static_cast<messageAnimation *>
                                       (m_messages[rowIndex]->content_.data());
            return (float)contentAnimationPtr->animation_->width_ / (float)
                   contentAnimationPtr->animation_->height_;
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVideoNote::ID) {
            auto contentVideoPtr = static_cast<messageVideoNote *>
                                   (m_messages[rowIndex]->content_.data());
            return (float)contentVideoPtr->video_note_->thumbnail_->width_ / (float)
                   contentVideoPtr->video_note_->thumbnail_->height_;
        }
        return QVariant();
    }
    case DOCUMENT_NAME: {
        if (m_messages[rowIndex]->content_->get_id() == messageDocument::ID) {
            auto contentDocumentPtr = static_cast<messageDocument *>
                                      (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentDocumentPtr->document_->file_name_);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVideo::ID) {
            auto contentVideoPtr = static_cast<messageVideo *>
                                   (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentVideoPtr->video_->file_name_);
        }
        return QVariant();
        break;
    }
    case DURATION: {
        if (m_messages[rowIndex]->content_->get_id() == messageVoiceNote::ID) {
            auto contentVoicePtr = static_cast<messageVoiceNote *>
                                   (m_messages[rowIndex]->content_.data());
            return contentVoicePtr->voice_note_->duration_;
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVideo::ID) {
            auto contentVideoPtr = static_cast<messageVideo *>
                                   (m_messages[rowIndex]->content_.data());
            return contentVideoPtr->video_->duration_;
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVideoNote::ID) {
            auto contentVideoNotePtr = static_cast<messageVideoNote *>
                                       (m_messages[rowIndex]->content_.data());
            return contentVideoNotePtr->video_note_->duration_;
        }
        if (m_messages[rowIndex]->content_->get_id() == messageAudio::ID) {
            auto contentAudioPtr = static_cast<messageAudio *>
                                   (m_messages[rowIndex]->content_.data());
            return contentAudioPtr->audio_->duration_;
        }
        return QVariant();
        break;
    }
    case WAVEFORM: {
        if (m_messages[rowIndex]->content_->get_id() == messageVoiceNote::ID) {
            auto contentVoicePtr = static_cast<messageVoiceNote *>
                                   (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentVoicePtr->voice_note_->waveform_);
        }
        return QVariant();
        break;
    }
    case AUDIO_PERFORMER: {
        if (m_messages[rowIndex]->content_->get_id() == messageAudio::ID) {
            auto contentAudioPtr = static_cast<messageAudio *>
                                   (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentAudioPtr->audio_->performer_);
        }
        return QVariant();
        break;
    }
    case AUDIO_TITLE: {
        if (m_messages[rowIndex]->content_->get_id() == messageAudio::ID) {
            auto contentAudioPtr = static_cast<messageAudio *>
                                   (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentAudioPtr->audio_->title_);
        }
        return QVariant();
        break;
    }

    case FILE_IS_DOWNLOADING:
    case FILE_IS_UPLOADING:
    case FILE_DOWNLOADING_COMPLETED:
    case FILE_UPLOADING_COMPLETED:
    case FILE_DOWNLOADED_SIZE:
    case FILE_UPLOADED_SIZE:
    case FILE_TYPE:
        return dataFileMeta(rowIndex, role);
        break;

    case STICKER_SET_ID:
        if (m_messages[rowIndex]->content_->get_id() == messageSticker::ID) {
            auto contentStickerPtr = static_cast<messageSticker *>
                                     (m_messages[rowIndex]->content_.data());
            return QString::number(contentStickerPtr->sticker_->set_id_);
        }
        return QVariant();
        break;
    case MEDIA_PREVIEW:
        if (m_messages[rowIndex]->content_->get_id() == messageAnimation::ID) {
            auto contentAnimationPtr = static_cast<messageAnimation *>(m_messages[rowIndex]->content_.data());
            if (contentAnimationPtr->animation_->thumbnail_->photo_->local_->is_downloading_completed_)
                return QString::fromStdString(contentAnimationPtr->animation_->thumbnail_->photo_->local_->path_);
            else {
                int fileId = contentAnimationPtr->animation_->thumbnail_->photo_->id_;
                emit downloadFileStart(fileId, 12, rowIndex);
            }
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVideo::ID) {
            auto contentVideoPtr = static_cast<messageVideo *>(m_messages[rowIndex]->content_.data());
            if (contentVideoPtr->video_->thumbnail_->photo_->local_->is_downloading_completed_)
                return QString::fromStdString(contentVideoPtr->video_->thumbnail_->photo_->local_->path_);
            else {
                int fileId = contentVideoPtr->video_->thumbnail_->photo_->id_;
                emit downloadFileStart(fileId, 12, rowIndex);
            }
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVideoNote::ID) {
            auto contentVideoPtr = static_cast<messageVideoNote *>(m_messages[rowIndex]->content_.data());
            if (contentVideoPtr->video_note_->thumbnail_->photo_->local_->is_downloading_completed_)
                return QString::fromStdString(contentVideoPtr->video_note_->thumbnail_->photo_->local_->path_);
            else {
                int fileId = contentVideoPtr->video_note_->thumbnail_->photo_->id_;
                emit downloadFileStart(fileId, 12, rowIndex);
            }
        }
        return QVariant();
        break;
    case SECTION: {
        auto messageDateTime = QDateTime::fromTime_t(m_messages[rowIndex]->date_);
        auto messageDate = messageDateTime.date();
        auto DateTimestamp = QDateTime::fromString(messageDate.toString(Qt::ISODate), Qt::ISODate);
        return DateTimestamp.toTime_t();
    }
    case LINKS: {
        if (m_messages[rowIndex]->content_->get_id() == messageText::ID) {
            auto contentPtr = static_cast<messageText *>
                              (m_messages[rowIndex]->content_.data());
            auto entities = contentPtr->text_->entities_;

            return getLinks(QString::fromStdString(contentPtr->text_->text_), entities);
        }
        return QVariant();
    }

    default:
        break;
    }
    return QVariant();
}

QVariant SearchChatMessagesModel::dataContent(const int rowIndex) const
{
    if (m_messages[rowIndex]->content_.data() != nullptr) {
        if (m_messages[rowIndex]->content_->get_id() == messageText::ID) {
            auto contentPtr = static_cast<messageText *>
                              (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentPtr->text_->text_);

        }
        if (m_messages[rowIndex]->content_->get_id() == messagePhoto::ID) {
            auto contentPhotoPtr = static_cast<messagePhoto *>
                                   (m_messages[rowIndex]->content_.data());
            int sizesCount = contentPhotoPtr->photo_->sizes_.size();
            if (sizesCount > 0) {
                if (contentPhotoPtr->photo_->sizes_[sizesCount - 1]->photo_->local_->is_downloading_completed_) {
                    return QString::fromStdString(contentPhotoPtr->photo_->sizes_[sizesCount - 1]->photo_->local_->path_);
                } else if (contentPhotoPtr->photo_->sizes_[0]->photo_->local_->is_downloading_completed_) {
                    int fileId = contentPhotoPtr->photo_->sizes_[sizesCount - 1]->photo_->id_;
                    emit downloadFileStart(fileId, 12, rowIndex);
                    return QString::fromStdString(contentPhotoPtr->photo_->sizes_[0]->photo_->local_->path_);
                } else {
                    int fileId = contentPhotoPtr->photo_->sizes_[0]->photo_->id_;
                    emit downloadFileStart(fileId, 12, rowIndex);

                    return QVariant();
                }
            }
            if (sizesCount > 0)
                return QString::fromStdString(contentPhotoPtr->photo_->
                                              sizes_[contentPhotoPtr->photo_->
                                                     sizes_.size() - 1]->
                                              photo_->local_->path_);
            return QVariant();
        }
        if (m_messages[rowIndex]->content_->get_id() == messageSticker::ID) {
            auto contentPhotoPtr = static_cast<messageSticker *>
                                   (m_messages[rowIndex]->content_.data());
            if (contentPhotoPtr->sticker_->sticker_->local_->is_downloading_completed_)
                return QString::fromStdString(contentPhotoPtr->sticker_->sticker_->local_->path_);
            else {
                int fileId = contentPhotoPtr->sticker_->sticker_->id_;
                emit downloadFileStart(fileId, 12, rowIndex);
                return QVariant();
            }
        }
        if (m_messages[rowIndex]->content_->get_id() == messageDocument::ID) {
            auto contentDocumentPtr = static_cast<messageDocument *>
                                      (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentDocumentPtr->document_->document_->local_->path_);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVoiceNote::ID) {
            auto contentVoicePtr = static_cast<messageVoiceNote *>
                                   (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentVoicePtr->voice_note_->voice_->local_->path_);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageAudio::ID) {
            auto contentAudioPtr = static_cast<messageAudio *>
                                   (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentAudioPtr->audio_->audio_->local_->path_);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVideo::ID) {
            auto contentVideoPtr = static_cast<messageVideo *>
                                   (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentVideoPtr->video_->video_->local_->path_);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVideoNote::ID) {
            auto contentVideoPtr = static_cast<messageVideoNote *>
                                   (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentVideoPtr->video_note_->video_->local_->path_);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageAnimation::ID) {
            auto contentAnimationPtr = static_cast<messageAnimation *>
                                       (m_messages[rowIndex]->content_.data());
            if (contentAnimationPtr->animation_->animation_->local_->is_downloading_completed_)
                return QString::fromStdString(contentAnimationPtr->animation_->animation_->local_->path_);

        }
        if (m_messages[rowIndex]->content_->get_id() == messageContact::ID) {
            auto contactPtr = static_cast<messageContact *>
                              (m_messages[rowIndex]->content_.data());
            QVariantMap contactData;
            contactData["phone_number"] = QString::fromStdString(contactPtr->contact_->phone_number_);
            contactData["first_name"] = QString::fromStdString(contactPtr->contact_->first_name_);
            contactData["last_name"] = QString::fromStdString(contactPtr->contact_->last_name_);
            contactData["user_id"] = contactPtr->contact_->user_id_;
            return contactData;
        }
    }
    return QVariant();
}

QVariant SearchChatMessagesModel::dataFileMeta(const int rowIndex, int role) const
{
    file *filePtr = nullptr;
    if (m_messages[rowIndex]->content_->get_id() == messagePhoto::ID) {
        auto contentPhotoPtr = static_cast<messagePhoto *>
                               (m_messages[rowIndex]->content_.data());
        int sizesCount = contentPhotoPtr->photo_->sizes_.size();
        filePtr = contentPhotoPtr->photo_->sizes_[sizesCount - 1]->photo_.data();
    }
    if (m_messages[rowIndex]->content_->get_id() == messageDocument::ID) {
        auto contentDocumentPtr = static_cast<messageDocument *>
                                  (m_messages[rowIndex]->content_.data());
        filePtr = contentDocumentPtr->document_->document_.data();
    }
    if (m_messages[rowIndex]->content_->get_id() == messageVoiceNote::ID) {
        auto contentVoicePtr = static_cast<messageVoiceNote *>
                               (m_messages[rowIndex]->content_.data());
        filePtr = contentVoicePtr->voice_note_->voice_.data();
    }
    if (m_messages[rowIndex]->content_->get_id() == messageAudio::ID) {
        auto contentAudioPtr = static_cast<messageAudio *>
                               (m_messages[rowIndex]->content_.data());
        filePtr = contentAudioPtr->audio_->audio_.data();
    }
    if (m_messages[rowIndex]->content_->get_id() == messageVideo::ID) {
        auto contentVideoPtr = static_cast<messageVideo *>
                               (m_messages[rowIndex]->content_.data());
        filePtr = contentVideoPtr->video_->video_.data();
    }
    if (m_messages[rowIndex]->content_->get_id() == messageVideoNote::ID) {
        auto contentVideoPtr = static_cast<messageVideoNote *>
                               (m_messages[rowIndex]->content_.data());
        filePtr = contentVideoPtr->video_note_->video_.data();
    }
    if (m_messages[rowIndex]->content_->get_id() == messageAnimation::ID) {
        auto contentAnimationPtr = static_cast<messageAnimation *>
                                   (m_messages[rowIndex]->content_.data());
        filePtr = contentAnimationPtr->animation_->animation_.data();
    }
    switch (role) {
    case FILE_IS_DOWNLOADING:
        if (filePtr)
            return filePtr->local_->is_downloading_active_;
        return QVariant();
        break;
    case FILE_IS_UPLOADING:
        if (filePtr)
            return filePtr->remote_->is_uploading_active_;
        return QVariant();
        break;
    case FILE_DOWNLOADING_COMPLETED:
        if (filePtr)
            return filePtr->local_->is_downloading_completed_;
        return QVariant();
        break;
    case FILE_UPLOADING_COMPLETED:
        if (filePtr)
            return filePtr->remote_->is_uploading_completed_;
        return QVariant();
        break;
    case FILE_DOWNLOADED_SIZE:
        if (filePtr)
            return filePtr->local_->downloaded_size_;
        return QVariant();
        break;
    case FILE_UPLOADED_SIZE:
        if (filePtr)
            return filePtr->remote_->uploaded_size_;
        return QVariant();
        break;
    case FILE_TYPE:
        if (m_messages[rowIndex]->content_->get_id() == messageAnimation::ID) {
            auto contentAnimationPtr = static_cast<messageAnimation *>
                                       (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentAnimationPtr->animation_->mime_type_);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVideo::ID) {
            auto contentVideoPtr = static_cast<messageVideo *>
                                   (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(contentVideoPtr->video_->mime_type_);
        }
        return QVariant();
    default:
        return QVariant();
        break;
    }
}

double SearchChatMessagesModel::peerId() const
{
    return m_peerId;
}

QHash<int, QByteArray> SearchChatMessagesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ID] = "id";
    roles[SENDER_USER_ID] = "sender_user_id";
    roles[SENDER_PHOTO] = "sender_photo";
    roles[AUTHOR] = "author";
    roles[CHAT_ID] = "chat_id";
    roles[MEMBER_STATUS] = "member_status";
    roles[IS_OUTGOING] = "is_outgoing";
    roles[CAN_BE_EDITED] = "can_be_edited";
    roles[CAN_BE_FORWARDED] = "can_be_forwarded";
    roles[CAN_BE_DELETED_ONLY_FOR_YOURSELF] = "can_be_deleted_only_for_yourself";
    roles[CAN_BE_DELETED_FOR_ALL_USERS] = "can_be_deleted_for_all_users";
    roles[IS_CHANNEL_POST] = "is_channel_post";
    roles[CONTAINS_UNREAD_MENTION] = "contains_unread_mention";
    roles[DATE] = "date";
    roles[EDIT_DATE] = "edit_date";
    roles[REPLY_TO_MESSAGE_ID] = "reply_to_message_id";
    roles[MEDIA_ALBUM_ID] = "media_album_id";
    roles[MEDIA_PREVIEW] = "media_preview";
    roles[CONTENT] = "content";
    roles[FILE_CAPTION] = "file_caption";
    roles[RICH_FILE_CAPTION] = "rich_file_caption";
    roles[PHOTO_ASPECT] = "photo_aspect";
    roles[DOCUMENT_NAME] = "document_name";
    roles[DURATION] = "duration";
    roles[AUDIO_PERFORMER] = "audio_performer";
    roles[AUDIO_TITLE] = "audio_title";

    roles[FILE_DOWNLOADED_SIZE] = "file_downloaded_size";
    roles[FILE_UPLOADED_SIZE] = "file_uploaded_size";
    roles[FILE_IS_DOWNLOADING] = "file_is_downloading";
    roles[FILE_IS_UPLOADING] = "file_is_uploading";
    roles[FILE_DOWNLOADING_COMPLETED] = "file_downloading_completed";
    roles[FILE_UPLOADING_COMPLETED] = "file_uploading_completed";
    roles[FILE_TYPE] = "file_type";
    roles[STICKER_SET_ID] = "sticker_set_id";
    roles[SECTION] = "section";
    roles[WAVEFORM] = "waveform";
    roles[LINKS] = "links";
    roles[SENDER_PHOTO] = "sender_photo";

    return roles;
}

} // namespace tdlibQt
