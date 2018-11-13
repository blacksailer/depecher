#include "MessagingModel.hpp"
#include "../ParseObject.hpp"
#include "../TdlibJsonWrapper.hpp"
#include "../NotificationManager.hpp"
#include "singletons/UsersModel.hpp"
#include <QVariantMap>
#include <QGuiApplication>

namespace tdlibQt {

constexpr int MESSAGE_LIMIT = 50;
constexpr int FETCH_OFFSET = 10;

MessagingModel::MessagingModel() :
    tdlibJson(TdlibJsonWrapper::instance()),
    m_NotificationsManager(NotificationManager::instance())
{
    /* Reply Workthrough
     * 1. Create map of replyMessagesMap, queue of messagesId +
     * 2.1 With every call of appendMessages(); call getMessages +
     * 2.2 Parse response from getMessages to  fill replyMessagesMap +
     * 2.3 Modify data() to return replyMessage values +
     * 3. Test UI +
     * 4. On click  append MessageId to queue of MessagesId to replyMessage
     * 4.1 if in message array scroll to message
     * 4.2 If not in message array, clear all, unconnect updates, and get messages with reply_id
     * 5. highlight for two seconds replyId message
     * 5. On return dequeue messageId
     * 5.1 if in message array scroll to message
     * 5.2 If not in message array, clear all, unconnect updates, and get messages with messageId
     * 6.  highlight for two seconds messageId message
     * 7. Test UI
     */

    connect(tdlibJson, &TdlibJsonWrapper::newMessages,
            this, &MessagingModel::appendMessages);
    connect(tdlibJson, &TdlibJsonWrapper::messageReceived,
            this, &MessagingModel::appendMessage);
    connect(tdlibJson, &TdlibJsonWrapper::callbackQueryAnswerReceived,
            this, &MessagingModel::onCallbackAnswerReceived);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateFile,
            this, &tdlibQt::MessagingModel::updateFile);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::fileReceived,
            this, &tdlibQt::MessagingModel::processFile);

    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateChatReadInbox,
            this, &MessagingModel::updateChatReadInbox);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateChatReadOutbox,
            this, &MessagingModel::updateChatReadOutbox);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateMessageEdited,
            this, &MessagingModel::onMessageEdited);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateMessageContent,
            this, &MessagingModel::onMessageContentEdited);
    connect(tdlibJson, &TdlibJsonWrapper::updateTotalCount,
            this, &MessagingModel::updateTotalCount);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateUserChatAction,
            this, &MessagingModel::updateChatAction);
    connect(this, &MessagingModel::downloadFileStart,
            this, &MessagingModel::getFile);
    connect(this, &MessagingModel::downloadAvatarStart,
            this, &MessagingModel::getAvatar);
    connect(this, &MessagingModel::isActiveChanged,
            this, &MessagingModel::onActiveChanged);
    connect(tdlibJson, &TdlibJsonWrapper::updateMessageSendSucceeded,
            this, &MessagingModel::updateMessageSend);
    connect(tdlibJson, &TdlibJsonWrapper::updateDeleteMessages,
            this, &MessagingModel::onMessageDeleted);

    connect(tdlibJson, &TdlibJsonWrapper::updateMessageSendFailed,
            this, &MessagingModel::updateMessageSend);
    connect(this, &MessagingModel::viewMessagesChanged,
            m_NotificationsManager, &NotificationManager::onViewMessages);
    connect(this, &MessagingModel::firstIdChanged, [this]() {
        if (messages.last()->id_ == lastMessage().toLongLong()) {
            if (!isUpdateConnected)
                connect(tdlibJson, &TdlibJsonWrapper::newMessageFromUpdate,
                        this, &MessagingModel::addMessageFromUpdate);
            isUpdateConnected = true;
            setAtYEnd(isUpdateConnected);
        }
    });

    m_NotificationsManager->currentViewableChatId = static_cast<qint64>(peerId().toLongLong());
    connect(&chatActionTimer, &QTimer::timeout, this, &MessagingModel::chatActionCleanUp);
    chatActionTimer.setInterval(5 * 1000);
}

MessagingModel::~MessagingModel()
{
    m_NotificationsManager->currentViewableChatId = 0;
}


