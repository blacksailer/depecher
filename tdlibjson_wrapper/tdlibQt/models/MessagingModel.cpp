#include "MessagingModel.hpp"
#include "../ParseObject.hpp"
#include "../NotificationManager.hpp"
#include "../TdlibJsonWrapper.hpp"
#include "singletons/UsersModel.hpp"
#include <QVariantMap>
namespace tdlibQt {

MessagingModel::MessagingModel() :
    tdlibJson(TdlibJsonWrapper::instance())
{
    connect(tdlibJson, &TdlibJsonWrapper::newMessages,
            this, &MessagingModel::appendMessages);
    connect(tdlibJson, &TdlibJsonWrapper::messageReceived,
            this, &MessagingModel::prependMessage);

    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateFile,
            this, &tdlibQt::MessagingModel::updateFile);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::fileReceived,
            this, &tdlibQt::MessagingModel::processFile);

    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateChatReadInbox,
            this, &MessagingModel::updateChatReadInbox);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateChatReadOutbox,
            this, &MessagingModel::updateChatReadOutbox);

    connect(tdlibJson, &TdlibJsonWrapper::updateTotalCount,
            this, &MessagingModel::updateTotalCount);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateUserChatAction,
            this, &MessagingModel::updateChatAction);
    connect(this, &MessagingModel::downloadFileStart,
            this, &MessagingModel::getFile);
    connect(this, &MessagingModel::downloadAvatarStart,
            this, &MessagingModel::getAvatar);
    connect(tdlibJson, &TdlibJsonWrapper::updateMessageSendSucceeded,
            this, &MessagingModel::updateMessageSend);
    connect(tdlibJson, &TdlibJsonWrapper::updateMessageSendFailed,
            this, &MessagingModel::updateMessageSend);

    connect(this, &MessagingModel::firstIdChanged, [this]() {
        if (messages.first()->id_ == lastMessage().toLongLong()) {
            if (!isUpdateConnected)
                connect(tdlibJson, &TdlibJsonWrapper::newMessageFromUpdate,
                        this, &MessagingModel::addMessageFromUpdate);
            isUpdateConnected = true;
            setAtYEnd(isUpdateConnected);
        }
    });

    NotificationManager::instance()->currentViewableChatId = static_cast<qint64>(peerId().toLongLong());
    connect(&chatActionTimer, &QTimer::timeout, this, &MessagingModel::chatActionCleanUp);
    chatActionTimer.setInterval(5 * 1000);
}

MessagingModel::~MessagingModel()
{
    NotificationManager::instance()->currentViewableChatId = 0;
}


