#include "MessagingModel.hpp"
#include "../ParseObject.hpp"
#include "../NotificationManager.hpp"
#include "../TdlibJsonWrapper.hpp"
#include <QVariantMap>
namespace tdlibQt {

MessagingModel::MessagingModel() :
    tdlibJson(TdlibJsonWrapper::instance())
{
    connect(tdlibJson, &TdlibJsonWrapper::newMessages,
            this, &MessagingModel::appendMessages);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateFile,
            this, &tdlibQt::MessagingModel::updateFile);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateChatReadInbox,
            this, &MessagingModel::updateChatReadInbox);
    connect(tdlibJson, &TdlibJsonWrapper::updateTotalCount,
            this, &MessagingModel::updateTotalCount);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateUserChatAction,
            this, &MessagingModel::updateChatAction);
    connect(this, &MessagingModel::downloadFileStart,
            this, &MessagingModel::getFile);

    connect(this, &MessagingModel::firstIdChanged, [this]() {
        if (messages.first()->id_ == lastMessage().toLongLong()) {
            isUpdateConnected = true;
            setAtYEnd(isUpdateConnected);
            connect(tdlibJson, &TdlibJsonWrapper::newMessageFromUpdate,
                    this, &MessagingModel::addMessageFromUpdate);
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
            if (messages[rowIndex]->content_->get_id() == messageUnsupported::ID)
                return "Unsupported message type";
        }
        break;
    case ID: //int64
        return QString::number( messages[rowIndex]->id_);
    case SENDER_USER_ID: //int64
        return QString::number( messages[rowIndex]->sender_user_id_);
    case AUTHOR:
        return tdlibJson->parseObject->getUserName(messages[rowIndex]->sender_user_id_);
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
    case PHOTO_CAPTION: {
        if (messages[rowIndex]->content_->get_id() == messagePhoto::ID) {
            auto contentPhotoPtr = static_cast<messagePhoto *>
                                   (messages[rowIndex]->content_.data());
            return QString::fromStdString(contentPhotoPtr->caption_->text_);
        }
        return QVariant();
    }
    case MESSAGE_TYPE: {
        if (messages[rowIndex]->chat_id_ == 0)
            return SYSTEM_NEW_MESSAGE;
        if (messages[rowIndex]->content_->get_id() == messageText::ID)
            return TEXT;
        if (messages[rowIndex]->content_->get_id() == messagePhoto::ID)
            return PHOTO;
        if (messages[rowIndex]->content_->get_id() == messageSticker::ID)
            return STICKER;

        return UNDEFINED;
        break;
    }
    //        SENDING_STATE,
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
    roles[CONTENT] = "content";
    roles[PHOTO_CAPTION] = "photo_caption";
    roles[REPLY_MARKUP] = "reply_markup";
    roles[MESSAGE_TYPE] = "message_type";

    return roles;
}

void MessagingModel::fetchMore(const QModelIndex &parent)
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
    qDebug() << "Can feych";
    return true;
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

void MessagingModel::updateChatReadInbox(const QJsonObject &outboxObject)
{
    qint64 chatId = ParseObject::getInt64(outboxObject["chat_id"]);
    if (chatId == peerId().toLongLong()) {
        qint64 lastReadId = ParseObject::getInt64(outboxObject["last_read_inbox_message_id"]);
        setLastMessage(QString::number(lastReadId));
    }
}

void MessagingModel::appendMessages(const QJsonObject &messagesObject)
{
    int totalCount = messagesObject["total_count"].toInt();
    QString extra = messagesObject["@extra"].toString("");

    qDebug() << extra;
    QVariantList messagesIds;

    QJsonArray messagesArray = messagesObject["messages"].toArray();
    if (extra == "prepend") {
        for (int r_i = messagesArray.size() - 1; r_i != -1; r_i--) {
            if (ParseObject::getInt64(messagesArray[r_i].toObject()["id"]) > messages.first()->id_) {
                beginInsertRows(QModelIndex(), 0, 0);
                prependMessage(messagesArray[r_i].toObject());
                messagesIds.append(messagesArray[r_i].toObject()["id"].toVariant());
                endInsertRows();

            }
        }
    } else if (extra == "append") {
        beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()) + totalCount);
        for (auto obj : messagesArray) {
            appendMessage(obj.toObject());
            messagesIds.append(obj.toObject()["id"].toVariant());
        }
        endInsertRows();
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
    if (messages.size() == 1)
        emit firstIdChanged();
}

void MessagingModel::prependMessage(const QJsonObject &messageObject)
{
    auto messageItem = ParseObject::parseMessage(messageObject);
    messages.prepend(messageItem);
    emit firstIdChanged();

}

void MessagingModel::addMessageFromUpdate(const QJsonObject &messageUpdateObject)
{
    if (peerId() != messageUpdateObject["message"].toObject()["chat_id"].toVariant().toString())
        return;
    beginInsertRows(QModelIndex(), 0, 0);
    prependMessage(messageUpdateObject["message"].toObject());
    endInsertRows();
    QVariantList ids;
    ids.append(messageUpdateObject["message"].toObject()["id"].toDouble());
    viewMessages(ids);
}

void MessagingModel::updateFile(const QJsonObject &fileObject)
{
    if (fileObject["@type"].toString() == "updateFile") {
        auto file = ParseObject::parseFile(fileObject["file"].toObject());
        if (messagePhotoQueue.keys().contains(file->id_)) {
            if (file->local_->is_downloading_completed_) {
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
                    messageStickerPtr->sticker_->sticker_ = file;
                }

                QVector<int> photoRole;
                photoRole.append(CONTENT);
                photoRole.append(MESSAGE_TYPE);
                emit dataChanged(index(messagePhotoQueue[file->id_]),
                                 index(messagePhotoQueue[file->id_]), photoRole);
                messagePhotoQueue.remove(file->id_);
            }

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
        setAction( userName + " is typing");
    } else
        setAction(QString::number(chatActionUserMap.size()) + " is typing");

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
    tdlibJson->sendTextMessage(jsonObject.toJson());
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

void MessagingModel::setAtYEnd(bool atYEnd)
{
    if (m_atYEnd == atYEnd)
        return;

    m_atYEnd = atYEnd;

    emit atYEndChanged(atYEnd);
}

} //namespace tdlibQt