QVariant MessagingModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int rowIndex = index.row();
    if (rowIndex > rowCount(QModelIndex()))
        return QVariant();
    if (rowIndex == FETCH_OFFSET)
        emit fetchOldMessages();
    switch (role) {
    case CONTENT:
        return dataContent(rowIndex);
    case ID: //int64
        return QString::number(messages[rowIndex]->id_);
    case SENDER_USER_ID: //int64
        return QString::number(messages[rowIndex]->sender_user_id_);
    case SENDER_PHOTO: {
        auto profilePhotoPtr = UsersModel::instance()->getUserPhoto(messages[rowIndex]->sender_user_id_);
        if (profilePhotoPtr.data()) {
            if (profilePhotoPtr->small_.data()) {
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
        return QString::number(messages[rowIndex]->chat_id_);
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
    case REPLY_TO_MESSAGE_ID: { //int64
        if (messages[rowIndex]->reply_to_message_id_ == 0)
            return rowIndex;


        return findIndexById(messages[rowIndex]->reply_to_message_id_);
    }
    case REPLY_AUTHOR: {
        if (messages[rowIndex]->reply_to_message_id_ == 0)
            return QVariant();
        //А как оповестить потомка что появился реплай в мапе?
        // 1. Сигналом модели
        if (replyMessagesMap.contains(messages[rowIndex]->reply_to_message_id_)) {
            return UsersModel::instance()->getUserFullName(replyMessagesMap[messages[rowIndex]->reply_to_message_id_]->sender_user_id_);
        }
        return QVariant();
    }
    case REPLY_MESSAGE: {
        if (messages[rowIndex]->reply_to_message_id_ == 0)
            return QVariant();
        //А как оповестить потомка что появился реплай в мапе?
        // 1. Сигналом модели
        if (replyMessagesMap.contains(messages[rowIndex]->reply_to_message_id_)) {
            if (replyMessagesMap[messages[rowIndex]->reply_to_message_id_]->content_->get_id() == messageText::ID) {
                auto contentPtr = static_cast<messageText *>
                                  (replyMessagesMap[messages[rowIndex]->reply_to_message_id_]->content_.data());
                if (contentPtr->text_.data() != nullptr)
                    return QString::fromStdString(contentPtr->text_->text_);
                return QVariant();
            } else
                return messageTypeToString(replyMessagesMap[messages[rowIndex]->reply_to_message_id_]->content_.data());
        }
        return QVariant();
    }
    case TTL:
        return messages[rowIndex]->ttl_;
    case TTL_EXPIRES_IN:
        return messages[rowIndex]->ttl_expires_in_;
    case AUTHOR_SIGNATURE:
        return QString::fromStdString(messages[rowIndex]->author_signature_);
    case VIEWS:
        return messages[rowIndex]->views_;
    case MEDIA_ALBUM_ID:
        return QString::number(messages[rowIndex]->media_album_id_);
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
    case FILE_TYPE:
        return dataFileMeta(rowIndex, role);
        break;
    case STICKER_SET_ID:
        if (messages[rowIndex]->content_->get_id() == messageSticker::ID) {
            auto contentStickerPtr = static_cast<messageSticker *>
                                     (messages[rowIndex]->content_.data());
            return QString::number(contentStickerPtr->sticker_->set_id_);
        }
        return QVariant();
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
        if (messages[rowIndex]->content_->get_id() == messageContact::ID)
            return CONTACT;
        if (messages[rowIndex]->content_->get_id() == messageChatJoinByLink::ID)
            return JOINBYLINK;
        if (messages[rowIndex]->content_->get_id() == messageContactRegistered::ID)
            return CONTACT_REGISTERED;
        if (messages[rowIndex]->content_->get_id() == messageSupergroupChatCreate::ID)
            return CHAT_CREATED;
        if (messages[rowIndex]->content_->get_id() == messageBasicGroupChatCreate::ID)
            return CHAT_CREATED;
        return UNDEFINED;
        break;
    }
    case SENDING_STATE:
        if (messages[rowIndex]->sending_state_.data()) {
            if (messages[rowIndex]->sending_state_->get_id() == messageSendingStatePending::ID)
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Pending);
            if (messages[rowIndex]->sending_state_->get_id() == messageSendingStateFailed::ID)
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Failed);
        }
        if (messages[rowIndex]->is_outgoing_) {
            if (messages[rowIndex]->id_ <= lastOutboxId())
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Read);
            else
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Not_Read);
        } else {
            if (messages[rowIndex]->id_ <= lastMessage().toLongLong())
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Read);
            else
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Not_Read);
        }
        break;
    case MEDIA_PREVIEW:
        if (messages[rowIndex]->content_->get_id() == messageAnimation::ID) {
            auto contentAnimationPtr = static_cast<messageAnimation *>(messages[rowIndex]->content_.data());
            if (contentAnimationPtr->animation_->thumbnail_->photo_->local_->is_downloading_completed_)
                return QString::fromStdString(contentAnimationPtr->animation_->thumbnail_->photo_->local_->path_);
            else {
                int fileId = contentAnimationPtr->animation_->thumbnail_->photo_->id_;
                emit downloadFileStart(fileId, 12, rowIndex);
            }
            return QVariant();
        }
        break;

    case REPLY_MARKUP:
        if (messages[rowIndex]->reply_markup_.data()) {
            if (messages[rowIndex]->reply_markup_->get_id() == replyMarkupInlineKeyboard::ID) {
                auto replyMarkupPtr = static_cast<replyMarkupInlineKeyboard *>(messages[rowIndex]->reply_markup_.data());
                QVariantList rowsButtons;
                for (auto row : replyMarkupPtr->rows_) {
                    QVariantList cellInRowButtons;
                    for (auto cell : row) {
                        TlStorerToString json;
                        cell->store(json, "button");
                        cellInRowButtons.append(json.doc["button"]);
                    }
                    rowsButtons.append(QVariant());
                    rowsButtons.back() = cellInRowButtons;

                }
                return rowsButtons;
            }
        }
        return QVariant();
        break;

    case SECTION: {
        auto messageDateTime = QDateTime::fromTime_t(messages[rowIndex]->date_);
        auto messageDate = messageDateTime.date();
        auto DateTimestamp = QDateTime::fromString(messageDate.toString(Qt::ISODate), Qt::ISODate);
        return DateTimestamp.toTime_t();
    }
    //        FORWARD_INFO,
    //        VIEWS,

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
    roles[MEMBER_STATUS] = "member_status";
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
    roles[REPLY_AUTHOR] = "reply_author";
    roles[REPLY_MESSAGE] = "reply_message";
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
    roles[FILE_TYPE] = "file_type";
    roles[STICKER_SET_ID] = "sticker_set_id";
    roles[REPLY_MARKUP] = "reply_markup";
    roles[MESSAGE_TYPE] = "message_type";
    roles[SECTION] = "section";
    return roles;
}