QVariant MessagingModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int rowIndex = index.row();
    if (rowIndex > rowCount(QModelIndex()))
        return QVariant();
    switch (role) {
    case CONTENT:
        return dataContent(rowIndex);
        break;
    case ID: //int64
        return QString::number( messages[rowIndex]->id_);
    case SENDER_USER_ID: //int64
        return QString::number( messages[rowIndex]->sender_user_id_);
    case SENDER_PHOTO: {
        auto profilePhotoPtr = UsersModel::instance()->getUserPhoto(messages[rowIndex]->sender_user_id_);
        if (profilePhotoPtr.data()) {
            if ( profilePhotoPtr->small_.data()) {
                if (profilePhotoPtr->small_->local_->is_downloading_completed_)
                    return QString::fromStdString(profilePhotoPtr->small_->local_->path_);
                else
                    emit downloadAvatarStart(profilePhotoPtr->small_->id_, 12, rowIndex);
            }
        }
        return QVariant();
    }
    case AUTHOR:
        return UsersModel::instance()->getUserFullName(messages[rowIndex]->sender_user_id_);
    case CHAT_ID: //int64
        return QString::number( messages[rowIndex]->chat_id_);
    case IS_OUTGOING:
        return messages[rowIndex]->is_outgoing_;
    case CAN_BE_EDITED:
        return messages[rowIndex]->can_be_edited_;
    case CAN_BE_FORWARDED:
        return messages[rowIndex]->can_be_forwarded_;
    case CAN_BE_DELETED_ONLY_FOR_YOURSELF:
        return messages[rowIndex]->can_be_deleted_only_for_self_;
    case CAN_BE_DELETED_FOR_ALL_USERS:
        return messages[rowIndex]->can_be_deleted_for_all_users_;
    case IS_CHANNEL_POST:
        return messages[rowIndex]->is_channel_post_;
    case CONTAINS_UNREAD_MENTION:
        return messages[rowIndex]->contains_unread_mention_;
    case DATE:
        return messages[rowIndex]->date_;
    case EDIT_DATE:
        return messages[rowIndex]->edit_date_;
    case REPLY_TO_MESSAGE_ID:  //int64
        return QString::number(messages[rowIndex]->reply_to_message_id_);
    case TTL:
        return messages[rowIndex]->ttl_;
    case TTL_EXPIRES_IN:
        return messages[rowIndex]->ttl_expires_in_;
    case AUTHOR_SIGNATURE:
        return QString::fromStdString(messages[rowIndex]->author_signature_);
    case VIEWS:
        return messages[rowIndex]->views_;
    case MEDIA_ALBUM_ID:
        return QString::number( messages[rowIndex]->media_album_id_);
    case FILE_CAPTION: {
        if (messages[rowIndex]->content_->get_id() == messagePhoto::ID) {
            auto contentPhotoPtr = static_cast<messagePhoto *>
                    (messages[rowIndex]->content_.data());
            return QString::fromStdString(contentPhotoPtr->caption_->text_);
        }
        if (messages[rowIndex]->content_->get_id() == messageDocument::ID) {
            auto contentDocumentPtr = static_cast<messageDocument *>
                    (messages[rowIndex]->content_.data());
            return QString::fromStdString(contentDocumentPtr->caption_->text_);
        }
        if (messages[rowIndex]->content_->get_id() == messageAnimation::ID) {
            auto contentAnimationPtr = static_cast<messageAnimation *>
                    (messages[rowIndex]->content_.data());
            return QString::fromStdString(contentAnimationPtr->caption_->text_);
        }

        return QVariant();
    }
    case PHOTO_ASPECT: {
        if (messages[rowIndex]->content_->get_id() == messagePhoto::ID) {
            auto contentPhotoPtr = static_cast<messagePhoto *>
                    (messages[rowIndex]->content_.data());
            return (float)contentPhotoPtr->photo_->sizes_.back()->width_ / (float)
                    contentPhotoPtr->photo_->sizes_.back()->height_;
        }
        if (messages[rowIndex]->content_->get_id() == messageAnimation::ID) {
            auto contentAnimationPtr = static_cast<messageAnimation *>
                    (messages[rowIndex]->content_.data());
            return (float)contentAnimationPtr->animation_->width_ / (float)
                    contentAnimationPtr->animation_->height_;
        }
        return QVariant();
    }
    case DOCUMENT_NAME: {
        if (messages[rowIndex]->content_->get_id() == messageDocument::ID) {
            auto contentDocumentPtr = static_cast<messageDocument *>
                    (messages[rowIndex]->content_.data());
            return QString::fromStdString(contentDocumentPtr->document_->file_name_);
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
        return dataFileMeta(rowIndex, role);
        break;

    case MESSAGE_TYPE: {
        if (messages[rowIndex]->chat_id_ == 0)
            return SYSTEM_NEW_MESSAGE;
        if (messages[rowIndex]->content_->get_id() == messageText::ID)
            return TEXT;
        if (messages[rowIndex]->content_->get_id() == messagePhoto::ID)
            return PHOTO;
        if (messages[rowIndex]->content_->get_id() == messageSticker::ID)
            return STICKER;
        if (messages[rowIndex]->content_->get_id() == messageDocument::ID)
            return DOCUMENT;
        if (messages[rowIndex]->content_->get_id() == messageAnimation::ID)
            return ANIMATION;
        return UNDEFINED;
        break;
    }
    case SENDING_STATE:
        if (messages[rowIndex]->sending_state_.data()) {
            if (messages[rowIndex]->sending_state_->get_id() == messageSendingStatePending::ID)
                return Sending_Pending;
            if (messages[rowIndex]->sending_state_->get_id() == messageSendingStateFailed::ID)
                return Sending_Failed;
        }
        if (messages[rowIndex]->is_outgoing_) {
            if (messages[rowIndex]->id_ <= lastOutboxId())
                return Sending_Read;
            else
                return Sending_Not_Read;
        } else {
            if (messages[rowIndex]->id_ <= lastMessage().toLongLong())
                return Sending_Read;
            else
                return Sending_Not_Read;
        }
        break;
    case MEDIA_PREVIEW:
        if (messages[rowIndex]->content_->get_id() == messageAnimation::ID) {
            auto contentAnimationPtr = static_cast<messageAnimation *>(messages[rowIndex]->content_.data());
            if(contentAnimationPtr->animation_->thumbnail_->photo_->local_->is_downloading_completed_)
                                return QString::fromStdString(contentAnimationPtr->animation_->thumbnail_->photo_->local_->path_);
            else {
                int fileId = contentAnimationPtr->animation_->thumbnail_->photo_->id_;
                emit downloadFileStart(fileId, 12, rowIndex);
            }
            return QVariant();
        }
        break;
        //        FORWARD_INFO,
        //        VIEWS,
        //        REPLY_MARKUP

    default:
        break;
    }

    return QVariant();
}

int MessagingModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return messages.size();
}