void MessagingModel::fetchMore(const QModelIndex & /*parent*/)
{
    qint64 lastMessageId =  lastInbox().toLongLong();
    //If do not check this, and in chat no new messages, getChatHistory returns 1 message. UI issue.
    if ((qint64)lastOutboxId() == lastMessage().toLongLong())
        lastMessageId = (qint64)lastOutboxId();

    fetchPending = true;
    if (rowCount(QModelIndex()) == 0) {
        if (lastMessageId != lastMessage().toLongLong())
            tdlibJson->getChatHistory(peerId().toLongLong(), lastMessageId, -10,
                                      MESSAGE_LIMIT, false);
        else
            tdlibJson->getChatHistory(peerId().toLongLong(), lastMessageId, -1,
                                      MESSAGE_LIMIT, false);
    } else {
        tdlibJson->getChatHistory(peerId().toLongLong(), messages.last()->id_, MESSAGE_LIMIT * -1 + 1, MESSAGE_LIMIT,
                                  false, "append");
    }
}

bool MessagingModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return !fetchPending && !atYEnd();
}

QVariantMap MessagingModel::chatType() const
{
    return m_chatType;
}

QString MessagingModel::action() const
{
    return m_action;
}

QString MessagingModel::lastInbox() const
{
    return m_lastMessageInbox;
}

QString MessagingModel::lastMessage() const
{
    return m_lastMessage;
}

bool MessagingModel::atYEnd() const
{
    return m_atYEnd;
}

double MessagingModel::lastOutboxId() const
{
    return m_lastOutboxId;
}