QHash<int, QByteArray> MessagingModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ID] = "id";
    roles[SENDER_USER_ID] = "sender_user_id";
    roles[SENDER_PHOTO] = "sender_photo";
    roles[AUTHOR] = "author";
    roles[CHAT_ID] = "chat_id";
    roles[SENDING_STATE] = "sending_state";
    roles[IS_OUTGOING] = "is_outgoing";
    roles[CAN_BE_EDITED] = "can_be_edited";
    roles[CAN_BE_FORWARDED] = "can_be_forwarded";
    roles[CAN_BE_DELETED_ONLY_FOR_YOURSELF] = "can_be_deleted_only_for_yourself";
    roles[CAN_BE_DELETED_FOR_ALL_USERS] = "can_be_deleted_for_all_users";
    roles[IS_CHANNEL_POST] = "is_channel_post";
    roles[CONTAINS_UNREAD_MENTION] = "contains_unread_mention";
    roles[DATE] = "date";
    roles[EDIT_DATE] = "edit_date";
    roles[FORWARD_INFO] = "forward_info";
    roles[REPLY_TO_MESSAGE_ID] = "reply_to_message_id";
    roles[TTL] = "ttl";
    roles[TTL_EXPIRES_IN] = "ttl_expires_in";
    roles[VIA_BOT_USER_ID] = "via_bot_user_id";
    roles[AUTHOR_SIGNATURE] = "author_signature";
    roles[VIEWS] = "views";
    roles[MEDIA_ALBUM_ID] = "media_album_id";
    roles[MEDIA_PREVIEW] = "media_preview";
    roles[CONTENT] = "content";
    roles[FILE_CAPTION] = "file_caption";
    roles[PHOTO_ASPECT] = "photo_aspect";
    roles[DOCUMENT_NAME] = "document_name";
    roles[FILE_DOWNLOADED_SIZE] = "file_downloaded_size";
    roles[FILE_UPLOADED_SIZE] = "file_uploaded_size";
    roles[FILE_IS_DOWNLOADING] = "file_is_downloading";
    roles[FILE_IS_UPLOADING] = "file_is_uploading";
    roles[FILE_DOWNLOADING_COMPLETED] = "file_downloading_completed";
    roles[FILE_UPLOADING_COMPLETED] = "file_uploading_completed";

    roles[REPLY_MARKUP] = "reply_markup";
    roles[MESSAGE_TYPE] = "message_type";

    return roles;
}

void MessagingModel::fetchMore(const QModelIndex & /*parent*/)
{

    qint64 lastMessageOutboxId = 0;
    if (currentMessage().length() > 0)
        lastMessageOutboxId = m_currentMessage.toLongLong();

    fetchPending = true;
    if (rowCount(QModelIndex()) == 0)
        tdlibJson->getChatHistory(peerId().toLongLong(), lastMessageOutboxId, -2,
                                  MESSAGE_LIMIT, false);
    else
        tdlibJson->getChatHistory(peerId().toLongLong(), messages.last()->id_, 0, MESSAGE_LIMIT,
                                  false, "append");
}

bool MessagingModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return true;
}

Enums::ChatType MessagingModel::chatType() const
{
    return m_chatType;
}

QString MessagingModel::action() const
{
    return m_action;
}

QString MessagingModel::currentMessage() const
{
    return m_currentMessage;
}

QString MessagingModel::lastMessage() const
{
    return m_lastMessage;
}

bool MessagingModel::atYEnd() const
{
    return m_atYEnd;
}

void MessagingModel::chatActionCleanUp()
{
    chatActionUserMap.clear();
    chatActionTimer.stop();
    setAction("");
}

void MessagingModel::getFile(const int fileId, const int priority, const int indexItem)
{
    tdlibJson->downloadFile(fileId, priority);
    messagePhotoQueue[fileId] = indexItem;
}

void MessagingModel::getAvatar(const qint64 fileId, const int priority, const int indexItem)
{
    if (!avatarPhotoQueue.contains(fileId)) {
        tdlibJson->downloadFile(fileId, priority);
        avatarPhotoQueue[fileId] = QVector<int>();
    }
    if (!avatarPhotoQueue[fileId].contains(indexItem))
        avatarPhotoQueue[fileId].append(indexItem);


}


void MessagingModel::updateChatReadInbox(const QJsonObject &inboxObject)
{
    qint64 chatId = ParseObject::getInt64(inboxObject["chat_id"]);
    if (chatId == peerId().toLongLong()) {
        qint64 lastReadId = ParseObject::getInt64(inboxObject["last_read_inbox_message_id"]);
        setLastMessage(QString::number(lastReadId));
        QVector<int> stateRole;
        stateRole.append(SENDING_STATE);
        emit dataChanged(index(0), index(messages.size() - 1), stateRole);
    }
}

void MessagingModel::updateChatReadOutbox(const QJsonObject &outboxObject)
{
    qint64 chatId = ParseObject::getInt64(outboxObject["chat_id"]);
    if (chatId == peerId().toLongLong()) {
        qint64 lastReadId = ParseObject::getInt64(outboxObject["last_read_outbox_message_id"]);
        setLastOutboxId(lastReadId);
        QVector<int> stateRole;
        stateRole.append(SENDING_STATE);
        emit dataChanged(index(0), index(messages.size() - 1), stateRole);
    }
}