QVariant MessagingModel::memberStatus() const
{
    auto status = m_UserStatus;
    if (status.data() == nullptr)
        return QVariant();
    if (status->get_id() == chatMemberStatusCreator::ID) {
        QVariantMap resultStatus;
        resultStatus["status"] = ChatMemberStatuses::Creator;
        resultStatus["is_member"] = static_cast<chatMemberStatusCreator *>(status.data())->is_member_;
        return resultStatus;
    }
    if (status->get_id() == chatMemberStatusAdministrator::ID) {
        QVariantMap resultStatus;
        resultStatus["status"] = ChatMemberStatuses::Administrator;
        resultStatus["can_be_edited"] = static_cast<chatMemberStatusAdministrator *>(status.data())->can_be_edited_;
        resultStatus["can_change_info"] = static_cast<chatMemberStatusAdministrator *>(status.data())->can_change_info_;
        resultStatus["can_delete_messages"] = static_cast<chatMemberStatusAdministrator *>(status.data())->can_delete_messages_;
        resultStatus["can_edit_messages"] = static_cast<chatMemberStatusAdministrator *>(status.data())->can_edit_messages_;
        resultStatus["can_invite_users"] = static_cast<chatMemberStatusAdministrator *>(status.data())->can_invite_users_;
        resultStatus["can_pin_messages"] = static_cast<chatMemberStatusAdministrator *>(status.data())->can_pin_messages_;
        resultStatus["can_post_messages"] = static_cast<chatMemberStatusAdministrator *>(status.data())->can_post_messages_;

        resultStatus["can_promote_members"] = static_cast<chatMemberStatusAdministrator *>(status.data())->can_promote_members_;
        resultStatus["can_restrict_members"] = static_cast<chatMemberStatusAdministrator *>(status.data())->can_restrict_members_;
        return resultStatus;
    }
    if (status->get_id() == chatMemberStatusBanned::ID) {
        QVariantMap resultStatus;
        resultStatus["status"] = ChatMemberStatuses::Banned;
        resultStatus["banned_until_date"] = static_cast<chatMemberStatusBanned *>(status.data())->banned_until_date_;
        return resultStatus;
    }
    if (status->get_id() == chatMemberStatusMember::ID) {
        QVariantMap resultStatus;
        resultStatus["status"] = ChatMemberStatuses::Member;
        return resultStatus;
    }
    if (status->get_id() == chatMemberStatusRestricted::ID) {
        QVariantMap resultStatus;
        resultStatus["status"] = ChatMemberStatuses::Restricted;
        resultStatus["can_add_web_page_previews"] = static_cast<chatMemberStatusRestricted *>(status.data())->can_add_web_page_previews_;
        resultStatus["can_send_media_messages"] = static_cast<chatMemberStatusRestricted *>(status.data())->can_send_media_messages_;
        resultStatus["can_send_messages"] = static_cast<chatMemberStatusRestricted *>(status.data())->can_send_messages_;
        resultStatus["can_send_other_messages"] = static_cast<chatMemberStatusRestricted *>(status.data())->can_send_other_messages_;
        resultStatus["is_member"] = static_cast<chatMemberStatusRestricted *>(status.data())->is_member_;
        resultStatus["restricted_until_date"] = static_cast<chatMemberStatusRestricted *>(status.data())->restricted_until_date_;
        return resultStatus;
    }
    if (status->get_id() == chatMemberStatusLeft::ID) {
        QVariantMap resultStatus;
        resultStatus["status"] = ChatMemberStatuses::Left;
        return resultStatus;

    }
    return QVariant();
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
        setLastInbox(QString::number(lastReadId));
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
    if (ParseObject::getInt64(messagesArray[0].toObject()["chat_id"]) == peerId().toDouble()) {
        qDebug() << "append extra:" << extra << "total Count" << totalCount;
        QVector<qint64> messageReplyIds;
        if (extra == "prepend" && totalCount == 0) {
            isAllOldMessages = true;
            setReachedHistoryEnd(true);
        }
        //Oldest
        if (extra == "prepend") {
            beginInsertRows(QModelIndex(), 0, totalCount - 1);
            for (int i = 0; i < messagesArray.size(); i++) {

                qint64 reply_id = ParseObject::getInt64(messagesArray[i].toObject()["reply_to_message_id"]);
                qDebug() << "Reply id" << reply_id;
                if (reply_id != 0)
                    messageReplyIds.append(reply_id);

                prependMessage(messagesArray[i].toObject());
                messagesIds.append(messagesArray[i].toObject()["id"].toVariant());
            }
            endInsertRows();
            setFetchOlderPending(false);
        } else if (extra == "append") {
            //Newest
            int totaltGoodMessages = 0;


            for (int r_i = messagesArray.size() - 1; r_i >= 0; r_i--) {
                auto obj = messagesArray[r_i];
                if (ParseObject::getInt64(obj.toObject()["id"]) > messages.last()->id_) {
                    totaltGoodMessages++;
                    messagesIds.append(obj.toObject()["id"].toVariant());
                }
            }
            if (totaltGoodMessages == 0)
                return;
            beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()) + totaltGoodMessages - 1);
            for (int r_i = messagesArray.size() - 1; r_i >= 0; r_i--) {
                auto obj = messagesArray[r_i];
                qint64 reply_id = ParseObject::getInt64(obj.toObject()["reply_to_message_id"]);
                qDebug() << "Reply id" << reply_id;

                if (reply_id != 0)
                    messageReplyIds.append(reply_id);

                if (ParseObject::getInt64(obj.toObject()["id"]) > messages.last()->id_) {
                    appendMessage(obj.toObject());
                }
            }
            endInsertRows();
        } else if (extra == "getReplies") {
            for (int i = 0; i < messagesArray.size(); i++) {
                auto obj = messagesArray[i].toObject();
                qint64 reply_message_id = ParseObject::getInt64(obj["id"]);
                replyMessagesMap[reply_message_id] = ParseObject::parseMessage(obj);
            }

            QVector<int> roles;
            roles.append(REPLY_AUTHOR);
            roles.append(REPLY_MESSAGE);
            emit dataChanged(index(0), index(messages.size() - 1), roles);

        } else {
            int indexToAppend = -1;
            int objTime = -1;

            beginInsertRows(QModelIndex(), 0, totalCount - 1);
            for (int i = 0; i < messagesArray.size(); i++) {
                auto obj = messagesArray[i];
                qint64 reply_id = ParseObject::getInt64(obj.toObject()["reply_to_message_id"]);
                qDebug() << "Reply id" << reply_id;
                if (reply_id != 0)
                    messageReplyIds.append(reply_id);
                prependMessage(obj.toObject());
                messagesIds.append(obj.toObject()["id"].toVariant());
            }
            endInsertRows();
            if (lastInbox() != lastMessage())
                for (int i = messages.size() - 1; i != -1; i--) {
                    if (lastInbox().toLongLong() == messages[i]->id_) {
                        indexToAppend = i;
                        objTime = messages[i]->date_;
                        break;
                    }
                }
            if (indexToAppend == -1) {
                setLastMessageIndex(messages.size() - 1);
                if (messageReplyIds.size() > 0)
                    tdlibJson->getMessages(peerId().toLongLong(), messageReplyIds, "getReplies");

                return;
            }
            indexToAppend++;
            setLastMessageIndex(indexToAppend);
            beginInsertRows(QModelIndex(), indexToAppend, indexToAppend);
            qint64 messageId = messages[indexToAppend - 1]->id_;
            const QByteArray messageSeparator =
                " {         \"@type\": \"message\",         \"author_signature\": \"\",         \"can_be_deleted_for_all_users\": false,         \"can_be_deleted_only_for_self\": false,         \"can_be_edited\": false,         \"can_be_forwarded\": false,         \"chat_id\": 0,         \"contains_unread_mention\": false,         \"content\": {             \"@type\": \"messageText\",             \"text\": {                 \"@type\": \"formattedText\",                 \"entities\": [                 ],                 \"text\": \"new message separator\"             }         },         \"date\": " + QString::number(objTime).toLatin1() + ",         \"edit_date\": 0,         \"id\": " + QString::number(messageId).toLatin1() + ",         \"is_channel_post\": false,         \"is_outgoing\": false,         \"media_album_id\": \"0\",         \"reply_to_message_id\": 0,         \"sender_user_id\": 0,         \"ttl\": 0,         \"ttl_expires_in\": 0,         \"via_bot_user_id\": 0,         \"views\": 0     } ";

            auto messageItem = ParseObject::parseMessage(QJsonDocument::fromJson(messageSeparator).object());

            messages.insert(indexToAppend, messageItem);
            endInsertRows();
        }


        viewMessages(messagesIds);
        qDebug() << "Reply id size" << messageReplyIds.size();

        if (messageReplyIds.size() > 0)
            tdlibJson->getMessages(peerId().toLongLong(), messageReplyIds, "getReplies");
        fetchPending = false;
    }
}

QString MessagingModel::messageTypeToString(MessageContent *messageContent) const
{
    switch (messageContent->get_id()) {
    case  messagePhoto::ID:
        return tr("Photo");
    case  messageDocument::ID:
        return tr("Document");
    case messageVideo::ID:
        return tr("Video");
    case messageAudio::ID:
        return tr("Audio");
    case messageVideoNote::ID:
        return tr("Video note");
    case messageAnimation::ID:
        return tr("GIF");
    case messageCall::ID:
        return tr("Call");
    case messageContact::ID:
        return tr("Contact");
    case messageVoiceNote::ID:
        return tr("Audio note");
    case messageVenue::ID:
        return tr("Venue");
    case messageUnsupported::ID:
        return tr("Unsupported");
    case messageSticker::ID:
        return tr("Sticker");
    default:
        return tr("Message content");
    }
}

void MessagingModel::appendMessage(const QJsonObject &messageObject)
{
    auto messageItem = ParseObject::parseMessage(messageObject);
    if (messageObject.contains("@extra")) {
        if (messageObject["@extra"].toString() != "") {
            replyMessagesMap[messageItem->id_] = messageItem;
            return;
        }
    }
    if (peerId().toLongLong() != messageItem->chat_id_)
        return;
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
        messages.append(messageItem);
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
        if (messages[rowIndex]->content_->get_id() == messageContact::ID) {
            auto contactPtr = static_cast<messageContact *>
                              (messages[rowIndex]->content_.data());
            QVariantMap contactData;
            contactData["phone_number"] = QString::fromStdString(contactPtr->contact_->phone_number_);
            contactData["first_name"] = QString::fromStdString(contactPtr->contact_->first_name_);
            contactData["last_name"] = QString::fromStdString(contactPtr->contact_->last_name_);
            contactData["user_id"] = contactPtr->contact_->user_id_;
            return contactData;
        }
        if (messages[rowIndex]->content_->get_id() == messageSupergroupChatCreate::ID) {
            auto createdPtr = static_cast<messageSupergroupChatCreate *>
                              (messages[rowIndex]->content_.data());
            return QString::fromStdString(createdPtr->title_);
        }
        if (messages[rowIndex]->content_->get_id() == messageBasicGroupChatCreate::ID) {
            auto createdPtr = static_cast<messageBasicGroupChatCreate *>
                              (messages[rowIndex]->content_.data());
            return QString::fromStdString(createdPtr->title_);
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
        if (messages[rowIndex]->content_->get_id() == messageAnimation::ID) {
            auto contentAnimationPtr = static_cast<messageAnimation *>
                                       (messages[rowIndex]->content_.data());
            return QString::fromStdString(contentAnimationPtr->animation_->mime_type_);
        }
        return QVariant();
    default:
        return QVariant();
        break;
    }
}