void MessagingModel::appendMessages(const QJsonObject &messagesObject)
{
    int totalCount = messagesObject["total_count"].toInt();
    QString extra = messagesObject["@extra"].toString("");

    QVariantList messagesIds;

    QJsonArray messagesArray = messagesObject["messages"].toArray();
    if (extra == "prepend") {
        for (int r_i = messagesArray.size() - 1; r_i != -1; r_i--) {
            if (ParseObject::getInt64(messagesArray[r_i].toObject()["id"]) > messages.first()->id_) {
                prependMessage(messagesArray[r_i].toObject());
                messagesIds.append(messagesArray[r_i].toObject()["id"].toVariant());

            }
        }
    } else if (extra == "append") {
        for (auto obj : messagesArray) {
            beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));
            appendMessage(obj.toObject());
            messagesIds.append(obj.toObject()["id"].toVariant());
            endInsertRows();
        }
    } else {
        beginInsertRows(QModelIndex(), 0, totalCount + 1);
        for (auto obj : messagesArray) {
            if (currentMessage() != lastMessage()
                    && currentMessage().toLongLong() == ParseObject::getInt64(obj.toObject()["id"])) {
                const QByteArray messageSeparator =
                        " {         \"@type\": \"message\",         \"author_signature\": \"\",         \"can_be_deleted_for_all_users\": false,         \"can_be_deleted_only_for_self\": false,         \"can_be_edited\": false,         \"can_be_forwarded\": false,         \"chat_id\": 0,         \"contains_unread_mention\": false,         \"content\": {             \"@type\": \"messageText\",             \"text\": {                 \"@type\": \"formattedText\",                 \"entities\": [                 ],                 \"text\": \"new message separator\"             }         },         \"date\": 0,         \"edit_date\": 0,         \"id\": 0,         \"is_channel_post\": false,         \"is_outgoing\": false,         \"media_album_id\": \"0\",         \"reply_to_message_id\": 0,         \"sender_user_id\": 0,         \"ttl\": 0,         \"ttl_expires_in\": 0,         \"via_bot_user_id\": 0,         \"views\": 0     } ";

                appendMessage(QJsonDocument::fromJson(messageSeparator).object());
            }
            appendMessage(obj.toObject());
            messagesIds.append(obj.toObject()["id"].toVariant());

        }
        endInsertRows();

    }
    viewMessages(messagesIds);
    fetchPending = false;
}

void MessagingModel::appendMessage(const QJsonObject &messageObject)
{
    auto messageItem = ParseObject::parseMessage(messageObject);
    messages.append(messageItem);

    bool is_uploading = data(index(messages.size() - 1), FILE_IS_UPLOADING).toBool();
    bool is_downloading = data(index(messages.size() - 1), FILE_IS_DOWNLOADING).toBool()  ;
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

        if (fileId > 0)
            messagePhotoQueue[fileId] = messages.size() - 1;
    }

    if (messages.size() == 1)
        emit firstIdChanged();
}

QVariant MessagingModel::dataContent(const int rowIndex) const
{
    if (messages[rowIndex]->content_.data() != nullptr) {
        if (messages[rowIndex]->content_->get_id() == messageText::ID) {
            auto contentPtr = static_cast<messageText *>
                    (messages[rowIndex]->content_.data());
            if (contentPtr->text_.data() != nullptr)
                return QString::fromStdString(contentPtr->text_->text_);
        }
        //Returns local filepath to View for QImageProvider
        if (messages[rowIndex]->content_->get_id() == messagePhoto::ID) {
            auto contentPhotoPtr = static_cast<messagePhoto *>
                    (messages[rowIndex]->content_.data());
            int sizesCount = contentPhotoPtr->photo_->sizes_.size();
            if (sizesCount > 0) {
                if (contentPhotoPtr->photo_->sizes_[sizesCount - 1]->photo_->local_->is_downloading_completed_)
                    return QString::fromStdString(contentPhotoPtr->photo_->sizes_[sizesCount -
                            1]->photo_->local_->path_);
                else if (contentPhotoPtr->photo_->sizes_[0]->photo_->local_->is_downloading_completed_) {
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
        if (messages[rowIndex]->content_->get_id() == messageSticker::ID) {
            auto contentPhotoPtr = static_cast<messageSticker *>
                    (messages[rowIndex]->content_.data());
            if (contentPhotoPtr->sticker_->sticker_->local_->is_downloading_completed_)
                return QString::fromStdString(contentPhotoPtr->sticker_->sticker_->local_->path_);
            else {
                int fileId = contentPhotoPtr->sticker_->sticker_->id_;
                emit downloadFileStart(fileId, 12, rowIndex);
                return QVariant();
            }
        }
        if (messages[rowIndex]->content_->get_id() == messageDocument::ID) {
            auto contentDocumentPtr = static_cast<messageDocument *>
                    (messages[rowIndex]->content_.data());
            return QString::fromStdString(contentDocumentPtr->document_->document_->local_->path_);

        }
        if (messages[rowIndex]->content_->get_id() == messageAnimation::ID) {
            auto contentAnimationPtr = static_cast<messageAnimation *>
                    (messages[rowIndex]->content_.data());
            if (contentAnimationPtr->animation_->animation_->local_->is_downloading_completed_)
                return QString::fromStdString(contentAnimationPtr->animation_->animation_->local_->path_);

        }
        if (messages[rowIndex]->content_->get_id() == messageUnsupported::ID)
            return "Unsupported message type";
    }
    return QVariant();
}

QVariant MessagingModel::dataFileMeta(const int rowIndex, int role) const
{
    file *filePtr = nullptr;
    if (messages[rowIndex]->content_->get_id() == messagePhoto::ID) {
        auto contentPhotoPtr = static_cast<messagePhoto *>
                (messages[rowIndex]->content_.data());
        int sizesCount = contentPhotoPtr->photo_->sizes_.size();
        filePtr = contentPhotoPtr->photo_->sizes_[sizesCount - 1]->photo_.data();
    }
    if (messages[rowIndex]->content_->get_id() == messageDocument::ID) {
        auto contentDocumentPtr = static_cast<messageDocument *>
                (messages[rowIndex]->content_.data());
        filePtr = contentDocumentPtr->document_->document_.data();
    }
    if (messages[rowIndex]->content_->get_id() == messageAnimation::ID) {
        auto contentAnimationPtr = static_cast<messageAnimation *>
                (messages[rowIndex]->content_.data());
        filePtr = contentAnimationPtr->animation_->animation_.data();
    }
    switch (role) {
    case FILE_IS_DOWNLOADING:
        if(filePtr)
            return filePtr->local_->is_downloading_active_;
        return QVariant();
        break;
    case FILE_IS_UPLOADING:
        if(filePtr)
            return filePtr->remote_->is_uploading_active_;
        return QVariant();
        break;
    case FILE_DOWNLOADING_COMPLETED:
        if(filePtr)
            return filePtr->local_->is_downloading_completed_;
        return QVariant();
        break;
    case FILE_UPLOADING_COMPLETED:
        if(filePtr)
            return filePtr->remote_->is_uploading_completed_;
        return QVariant();
        break;
    case FILE_DOWNLOADED_SIZE:
        if(filePtr)
            return filePtr->local_->downloaded_size_;
        return QVariant();
        break;
    case FILE_UPLOADED_SIZE:
        if(filePtr)
            return filePtr->remote_->uploaded_size_;
        return QVariant();
        break;
    default:
        return QVariant();
        break;
    }
}

void MessagingModel::prependMessage(const QJsonObject &messageObject)
{
    auto messageItem = ParseObject::parseMessage(messageObject);
    bool is_replaced = false;
    if (messageItem->sending_state_.data())
        if (messageItem->sending_state_->get_id() == messageSendingStatePending::ID) {
            for (int i = 0 ; i < messages.size(); i++)
                if (messages[i]->id_ == messageItem->id_) {
                    messages.replace(i, messageItem);
                    emit dataChanged(index(i), index(i));
                    is_replaced = true;
                    break;
                }
        }
    if (!is_replaced) {
        beginInsertRows(QModelIndex(), 0, 0);
        messages.prepend(messageItem);
        endInsertRows();
        if (messagePhotoQueue.keys().size() > 0) {
            for (int key : messagePhotoQueue.keys())
                messagePhotoQueue[key]++;
        }

    }

    bool is_downl_or_upl = data(index(0), FILE_IS_UPLOADING).toBool()
            || data(index(0), FILE_IS_DOWNLOADING).toBool()  ;
    if (is_downl_or_upl) {
        int fileId = -1;
        //Increment all ids in messagePhotoQueue
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
        if (fileId > 0)
            messagePhotoQueue[fileId] = 0;

    }
    emit firstIdChanged();

}

void MessagingModel::addMessageFromUpdate(const QJsonObject &messageUpdateObject)
{
    if (peerId() != messageUpdateObject["message"].toObject()["chat_id"].toVariant().toString())
        return;
    prependMessage(messageUpdateObject["message"].toObject());
    QVariantList ids;
    ids.append(messageUpdateObject["message"].toObject()["id"].toDouble());
    viewMessages(ids);
}

void MessagingModel::updateFile(const QJsonObject &fileObject)
{
    if (fileObject["@type"].toString() == "updateFile")
        processFile(fileObject["file"].toObject());
}
void MessagingModel::processFile(const QJsonObject &fileObject)
{
    auto file = ParseObject::parseFile(fileObject);
    //1. - can be file in message
    //2. - can be avatar photo
    if (messagePhotoQueue.keys().contains(file->id_)) {
        QVector<int> photoRole;
        if (messages[messagePhotoQueue[file->id_]]->content_->get_id() == messagePhoto::ID) {
            auto messagePhotoPtr = static_cast<messagePhoto *>
                    (messages[messagePhotoQueue[file->id_]]->content_.data());
            for (quint32 i = 0 ; i < messagePhotoPtr->photo_->sizes_.size(); i++) {
                if (messagePhotoPtr->photo_->sizes_[i]->photo_->id_ == file->id_) {
                    messagePhotoPtr->photo_->sizes_[i]->photo_ = file;
                    break;
                }
            }
        }
        if (messages[messagePhotoQueue[file->id_]]->content_->get_id() == messageSticker::ID) {
            auto messageStickerPtr = static_cast<messageSticker *>
                    (messages[messagePhotoQueue[file->id_]]->content_.data());
            if (messageStickerPtr->sticker_->sticker_->id_ == file->id_)
                messageStickerPtr->sticker_->sticker_ = file;
        }
        if (messages[messagePhotoQueue[file->id_]]->content_->get_id() == messageDocument::ID) {
            auto messageDocumentPtr = static_cast<messageDocument *>
                    (messages[messagePhotoQueue[file->id_]]->content_.data());
            if ( messageDocumentPtr->document_->document_->id_ == file->id_)
                messageDocumentPtr->document_->document_ = file;
        }
        if (messages[messagePhotoQueue[file->id_]]->content_->get_id() == messageAnimation::ID) {
            auto  messageAnimationPtr = static_cast<messageAnimation *>
                    (messages[messagePhotoQueue[file->id_]]->content_.data());
            if ( messageAnimationPtr->animation_->animation_->id_ == file->id_)
                messageAnimationPtr->animation_->animation_ = file;
            if ( messageAnimationPtr->animation_->thumbnail_->photo_->id_ == file->id_)
                messageAnimationPtr->animation_->thumbnail_->photo_ = file;

}
        if (file->local_->is_downloading_completed_)
        {
            photoRole.append(CONTENT);
            photoRole.append(MEDIA_PREVIEW);
        }
        photoRole.append(FILE_DOWNLOADED_SIZE);
        photoRole.append(FILE_UPLOADED_SIZE);
        photoRole.append(FILE_IS_DOWNLOADING);
        photoRole.append(FILE_IS_UPLOADING);
        photoRole.append(FILE_DOWNLOADING_COMPLETED);
        photoRole.append(FILE_UPLOADING_COMPLETED);
        photoRole.append(MESSAGE_TYPE);
        emit dataChanged(index(messagePhotoQueue[file->id_]),
                index(messagePhotoQueue[file->id_]), photoRole);
        if (file->local_->is_downloading_completed_ && file->remote_->is_uploading_completed_)
            messagePhotoQueue.remove(file->id_);

    }
    if (avatarPhotoQueue.keys().contains(file->id_)) {
        if (file->local_->is_downloading_completed_) {
            UsersModel::instance()->setSmallAvatar(messages[avatarPhotoQueue[file->id_].at(0)]->sender_user_id_,
                    file);
            QVector<int> avatarRole;
            avatarRole.append(SENDER_PHOTO);
            for (int itr : avatarPhotoQueue[file->id_])
                emit dataChanged(index(itr),
                                 index(itr), avatarRole);
            avatarPhotoQueue.remove(file->id_);
        }

    }
}

void MessagingModel::updateTotalCount(int totalCount)
{
    if (m_totalCount == totalCount)
        return;

    m_totalCount = totalCount;
}

void MessagingModel::updateChatAction(const QJsonObject &chatActionObject)
{
    auto action = ParseObject::parseChatAction(chatActionObject);
    if (action->chat_id_ != m_peerId.toLongLong())
        return;
    chatActionUserMap[action->user_id_] = action;
    if (chatActionUserMap.size() == 1) {
        chatActionTimer.start();
        QString userName = tdlibJson->parseObject->getFirstName(chatActionUserMap.first()->user_id_);
        setAction(userName + " is typing");
    } else
        setAction(QString::number(chatActionUserMap.size()) + " people are typing");

}

QString MessagingModel::userName() const
{
    return m_userName;
}

QString MessagingModel::peerId() const
{
    return m_peerId;
}

void MessagingModel::setUserName(QString userName)
{
    if (m_userName == userName)
        return;

    m_userName = userName;
    emit userNameChanged(userName);
}

void MessagingModel::setPeerId(QString peerId)
{
    if (m_peerId == peerId)
        return;

    m_peerId = peerId;
    m_UserStatus = UsersModel::instance()->getGroupStatus(m_peerId.toLongLong());

    emit peerIdChanged(peerId);
}

void MessagingModel::sendTextMessage(const QString &text,
                                     const QString &reply_id)
{
    Q_UNUSED(reply_id)
    TlStorerToString json;
    sendMessage sendMessageObject;
    sendMessageObject.chat_id_ = m_peerId.toLongLong();
    sendMessageObject.disable_notification_ = false;
    sendMessageObject.from_background_ = false;
    sendMessageObject.reply_to_message_id_ = 0;
    sendMessageObject.input_message_content_ = QSharedPointer<inputMessageText>(new inputMessageText);
    inputMessageText *ptr = static_cast<inputMessageText *>
            (sendMessageObject.input_message_content_.data());
    ptr->clear_draft_ = true;
    ptr->disable_web_page_preview_ = true;
    ptr->text_ = QSharedPointer<formattedText>(new formattedText);
    ptr->text_->text_ = text.toStdString();


    sendMessageObject.store(json, "input_message_content");
    QVariantMap originalObject = json.doc["input_message_content"].toMap();
    originalObject.remove("reply_markup");
    auto jsonObject = QJsonDocument::fromVariant(originalObject);
    tdlibJson->sendMessage(jsonObject.toJson());
}

void MessagingModel::sendPhotoMessage(const QString &filepath, const QString &reply_id,
                                      const QString &caption)
{
    Q_UNUSED(reply_id)

    TlStorerToString json;
    sendMessage sendMessageObject;
    sendMessageObject.chat_id_ = m_peerId.toLongLong();
    sendMessageObject.disable_notification_ = false;
    sendMessageObject.from_background_ = false;
    sendMessageObject.reply_to_message_id_ = 0;
    sendMessageObject.input_message_content_ = QSharedPointer<inputMessagePhoto>(new inputMessagePhoto);
    inputMessagePhoto *ptr = static_cast<inputMessagePhoto *>
            (sendMessageObject.input_message_content_.data());
    auto photoPtr = QSharedPointer<inputFileLocal>(new inputFileLocal);
    photoPtr->path_ = filepath.toStdString();
    ptr->photo_ = photoPtr;

    ptr->caption_ = QSharedPointer<formattedText>(new formattedText);
    ptr->caption_->text_ = caption.toStdString();


    sendMessageObject.store(json, "input_message_content");
    QString jsonString = QJsonDocument::fromVariant(json.doc["input_message_content"]).toJson();
    jsonString = jsonString.replace("\"null\"", "null");

    tdlibJson->sendMessage(jsonString);
}

void MessagingModel::sendDocumentMessage(const QString &filepath, const QString &reply_id,
                                         const QString &caption)
{
    Q_UNUSED(reply_id)

    TlStorerToString json;
    sendMessage sendMessageObject;
    sendMessageObject.chat_id_ = m_peerId.toLongLong();
    sendMessageObject.disable_notification_ = false;
    sendMessageObject.from_background_ = false;
    sendMessageObject.reply_to_message_id_ = 0;
    sendMessageObject.input_message_content_ = QSharedPointer<inputMessageDocument>
            (new inputMessageDocument);
    inputMessageDocument *ptr = static_cast<inputMessageDocument *>
            (sendMessageObject.input_message_content_.data());
    auto docPtr = QSharedPointer<inputFileLocal>(new inputFileLocal);
    docPtr->path_ = filepath.toStdString();
    ptr->document_ = docPtr;
    ptr->caption_ = QSharedPointer<formattedText>(new formattedText);
    ptr->caption_->text_ = caption.toStdString();

    sendMessageObject.store(json, "input_message_content");
    QString jsonString = QJsonDocument::fromVariant(json.doc["input_message_content"]).toJson();
    jsonString = jsonString.replace("\"null\"", "null");

    tdlibJson->sendMessage(jsonString);
}

void MessagingModel::downloadDocument(const int rowIndex)
{
    int fileId = -1;
    if (messages[rowIndex]->content_->get_id() == messageDocument::ID) {
        auto contentDocumentPtr = static_cast<messageDocument *>
                (messages[rowIndex]->content_.data());
        fileId = contentDocumentPtr->document_->document_->id_;
    }
    if (messages[rowIndex]->content_->get_id() == messagePhoto::ID) {
        auto contentDocumentPtr = static_cast<messagePhoto *>
                (messages[rowIndex]->content_.data());
        int sizesCount = contentDocumentPtr->photo_->sizes_.size();
        fileId = contentDocumentPtr->photo_->sizes_[sizesCount - 1]->photo_->id_;
    }
    if (messages[rowIndex]->content_->get_id() == messageAnimation::ID) {
        auto contentAnimationPtr = static_cast<messageAnimation *>
                (messages[rowIndex]->content_.data());
        fileId = contentAnimationPtr->animation_->animation_->id_;
    }

    if (fileId > -1)
        emit downloadFileStart(fileId, 10, rowIndex);
}

void MessagingModel::cancelDownload(const int rowIndex)
{
    int fileId = -1;
    if (messages[rowIndex]->content_->get_id() == messageDocument::ID) {
        auto contentDocumentPtr = static_cast<messageDocument *>
                (messages[rowIndex]->content_.data());
        fileId = contentDocumentPtr->document_->document_->id_;
    }
    if (messages[rowIndex]->content_->get_id() == messagePhoto::ID) {
        auto contentDocumentPtr = static_cast<messagePhoto *>
                (messages[rowIndex]->content_.data());
        int sizesCount = contentDocumentPtr->photo_->sizes_.size();
        fileId = contentDocumentPtr->photo_->sizes_[sizesCount - 1]->photo_->id_;
    }
    tdlibJson->cancelDownloadFile(fileId);
}

void MessagingModel::cancelUpload(const int rowIndex)
{
    int fileId = -1;
    if (messages[rowIndex]->content_->get_id() == messageDocument::ID) {
        auto contentDocumentPtr = static_cast<messageDocument *>
                (messages[rowIndex]->content_.data());
        fileId = contentDocumentPtr->document_->document_->id_;
    }
    if (messages[rowIndex]->content_->get_id() == messagePhoto::ID) {
        auto contentDocumentPtr = static_cast<messagePhoto *>
                (messages[rowIndex]->content_.data());
        int sizesCount = contentDocumentPtr->photo_->sizes_.size();
        fileId = contentDocumentPtr->photo_->sizes_[sizesCount - 1]->photo_->id_;
    }
    tdlibJson->cancelUploadFile(fileId);
}

void MessagingModel::deleteMessage(const int rowIndex, const bool revoke)
{
    if (rowIndex >= 0   && rowIndex < messages.size()) {
        qint64 chatId = messages[rowIndex]->chat_id_;
        QVector<qint64> messageIds;
        messageIds.append(messages[rowIndex]->id_);

        tdlibJson->deleteMessages(chatId, messageIds, revoke);

        //1. if exists in fileUpdates (rowIndex == fileIndex) -> remove
        //2. if rowIndex > fileIndex -> nothing
        //3. if rowIndex < fileIndex -> decrease by 1
        for (int key : messagePhotoQueue.keys()) {
            if (rowIndex < messagePhotoQueue[key]) {
                messagePhotoQueue[key]--;
                break;
            }
            if (rowIndex == messagePhotoQueue[key]) {
                messagePhotoQueue.remove(key);
            }
        }
        beginRemoveRows(QModelIndex(), rowIndex, rowIndex);
        messages.removeAt(rowIndex);
        endRemoveRows();

    }
    return;
}

void MessagingModel::joinChat()
{
    TlStorerToString json;
    chatMemberStatusMember statusJoin;
    statusJoin.store(json, "status");
    qDebug() << QJsonDocument::fromVariant(json.doc).toJson();

}

void MessagingModel::deleteMessages(QList<int> rowIndices, const bool revoke)
{
    std::sort(rowIndices.begin(), rowIndices.end(),
              [](const int a, const int b) -> bool
    { return a > b; });
    for (int index : rowIndices)
        deleteMessage(index, revoke);
    return;
}

void MessagingModel::viewMessages(const QVariantList &ids)
{
    bool force_read = false;
    tdlibJson->viewMessages(peerId(), ids, force_read);
    NotificationManager::instance()->removeNotification(peerId().toLongLong());

}

void MessagingModel::getNewMessages()
{
    if (messages.size() > 0
            && !fetchPending
            && !isUpdateConnected) {
        if (lastMessage().toLongLong() != messages.first()->id_) {
            fetchPending = true;
            tdlibJson->getChatHistory(peerId().toLongLong(), messages.first()->id_, MESSAGE_LIMIT * -1 + 1,
                                      MESSAGE_LIMIT, false, "prepend");
        }
    }
}

void MessagingModel::setChatType(const Enums::ChatType chatType)
{
    if (m_chatType == chatType)
        return;

    m_chatType = chatType;
    emit chatTypeChanged(chatType);
}

void MessagingModel::setAction(const QString &action)
{
    if (m_action == action)
        return;

    m_action = action;
    emit actionChanged(action);
}

void MessagingModel::updateMessageSend(const QJsonObject &updateMessageSendObject)
{
    auto messageItem = ParseObject::parseMessage(updateMessageSendObject["message"].toObject());
    qint64 messageId = ParseObject::getInt64(updateMessageSendObject["old_message_id"]);
    for (int i = 0; i < messages.size(); i++) {
        if (messages[i]->id_ == messageId) {
            messages.replace(i, messageItem);
            emit dataChanged(index(i), index(i));
            break;
        }
    }
    if (updateMessageSendObject["@type"] == "updateMessageSendFailed") {
        emit errorReceived(updateMessageSendObject["error_code"].toInt(),
                updateMessageSendObject["error_message"].toString());
    }

}

void MessagingModel::setCurrentMessage(const QString &currentMessage)
{
    if (m_currentMessage == currentMessage)
        return;

    m_currentMessage = currentMessage;
    emit currentMessageChanged(currentMessage);
}

void MessagingModel::setLastMessage(QString lastMessage)
{
    if (m_lastMessage == lastMessage)
        return;

    m_lastMessage = lastMessage;
    emit lastMessageChanged(lastMessage);
}

void MessagingModel::setAtYEnd(bool atYEnd)
{
    if (m_atYEnd == atYEnd)
        return;

    m_atYEnd = atYEnd;

    emit atYEndChanged(atYEnd);
}

} //namespace tdlibQt