QSharedPointer<message> MessagingModel::findMessageById(const qint64 messageId) const
{
    QSharedPointer<message> result = QSharedPointer<message>(nullptr);
    for (int i = 0; i < messages.size(); i++) {
        if (messages[i]->id_ == messageId) {
            result = messages[i];
            break;
        }
    }

    return result;
}

int MessagingModel::findIndexById(const qint64 messageId) const
{
    int result = 0;
    for (int i = 0; i < messages.size(); i++) {
        if (messages[i]->id_ == messageId) {
            result = i;
            break;
        }
    }

    return result;
}

bool MessagingModel::canFetchOlder()
{
    return !isAllOldMessages;
}

void MessagingModel::prependMessage(const QJsonObject &messageObject)
{
    auto messageItem = ParseObject::parseMessage(messageObject);

    messages.prepend(messageItem);

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

    //    if (messages.size() == 1)
    emit firstIdChanged();

}

void MessagingModel::addMessageFromUpdate(const QJsonObject &messageUpdateObject)
{
    if (peerId() != messageUpdateObject["message"].toObject()["chat_id"].toVariant().toString())
        return;
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));
    appendMessage(messageUpdateObject["message"].toObject());
    endInsertRows();
    setLastMessage(QString::number(messages.last()->id_));
    QVariantList ids;
    ids.append(messageUpdateObject["message"].toObject()["id"].toDouble());
    if (isActive())
        viewMessages(ids);
    else {
        int64 messageId = ParseObject::getInt64(messageUpdateObject["message"].toObject()["id"]);
        unseenMessageIds.append(messageId);
    }
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
            if (messageDocumentPtr->document_->document_->id_ == file->id_)
                messageDocumentPtr->document_->document_ = file;
        }
        if (messages[messagePhotoQueue[file->id_]]->content_->get_id() == messageAnimation::ID) {
            auto  messageAnimationPtr = static_cast<messageAnimation *>
                                        (messages[messagePhotoQueue[file->id_]]->content_.data());
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

    setLastOutboxId(UsersModel::instance()->getLastMessageOutbox(m_peerId.toLongLong()));
    setLastMessage(QString::number(UsersModel::instance()->getLastMessageId(m_peerId.toLongLong())));
    setLastInbox(QString::number(UsersModel::instance()->getLastMessageInbox(m_peerId.toLongLong())));
    setUserName(UsersModel::instance()->getChatTitle(m_peerId.toLongLong()));
    setChatType(UsersModel::instance()->getChatType(m_peerId.toLongLong()));

    if (messages.size() > 0)
        emit firstIdChanged();
    emit peerIdChanged(peerId);
}

void MessagingModel::sendTextMessage(const QString &text,
                                     const QString &reply_id)
{
    TlStorerToString json;
    sendMessage sendMessageObject;
    sendMessageObject.chat_id_ = m_peerId.toLongLong();
    sendMessageObject.disable_notification_ = false;
    sendMessageObject.from_background_ = false;
    sendMessageObject.reply_to_message_id_ = reply_id.toLongLong();
    sendMessageObject.input_message_content_ = QSharedPointer<inputMessageText>(new inputMessageText);
    inputMessageText *ptr = static_cast<inputMessageText *>
                            (sendMessageObject.input_message_content_.data());
    ptr->clear_draft_ = true;
    ptr->disable_web_page_preview_ = true;
    ptr->text_ = QSharedPointer<formattedText>(new formattedText);
    ptr->text_->text_ = text.toStdString();

    if (reply_id != "0" && !replyMessagesMap.contains(reply_id.toLongLong())) {
        auto repliedMessage = findMessageById(reply_id.toLongLong());
        if (repliedMessage.data() != nullptr)
            replyMessagesMap[reply_id.toLongLong()] = repliedMessage;
    }

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

    if (reply_id != "0" && !replyMessagesMap.contains(reply_id.toLongLong())) {
        auto repliedMessage = findMessageById(reply_id.toLongLong());
        if (repliedMessage.data() != nullptr)
            replyMessagesMap[reply_id.toLongLong()] = repliedMessage;
    }

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

    if (reply_id != "0" && !replyMessagesMap.contains(reply_id.toLongLong())) {
        auto repliedMessage = findMessageById(reply_id.toLongLong());
        if (repliedMessage.data() != nullptr)
            replyMessagesMap[reply_id.toLongLong()] = repliedMessage;
    }

    sendMessageObject.store(json, "input_message_content");
    QString jsonString = QJsonDocument::fromVariant(json.doc["input_message_content"]).toJson();
    jsonString = jsonString.replace("\"null\"", "null");

    tdlibJson->sendMessage(jsonString);
}

void MessagingModel::sendStickerMessage(const int &fileId, const QString &reply_id)
{
    Q_UNUSED(reply_id)

    TlStorerToString json;
    sendMessage sendMessageObject;
    sendMessageObject.chat_id_ = m_peerId.toLongLong();
    sendMessageObject.disable_notification_ = false;
    sendMessageObject.from_background_ = false;
    sendMessageObject.reply_to_message_id_ = 0;
    sendMessageObject.input_message_content_ = QSharedPointer<inputMessageSticker>
            (new inputMessageSticker);
    inputMessageSticker *ptr = static_cast<inputMessageSticker *>
                               (sendMessageObject.input_message_content_.data());
    auto docPtr = QSharedPointer<inputFileId>(new inputFileId);
    docPtr->id_ = fileId;
    ptr->sticker_ = docPtr;
    ptr->width_ = 512;
    ptr->height_ = 512;

    if (reply_id != "0" && !replyMessagesMap.contains(reply_id.toLongLong())) {
        auto repliedMessage = findMessageById(reply_id.toLongLong());
        if (repliedMessage.data() != nullptr)
            replyMessagesMap[reply_id.toLongLong()] = repliedMessage;
    }

    sendMessageObject.store(json, "input_message_content");
    QString jsonString = QJsonDocument::fromVariant(json.doc["input_message_content"]).toJson();
    jsonString = jsonString.replace("\"null\"", "null");

    tdlibJson->sendMessage(jsonString);

}

void MessagingModel::getCallbackQueryAnswerFunc(const QString &messageId, const QString &payloadType, const QString &payloadData)
{
    getCallbackQueryAnswer obj;
    obj.chat_id_ = peerId().toLongLong();
    obj.message_id_ = messageId.toLongLong();
    if (payloadType == "inlineKeyboardButtonTypeCallback") {
        auto payload = QSharedPointer<callbackQueryPayloadData>(new callbackQueryPayloadData);
        payload->data_ = payloadData.toStdString();
        obj.payload_ = payload;
    }
    if (payloadType == "inlineKeyboardButtonTypeCallbackGame") {
        auto payload = QSharedPointer<callbackQueryPayloadGame>(new callbackQueryPayloadGame);
        payload->game_short_name_ = payloadData.toStdString();
        obj.payload_ = payload;
    }
    TlStorerToString json;
    obj.store(json, "getCallbackQueryAnswer");
    QString jsonString = QJsonDocument::fromVariant(json.doc["getCallbackQueryAnswer"]).toJson();
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

    if (qApp->applicationState() == Qt::ApplicationActive)    {
        tdlibJson->viewMessages(peerId(), ids, force_read);
        emit viewMessagesChanged(peerId().toLongLong());
    }
}

void MessagingModel::fetchOlder()
{
    if (messages.size() > 0 && canFetchOlder() && !fetchOlderPending()) {
        setFetchOlderPending(true);
        tdlibJson->getChatHistory(peerId().toLongLong(), messages.first()->id_, 0,
                                  MESSAGE_LIMIT, false, "prepend");
    }
}

void MessagingModel::setChatType(const QVariantMap &chatType)
{
    if (m_chatType == chatType)
        return;

    m_chatType = chatType;
    if (static_cast<tdlibQt::Enums::ChatType>(m_chatType["type"].toInt()) == tdlibQt::Enums::ChatType::Supergroup)
        m_UserStatus = UsersModel::instance()->getGroupStatus(m_chatType["supergroup_id"].toInt());
    emit memberStatusChanged(memberStatus());

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

void MessagingModel::onActiveChanged(const bool isActive)
{
    if (isActive) {
        if (unseenMessageIds.size() > 0)
            viewMessages(unseenMessageIds);
        unseenMessageIds.clear();
    }

}

void MessagingModel::onMessageContentEdited(const QJsonObject &updateMessageContentObject)
{
    qint64 chatId = ParseObject::getInt64(updateMessageContentObject["chat_id"]);
    if (peerId().toLongLong() != chatId)
        return;
    qint64 messageId = ParseObject::getInt64(updateMessageContentObject["message_id"]);
    auto newContent  = ParseObject::parseMessageContent(updateMessageContentObject["new_content"].toObject());
    for (int i = 0 ; i < messages.size(); i++) {
        if (messages[i]->id_ == messageId) {
            messages[i]->content_ = newContent;
            QVector<int> roles;
            roles.append(CONTENT);
            emit dataChanged(index(i), index(i), roles);
            break;
        }
    }
}

void MessagingModel::onMessageEdited(const QJsonObject &updateMessageEditedObject)
{
    qint64 chatId = ParseObject::getInt64(updateMessageEditedObject["chat_id"]);
    if (peerId().toLongLong() != chatId)
        return;
    qint64 messageId = ParseObject::getInt64(updateMessageEditedObject["message_id"]);
    int editDate = updateMessageEditedObject["edit_date"].toInt();
    auto replyMarkup  = ParseObject::parseReplyMarkup(updateMessageEditedObject["reply_markup"].toObject());
    for (int i = 0 ; i < messages.size(); i++) {
        if (messages[i]->id_ == messageId) {
            messages[i]->edit_date_ = editDate;
            messages[i]->reply_markup_ = replyMarkup;
            QVector<int> roles;
            roles.append(EDIT_DATE);
            roles.append(REPLY_MARKUP);
            emit dataChanged(index(i), index(i), roles);
            break;
        }
    }
}

void MessagingModel::onMessageDeleted(const QJsonObject &updateDeleteMessagesObject)
{
    bool fromCache = updateDeleteMessagesObject["from_cache"].toBool();
    if (fromCache)
        return;
    qint64 chatId = ParseObject::getInt64(updateDeleteMessagesObject["chat_id"]);
    if (chatId != peerId().toLongLong())
        return;
    bool isPermanent = updateDeleteMessagesObject["is_permanent"].toBool();
    QList<qint64> messageIds;
    for (auto val :  updateDeleteMessagesObject["message_ids"].toArray())
        messageIds.push_back(ParseObject::getInt64(val));
    while (messageIds.size() > 0) {
        qint64 id = messageIds.takeAt(0);
        for (int i = 0; i < messages.size(); i++) {
            if (messages[i]->id_ == id) {
                beginRemoveRows(QModelIndex(), i, i);
                messages.removeAt(i);
                endRemoveRows();
                break;
            }
        }
    }
}

void MessagingModel::onCallbackAnswerReceived(const QJsonObject &callbackAnswerObject)
{
    emit callbackQueryAnswerShow(callbackAnswerObject["text"].toString(), callbackAnswerObject["show_alert"].toBool());
}

void MessagingModel::setLastInbox(const QString &currentMessage)
{
    if (m_lastMessageInbox == currentMessage)
        return;

    m_lastMessageInbox = currentMessage;
    emit lastInboxChanged(currentMessage);
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

void MessagingModel::setLastOutboxId(double lastOutboxId)
{
    if (m_lastOutboxId == lastOutboxId)
        return;

    m_lastOutboxId = lastOutboxId;
    emit lastOutboxIdChanged(lastOutboxId);
}

void MessagingModel::setIsActive(bool isActive)
{
    if (m_isActive == isActive)
        return;

    m_isActive = isActive;
    emit isActiveChanged(m_isActive);
}

} //namespace tdlibQt
