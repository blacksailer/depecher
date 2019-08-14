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
     * 4.On click  append MessageId to queue of MessagesId to replyMessage +
     * 4.1 if in message array scroll to message +
     * 4.2 (if findMessageById == -1 )  If not in message array, clear all, unconnect updates, and get messages with reply_id
     * 5. highlight for two seconds replyId message +
     * 5. On return dequeue messageId +
     * 5.1 if in message array scroll to message
     * 5.2 If not in message array, clear all, unconnect updates, and get messages with messageId
     * 6.  highlight for two seconds messageId message
     * 7. Test UI
     */

    connect(tdlibJson, &TdlibJsonWrapper::newMessages,
            this, &MessagingModel::addMessages);
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
        if (m_messages.last()->id_ == lastMessage().toLongLong()) {
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
    userStatusTimer.setInterval(60 * 1000);
    connect(&chatActionTimer, &QTimer::timeout, this, &MessagingModel::updateStatus);
    connect(UsersModel::instance(), &UsersModel::userStatusChanged, this, &MessagingModel::updateStatus);
    userStatusTimer.start();
    //Adding empty item. fetchOlder issue
    beginInsertRows(QModelIndex(), 0, 0);
    endInsertRows();
}

MessagingModel::~MessagingModel()
{
    m_NotificationsManager->currentViewableChatId = 0;
}


QVariant MessagingModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() == 0 || index.row() > rowCount(QModelIndex()))
        return QVariant();
    //minus one because of invisible item. fetchOlder issue
    int rowIndex = index.row() - 1;

    switch (role) {
    case CONTENT:
        return dataContent(rowIndex);
    case ID: //int64
        return QString::number(m_messages[rowIndex]->id_);
    case SENDER_USER_ID: //int64
        return QString::number(m_messages[rowIndex]->sender_user_id_);
    case SENDER_PHOTO: {
        auto profilePhotoPtr = UsersModel::instance()->getUserPhoto(m_messages[rowIndex]->sender_user_id_);
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
        return UsersModel::instance()->getUserFullName(m_messages[rowIndex]->sender_user_id_);
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
    case REPLY_TO_MESSAGE_ID: { //int64
        return QString::number(m_messages[rowIndex]->reply_to_message_id_);

        if (m_messages[rowIndex]->reply_to_message_id_ == 0)
            return rowIndex;
        return findIndexById(m_messages[rowIndex]->reply_to_message_id_);
    }
    case REPLY_AUTHOR: {
        if (m_messages[rowIndex]->reply_to_message_id_ == 0)
            return QVariant();
        //А как оповестить потомка что появился реплай в мапе?
        // 1. Сигналом модели
        if (replyMessagesMap.contains(m_messages[rowIndex]->reply_to_message_id_)) {
            return UsersModel::instance()->getUserFullName(replyMessagesMap[m_messages[rowIndex]->reply_to_message_id_]->sender_user_id_);
        }
        return QVariant();
    }
    case REPLY_MESSAGE: {
        qint64 reply_id = m_messages[rowIndex]->reply_to_message_id_;
        if (reply_id == 0)
            return QVariant();
        //А как оповестить потомка что появился реплай в мапе?
        // 1. Сигналом модели
        if (replyMessagesMap.contains(reply_id)) {
            auto messagePtr = replyMessagesMap[reply_id]->content_;
            if (messagePtr->get_id() == messageText::ID) {
                messageText *contentPtr = static_cast<messageText *>
                                          (messagePtr.data());
                return QString::fromStdString(contentPtr->text_->text_);

            } else
                return ParseObject::messageTypeToString(messagePtr.data()->get_id());
        }
        return QVariant();
    }
    case TTL:
        return m_messages[rowIndex]->ttl_;
    case TTL_EXPIRES_IN:
        return m_messages[rowIndex]->ttl_expires_in_;
    case AUTHOR_SIGNATURE:
        return QString::fromStdString(m_messages[rowIndex]->author_signature_);
    case VIEWS:
        return m_messages[rowIndex]->views_;
    case MEDIA_ALBUM_ID:
        return QString::number(m_messages[rowIndex]->media_album_id_);
    case FORWARD_INFO: {
//        if (m_messages[rowIndex]->forward_info_.data()) {
        if (m_messages[rowIndex]->forward_info_->origin_.data()) {
            if (m_messages[rowIndex]->forward_info_->origin_->get_id() == messageForwardOriginUser::ID) {
                messageForwardOriginUser *messageForwardInfoPtr = static_cast<messageForwardOriginUser *>
                        (m_messages[rowIndex]->forward_info_->origin_.data());

                return UsersModel::instance()->getUserFullName(messageForwardInfoPtr->sender_user_id_);
            }
            if (m_messages[rowIndex]->forward_info_->origin_->get_id() == messageForwardOriginChannel::ID) {
                messageForwardOriginChannel *messageForwardInfoPtr = static_cast<messageForwardOriginChannel *>
                        (m_messages[rowIndex]->forward_info_->origin_.data());

                return UsersModel::instance()->getChatTitle(messageForwardInfoPtr->chat_id_);
            }
            if (m_messages[rowIndex]->forward_info_->origin_->get_id() == messageForwardOriginHiddenUser::ID) {
                messageForwardOriginHiddenUser *messageForwardInfoPtr = static_cast<messageForwardOriginHiddenUser *>
                        (m_messages[rowIndex]->forward_info_->origin_.data());

                return QString::fromStdString(messageForwardInfoPtr->sender_name_);
            }
        }

//        }
        return QVariant();
    }
    case RICH_FILE_CAPTION: {
        if (m_messages[rowIndex]->content_->get_id() == messagePhoto::ID) {
            auto contentPhotoPtr = static_cast<messagePhoto *>
                                   (m_messages[rowIndex]->content_.data());
            auto entities = contentPhotoPtr->caption_->entities_;
            return makeRichText(QString::fromStdString(contentPhotoPtr->caption_->text_), entities);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageDocument::ID) {
            auto contentDocumentPtr = static_cast<messageDocument *>
                                      (m_messages[rowIndex]->content_.data());
            auto entities = contentDocumentPtr->caption_->entities_;
            return makeRichText(QString::fromStdString(contentDocumentPtr->caption_->text_), entities);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageAnimation::ID) {
            auto contentAnimationPtr = static_cast<messageAnimation *>
                                       (m_messages[rowIndex]->content_.data());
            auto entities = contentAnimationPtr->caption_->entities_;
            return makeRichText(QString::fromStdString(contentAnimationPtr->caption_->text_), entities);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVoiceNote::ID) {
            auto contentVoicePtr = static_cast<messageVoiceNote *>
                                   (m_messages[rowIndex]->content_.data());
            auto entities = contentVoicePtr->caption_->entities_;
            return makeRichText(QString::fromStdString(contentVoicePtr->caption_->text_), entities);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageAudio::ID) {
            auto contentAudioPtr = static_cast<messageAudio *>
                                   (m_messages[rowIndex]->content_.data());
            auto entities = contentAudioPtr->caption_->entities_;
            return makeRichText(QString::fromStdString(contentAudioPtr->caption_->text_), entities);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageVideo::ID) {
            auto contentVideoPtr = static_cast<messageVideo *>
                                   (m_messages[rowIndex]->content_.data());
            auto entities = contentVideoPtr->caption_->entities_;
            return makeRichText(QString::fromStdString(contentVideoPtr->caption_->text_), entities);
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
    case MESSAGE_TYPE: {
        if (m_messages[rowIndex]->chat_id_ == 0)
            return SYSTEM_NEW_MESSAGE;
        if (m_messages[rowIndex]->content_->get_id() == messageText::ID)
            return TEXT;
        if (m_messages[rowIndex]->content_->get_id() == messagePhoto::ID)
            return PHOTO;
        if (m_messages[rowIndex]->content_->get_id() == messageSticker::ID)
            return STICKER;
        if (m_messages[rowIndex]->content_->get_id() == messageDocument::ID)
            return DOCUMENT;
        if (m_messages[rowIndex]->content_->get_id() == messageVoiceNote::ID)
            return VOICE;
        if (m_messages[rowIndex]->content_->get_id() == messageAudio::ID)
            return AUDIO;
        if (m_messages[rowIndex]->content_->get_id() == messageVideo::ID)
            return VIDEO;
        if (m_messages[rowIndex]->content_->get_id() == messageVideoNote::ID)
            return VIDEO_NOTE;
        if (m_messages[rowIndex]->content_->get_id() == messageAnimation::ID)
            return ANIMATION;
        if (m_messages[rowIndex]->content_->get_id() == messageContact::ID)
            return CONTACT;
        if (m_messages[rowIndex]->content_->get_id() == messageChatJoinByLink::ID)
            return JOINBYLINK;
        if (m_messages[rowIndex]->content_->get_id() == messageContactRegistered::ID)
            return CONTACT_REGISTERED;
        if (m_messages[rowIndex]->content_->get_id() == messageSupergroupChatCreate::ID)
            return CHAT_CREATED;
        if (m_messages[rowIndex]->content_->get_id() == messageBasicGroupChatCreate::ID)
            return CHAT_CREATED;
        return UNDEFINED;
        break;
    }
    case SENDING_STATE:
        if (m_messages[rowIndex]->sending_state_.data()) {
            if (m_messages[rowIndex]->sending_state_->get_id() == messageSendingStatePending::ID)
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Pending);
            if (m_messages[rowIndex]->sending_state_->get_id() == messageSendingStateFailed::ID)
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Failed);
        }
        if (m_messages[rowIndex]->is_outgoing_) {
            if (m_messages[rowIndex]->id_ <= lastOutboxId())
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Read);
            else
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Not_Read);
        } else {
            if (m_messages[rowIndex]->id_ <= lastMessage().toLongLong())
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Read);
            else
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Not_Read);
        }
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

    case REPLY_MARKUP:
        if (m_messages[rowIndex]->reply_markup_.data()) {
            if (m_messages[rowIndex]->reply_markup_->get_id() == replyMarkupInlineKeyboard::ID) {
                auto replyMarkupPtr = static_cast<replyMarkupInlineKeyboard *>(m_messages[rowIndex]->reply_markup_.data());
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
        auto messageDateTime = QDateTime::fromTime_t(m_messages[rowIndex]->date_);
        auto messageDate = messageDateTime.date();
        auto DateTimestamp = QDateTime::fromString(messageDate.toString(Qt::ISODate), Qt::ISODate);
        return DateTimestamp.toTime_t();
    }
    case RICH_TEXT:
        if (m_messages[rowIndex]->content_.data() != nullptr) {
            if (m_messages[rowIndex]->content_->get_id() == messageText::ID) {
                auto contentPtr = static_cast<messageText *>
                                  (m_messages[rowIndex]->content_.data());
                if (contentPtr->text_.data() != nullptr) {
                    auto t = contentPtr->text_->entities_;
                    return makeRichText(QString::fromStdString(contentPtr->text_->text_), t);
                }
            }
        }
        return QVariant();
    //        VIEWS,
    default:
        break;
    }

    return QVariant();
}

int MessagingModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_messages.size() + 1;
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
    roles[REPLY_MARKUP] = "reply_markup";
    roles[MESSAGE_TYPE] = "message_type";
    roles[SECTION] = "section";
    roles[WAVEFORM] = "waveform";
    roles[RICH_TEXT] = "rich_text";

    return roles;
}
void MessagingModel::fetchOlder()
{
    if (m_messages.size() > 0 && canFetchOlder()) {
        setFetching(true);
        tdlibJson->getChatHistory(peerId().toLongLong(), m_messages.first()->id_, 0,
                                  MESSAGE_LIMIT, false, "prepend");
    }
}

void MessagingModel::fetchMore(const QModelIndex & /*parent*/)
{
    qint64 lastMessageId =  lastInbox().toLongLong();
    //If do not check this, and in chat no new messages, getChatHistory returns 1 message. UI issue.
    if ((qint64)lastOutboxId() == lastMessage().toLongLong())
        lastMessageId = (qint64)lastOutboxId();

    if (!fetching()) {
        setFetching(true);
        if (rowCount(QModelIndex()) == 1) {
            tdlibJson->getChatHistory(peerId().toLongLong(), lastMessageId, -10,
                                      MESSAGE_LIMIT, false);
        } else {
            tdlibJson->getChatHistory(peerId().toLongLong(), m_messages.last()->id_, MESSAGE_LIMIT * -1 + 1, MESSAGE_LIMIT,
                                      false, "append");
        }
    }
}

bool MessagingModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    if (m_messages.size() > 0)
        return !m_fetching && !(lastMessage().toLongLong() == m_messages.last()->id_);
    else
        return !m_fetching;
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
    userStatusTimer.start();
    updateStatus();
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
        emit dataChanged(index(1), index(m_messages.size()), stateRole);
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
        emit dataChanged(index(1), index(m_messages.size()), stateRole);
    }
}

void MessagingModel::addMessages(const QJsonObject &messagesObject)
{
    int totalCount = messagesObject["total_count"].toInt();
    QString extra = messagesObject["@extra"].toString("");

    QVariantList messagesIds;

    QJsonArray messagesArray = messagesObject["messages"].toArray();
    if (ParseObject::getInt64(messagesArray[0].toObject()["chat_id"]) == peerId().toDouble()) {
        qDebug() << "add extra:" << extra << "total Count" << totalCount;
        QVector<qint64> messageReplyIds;
        if (extra == "prepend" && totalCount == 0)
            setReachedHistoryEnd(true);

        //Oldest
        if (extra == "prepend") {
            beginInsertRows(QModelIndex(), 0, totalCount - 1);
            for (int i = 0; i < messagesArray.size(); i++) {

                qint64 reply_id = ParseObject::getInt64(messagesArray[i].toObject()["reply_to_message_id"]);
                if (reply_id != 0)
                    messageReplyIds.append(reply_id);

                prependMessage(messagesArray[i].toObject());
                messagesIds.append(messagesArray[i].toObject()["id"].toVariant());
            }
            endInsertRows();
            //Notifying view to update previous last item. fetchOlder issue
            m_indexToUpdate = totalCount;

            QTimer::singleShot(500, this, [this]() {
                emit dataChanged(index(m_indexToUpdate), index(m_indexToUpdate), QVector<int>());
            });

        } else if (extra == "append") {
            //Newest
            int totalGoodMessages = 0;


            for (int r_i = messagesArray.size() - 1; r_i >= 0; r_i--) {
                auto obj = messagesArray[r_i];
                if (ParseObject::getInt64(obj.toObject()["id"]) > m_messages.last()->id_) {
                    totalGoodMessages++;
                    messagesIds.append(obj.toObject()["id"].toVariant());
                }
            }
            if (totalGoodMessages == 0)
                return;
            beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()) + totalGoodMessages - 1);
            for (int r_i = messagesArray.size() - 1; r_i >= 0; r_i--) {
                auto obj = messagesArray[r_i];
                qint64 reply_id = ParseObject::getInt64(obj.toObject()["reply_to_message_id"]);

                if (reply_id != 0)
                    messageReplyIds.append(reply_id);

                if (ParseObject::getInt64(obj.toObject()["id"]) > m_messages.last()->id_) {
                    appendMessage(obj.toObject());
                }
            }
            endInsertRows();
        } else if (extra == "getReplies") {
            addRepliedMessage(messagesObject);
        } else if (extra == "forwardMessagesExtra") {

        } else {
            int indexToAppend = -1;
            int objTime = -1;

            //On forward returns updateNewMessage and messages. Workaround
            beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()) + totalCount - 1);
            for (int i = messagesArray.size() - 1; i >= 0; i--) {
                auto obj = messagesArray[i];
                qint64 reply_id = ParseObject::getInt64(obj.toObject()["reply_to_message_id"]);
                if (reply_id != 0)
                    messageReplyIds.append(reply_id);
                appendMessage(obj.toObject());
                messagesIds.append(obj.toObject()["id"].toVariant());
            }
            endInsertRows();

            //            fetchOlder();

            if (messageReplyIds.size() > 0)
                tdlibJson->getMessages(peerId().toLongLong(), messageReplyIds, "getReplies");

            if (lastInbox() != lastMessage())
                for (int i = m_messages.size() - 1; i != -1; i--) {
                    if (lastInbox().toLongLong() == m_messages[i]->id_) {
                        indexToAppend = i;
                        objTime = m_messages[i]->date_;
                        break;
                    }
                }

            if (indexToAppend == -1) {
                setLastMessageIndex(m_messages.size() - 1);
            } else {
                indexToAppend++;
                setLastMessageIndex(indexToAppend);

                beginInsertRows(QModelIndex(), indexToAppend, indexToAppend);
                qint64 messageId = m_messages[indexToAppend - 1]->id_;
                const QByteArray messageSeparator =
                    " {         \"@type\": \"message\",         \"author_signature\": \"\",         \"can_be_deleted_for_all_users\": false,         \"can_be_deleted_only_for_self\": false,         \"can_be_edited\": false,         \"can_be_forwarded\": false,         \"chat_id\": 0,         \"contains_unread_mention\": false,         \"content\": {             \"@type\": \"messageText\",             \"text\": {                 \"@type\": \"formattedText\",                 \"entities\": [                 ],                 \"text\": \"new message separator\"             }         },         \"date\": " + QString::number(objTime).toLatin1() + ",         \"edit_date\": 0,         \"id\": " + QString::number(messageId).toLatin1() + ",         \"is_channel_post\": false,         \"is_outgoing\": false,         \"media_album_id\": \"0\",         \"reply_to_message_id\": 0,         \"sender_user_id\": 0,         \"ttl\": 0,         \"ttl_expires_in\": 0,         \"via_bot_user_id\": 0,         \"views\": 0     } ";

                auto messageItem = ParseObject::parseMessage(QJsonDocument::fromJson(messageSeparator).object());

                m_messages.insert(indexToAppend, messageItem);
                endInsertRows();
            }

        }

        if (messagesIds.size() > 0)
            viewMessages(messagesIds);

        if (messageReplyIds.size() > 0)
            tdlibJson->getMessages(peerId().toLongLong(), messageReplyIds, "getReplies");


        setFetching(false);
    }
}

void MessagingModel::appendMessage(const QJsonObject &messageObject)
{
    auto messageItem = ParseObject::parseMessage(messageObject);
    if (messageObject.contains("@extra")) {
        if (messageObject["@extra"].toString() == "editText") {
            //skip from edit
            return;
        }
        if (messageObject["@extra"].toString() == "editCaption") {
            //skip from edit
            return;
        } else if (messageObject["@extra"].toString() != "") {
            //do not rembeber why...
            replyMessagesMap[messageItem->id_] = messageItem;
            return;
        }
    }
    if (peerId().toLongLong() != messageItem->chat_id_)
        return;
    bool is_replaced = false;
    if (messageItem->sending_state_.data())
        if (messageItem->sending_state_->get_id() == messageSendingStatePending::ID) {
            for (int i = 0 ; i < m_messages.size(); i++)
                if (m_messages[i]->id_ == messageItem->id_) {
                    m_messages.replace(i, messageItem);
                    emit dataChanged(index(i + 1), index(i  + 1));
                    is_replaced = true;
                    break;
                }
        }
    if (!is_replaced) {
        qint64 reply_id = messageItem->reply_to_message_id_;

        if (reply_id != 0) {
            QVector<qint64> message_ids;
            message_ids << reply_id;
            tdlibJson->getMessages(peerId().toLongLong(), message_ids, "getReplies");
        }
        m_messages.append(messageItem);


    }

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
            messagePhotoQueue[fileId] = m_messages.size() - 1;
    }
    emit firstIdChanged();

}

QVariant MessagingModel::dataContent(const int rowIndex) const
{
    if (m_messages[rowIndex]->content_.data() != nullptr) {
        if (m_messages[rowIndex]->content_->get_id() == messageText::ID) {
            auto contentPtr = static_cast<messageText *>
                              (m_messages[rowIndex]->content_.data());
            if (contentPtr->text_.data() != nullptr)
                return QString::fromStdString(contentPtr->text_->text_);
        }
        //Returns local filepath to View for QImageProvider
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
        if (m_messages[rowIndex]->content_->get_id() == messageSupergroupChatCreate::ID) {
            auto createdPtr = static_cast<messageSupergroupChatCreate *>
                              (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(createdPtr->title_);
        }
        if (m_messages[rowIndex]->content_->get_id() == messageBasicGroupChatCreate::ID) {
            auto createdPtr = static_cast<messageBasicGroupChatCreate *>
                              (m_messages[rowIndex]->content_.data());
            return QString::fromStdString(createdPtr->title_);
        }

        if (m_messages[rowIndex]->content_->get_id() == messageUnsupported::ID)
            return "Unsupported message type";
    }
    return QVariant();
}

QVariant MessagingModel::dataFileMeta(const int rowIndex, int role) const
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

QSharedPointer<message> MessagingModel::findMessageById(const qint64 messageId) const
{
    QSharedPointer<message> result = QSharedPointer<message>(nullptr);
    for (int i = 0; i < m_messages.size(); i++) {
        if (m_messages[i]->id_ == messageId) {
            result = m_messages[i];
            break;
        }
    }

    return result;
}

int MessagingModel::findIndexById(const qint64 messageId) const
{
    int result = -1;
    for (int i = 0; i < m_messages.size(); i++) {
        if (m_messages[i]->id_ == messageId) {
            result = i;
            break;
        }
    }

    return result;
}

void MessagingModel::addRepliedMessage(const QJsonObject &messageObject)
{
    QJsonArray messagesArray = messageObject["messages"].toArray();
    for (int i = 0; i < messagesArray.size(); i++) {
        auto obj = messagesArray[i].toObject();
        qint64 reply_message_id = ParseObject::getInt64(obj["id"]);
        replyMessagesMap[reply_message_id] = ParseObject::parseMessage(obj);
    }
    QVector<int> roles;
    roles.append(REPLY_AUTHOR);
    roles.append(REPLY_MESSAGE);
    emit dataChanged(index(1), index(m_messages.size()), roles);
}


bool MessagingModel::canFetchOlder()
{
    return !reachedHistoryEnd();
}

QString MessagingModel::makeRichText(const QString &data, const std::vector<QSharedPointer<textEntity> > &markup) const
{
    if (markup.size() == 0)
        return data;

    QList<QPair<int, int>> positions;

    for (int i = 0; i < markup.size(); ++i)
        positions.append(QPair<int, int>(markup[i]->offset_, markup[i]->length_));

    QStringList textParts;

    for (int i = 0; i < positions.size(); ++i) {
        auto pair = positions[i];
        textParts.append(data.mid(pair.first, pair.second));
    }

    for (int i = 0; i < markup.size(); ++i) {
        switch (markup[i]->type_->get_id()) {
        case textEntityTypeItalic::ID:
            textParts[i] = textParts[i].prepend("<i>");
            textParts[i] = textParts[i].append("</i>");
            break;
        case textEntityTypeBold::ID:
            textParts[i] = textParts[i].prepend("<b>");
            textParts[i] = textParts[i].append("</b>");
            break;
        case textEntityTypeEmailAddress::ID:
            textParts[i] = textParts[i].prepend("<a href=\"mailto:" + textParts[i] + "\">");
            textParts[i] = textParts[i].append("</a>");
            break;
        case textEntityTypeHashtag::ID:
            textParts[i] = textParts[i].prepend("<a href=\"hashtag/" + textParts[i] + "\">");
            textParts[i] = textParts[i].append("</a>");
            break;
        case textEntityTypeMention::ID:
            textParts[i] = textParts[i].prepend("<a href=\"user/" + textParts[i] + "\">");
            textParts[i] = textParts[i].append("</a>");
            break;
        case textEntityTypePhoneNumber::ID: {
            QString phone_trimmed = textParts[i];
            textParts[i] = textParts[i].prepend("<a href=\"tel:" + phone_trimmed.remove(QRegExp("[- )(]")) + "\">");
            textParts[i] = textParts[i].append("</a>");
            break;
        }
        case textEntityTypeUrl::ID: {
            if (textParts[i].left(4) == "http")
                textParts[i] = textParts[i].prepend("<a href=\"" + textParts[i] + "\">");
            else
                textParts[i] = textParts[i].prepend("<a href=\"" + QUrl::fromUserInput(textParts[i]).toString() + "\">");
            textParts[i] = textParts[i].append("</a>");
            break;
        }
        case textEntityTypeMentionName::ID: {
            auto tmp = static_cast<textEntityTypeMentionName *>(markup[i]->type_.data());
            textParts[i] = textParts[i].prepend(QString("<a href=\"id_user/%1\">").arg(QString::number(tmp->user_id_)));
            textParts[i] = textParts[i].append("</a>");
            break;
        }
        case textEntityTypeBotCommand::ID:
            textParts[i] = textParts[i].prepend("<a href=\"bot_command/" + textParts[i] + "\">");
            textParts[i] = textParts[i].append("</a>");
            break;
        case textEntityTypeTextUrl::ID: {
            auto tmp = static_cast<textEntityTypeTextUrl *>(markup[i]->type_.data());
            textParts[i] = textParts[i].prepend(QString("<a href=\"%1\">").arg(QString::fromStdString(tmp->url_)));
            textParts[i] = textParts[i].append("</a>");
            break;
        }
        break;
        case textEntityTypeCashtag::ID:
        case textEntityTypeCode::ID:
        case textEntityTypePre::ID:
        case textEntityTypePreCode::ID:
            break;
        default:
            break;
        }
    }

    int bias = 0;
    QString result = data;
    for (int i = 0; i < textParts.size(); ++i) {
        result = result.replace(positions[i].first + bias, positions[i].second, textParts[i]);
        bias += textParts[i].size() - positions[i].second;
    }
    return result;
}

void MessagingModel::prependMessage(const QJsonObject &messageObject)
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
            messagePhotoQueue[fileId] = 0;

    }
    if (messagePhotoQueue.keys().size() > 0) {
        for (int key : messagePhotoQueue.keys())
            messagePhotoQueue[key]++;
    }
}

void MessagingModel::addMessageFromUpdate(const QJsonObject &messageUpdateObject)
{
    if (peerId() != messageUpdateObject["message"].toObject()["chat_id"].toVariant().toString())
        return;
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));
    appendMessage(messageUpdateObject["message"].toObject());
    endInsertRows();
    setLastMessage(QString::number(m_messages.last()->id_));
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
        if (m_messages[messagePhotoQueue[file->id_]]->content_->get_id() == messagePhoto::ID) {
            auto messagePhotoPtr = static_cast<messagePhoto *>
                                   (m_messages[messagePhotoQueue[file->id_]]->content_.data());
            for (quint32 i = 0 ; i < messagePhotoPtr->photo_->sizes_.size(); i++) {
                if (messagePhotoPtr->photo_->sizes_[i]->photo_->id_ == file->id_) {
                    messagePhotoPtr->photo_->sizes_[i]->photo_ = file;
                    break;
                }
            }
        }
        if (m_messages[messagePhotoQueue[file->id_] ]->content_->get_id() == messageVideo::ID) {
            auto contentVideoPtr = static_cast<messageVideo *>
                                   (m_messages[messagePhotoQueue[file->id_]]->content_.data());
            if (contentVideoPtr->video_->video_->id_ == file->id_)
                contentVideoPtr->video_->video_ = file;
            else if (contentVideoPtr->video_->thumbnail_->photo_->id_ == file->id_)
                contentVideoPtr->video_->thumbnail_->photo_ = file;

        }
        if (m_messages[messagePhotoQueue[file->id_] ]->content_->get_id() == messageVideoNote::ID) {
            auto contentVideoNotePtr = static_cast<messageVideoNote *>
                                       (m_messages[messagePhotoQueue[file->id_]]->content_.data());
            if (contentVideoNotePtr->video_note_->video_->id_ == file->id_)
                contentVideoNotePtr->video_note_->video_ = file;
            else if (contentVideoNotePtr->video_note_->thumbnail_->photo_->id_ == file->id_)
                contentVideoNotePtr->video_note_->thumbnail_->photo_ = file;

        }
        if (m_messages[messagePhotoQueue[file->id_]]->content_->get_id() == messageSticker::ID) {
            auto messageStickerPtr = static_cast<messageSticker *>
                                     (m_messages[messagePhotoQueue[file->id_]]->content_.data());
            if (messageStickerPtr->sticker_->sticker_->id_ == file->id_)
                messageStickerPtr->sticker_->sticker_ = file;
        }
        if (m_messages[messagePhotoQueue[file->id_]]->content_->get_id() == messageDocument::ID) {
            auto messageDocumentPtr = static_cast<messageDocument *>
                                      (m_messages[messagePhotoQueue[file->id_]]->content_.data());
            if (messageDocumentPtr->document_->document_->id_ == file->id_)
                messageDocumentPtr->document_->document_ = file;
        }
        if (m_messages[messagePhotoQueue[file->id_]]->content_->get_id() == messageVoiceNote::ID) {
            auto messageVoiceNotePtr = static_cast<messageVoiceNote *>
                                       (m_messages[messagePhotoQueue[file->id_]]->content_.data());
            if (messageVoiceNotePtr->voice_note_->voice_->id_ == file->id_)
                messageVoiceNotePtr->voice_note_->voice_ = file;
        }
        if (m_messages[messagePhotoQueue[file->id_]]->content_->get_id() == messageAudio::ID) {
            auto messageAudioPtr = static_cast<messageAudio *>
                                   (m_messages[messagePhotoQueue[file->id_]]->content_.data());
            if (messageAudioPtr->audio_->audio_->id_ == file->id_)
                messageAudioPtr->audio_->audio_ = file;
        }
        if (m_messages[messagePhotoQueue[file->id_]]->content_->get_id() == messageAnimation::ID) {
            auto  messageAnimationPtr = static_cast<messageAnimation *>
                                        (m_messages[messagePhotoQueue[file->id_]]->content_.data());
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
        emit dataChanged(index(messagePhotoQueue[file->id_] + 1),
                         index(messagePhotoQueue[file->id_] + 1), photoRole);
        if (file->local_->is_downloading_completed_ && file->remote_->is_uploading_completed_)
            messagePhotoQueue.remove(file->id_);

    }
    if (avatarPhotoQueue.keys().contains(file->id_)) {
        if (file->local_->is_downloading_completed_) {
            UsersModel::instance()->setSmallAvatar(m_messages[avatarPhotoQueue[file->id_].at(0)]->sender_user_id_,
                                                   file);
            QVector<int> avatarRole;
            avatarRole.append(SENDER_PHOTO);
            for (int itr : avatarPhotoQueue[file->id_])
                emit dataChanged(index(itr + 1),
                                 index(itr + 1), avatarRole);
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
        userStatusTimer.stop();
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
    updateStatus();
    if (m_messages.size() > 0)
        emit firstIdChanged();
    emit peerIdChanged(peerId);
}

void MessagingModel::sendForwardMessages(const QString &chat_id, const QString &from_chat_id, const QVariantList message_ids)
{
    sendForwardMessages(chat_id.toLongLong(), from_chat_id.toLongLong(), message_ids, false, false, false);
}

void MessagingModel::sendForwardMessages(const qint64 chat_id, const qint64 from_chat_id, const QVariantList message_ids, const bool disable_notification, const bool from_background, const bool as_album)
{
    QVector<qint64> ids;
    for (QVariant item : message_ids)
        ids.append(item.toString().toLongLong());

    tdlibJson->forwardMessage(chat_id, from_chat_id, ids, disable_notification, from_background, as_album);
}

void MessagingModel::sendEditCaptionMessage(const QString &message_id, const QString &caption)
{
    TlStorerToString json;
    editMessageCaption editMessageObject;
    editMessageObject.chat_id_ = m_peerId.toLongLong();
    editMessageObject.message_id_ = message_id.toLongLong();
    editMessageObject.caption_ = QSharedPointer<formattedText>(new formattedText);
    formattedText *ptr = static_cast<formattedText *>
                         (editMessageObject.caption_.data());
    ptr->text_ = caption.toStdString();
    editMessageObject.store(json, "input_message_content");
    QVariantMap originalObject = json.doc["input_message_content"].toMap();
    originalObject["@extra"] = "editCaption";
    originalObject.remove("reply_markup");
    auto jsonObject = QJsonDocument::fromVariant(originalObject);
    tdlibJson->sendMessage(jsonObject.toJson());
}

void MessagingModel::sendEditTextMessage(const QString &message_id, const QString &text)
{
    TlStorerToString json;
    editMessageText editMessageObject;
    editMessageObject.chat_id_ = m_peerId.toLongLong();
    editMessageObject.message_id_ = message_id.toLongLong();
    editMessageObject.input_message_content_ = QSharedPointer<inputMessageText>(new inputMessageText);
    inputMessageText *ptr = static_cast<inputMessageText *>
                            (editMessageObject.input_message_content_.data());
    ptr->clear_draft_ = true;
    ptr->disable_web_page_preview_ = false;
    ptr->text_ = QSharedPointer<formattedText>(new formattedText);
    ptr->text_->text_ = text.toStdString();

    editMessageObject.store(json, "input_message_content");
    QVariantMap originalObject = json.doc["input_message_content"].toMap();
    originalObject.remove("reply_markup");
    originalObject["@extra"] = "editText";

    auto jsonObject = QJsonDocument::fromVariant(originalObject);
    tdlibJson->sendMessage(jsonObject.toJson());
}

void MessagingModel::sendTextMessage(const QString &text,
                                     const QString &reply_id)
{
    QByteArray formattedTextEntities = tdlibJson->sendSyncroniousMessage(QString("{\"@type\":\"parseTextEntities\","
                                       "\"text\":\"%1\","
                                       "\"parse_mode\":"
                                       "{\"@type\":\"textParseModeMarkdown\"}}").arg(QString(text).replace(QChar('"'), "\\\"")));
    qDebug() << formattedTextEntities;
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
    ptr->text_ = ParseObject::parseFormattedTextContent(QJsonDocument::fromJson(formattedTextEntities).object());
    if (reply_id != "0" && reply_id != "-1" && !replyMessagesMap.contains(reply_id.toLongLong())) {
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
    TlStorerToString json;
    sendMessage sendMessageObject;
    sendMessageObject.chat_id_ = m_peerId.toLongLong();
    sendMessageObject.disable_notification_ = false;
    sendMessageObject.from_background_ = false;
    sendMessageObject.reply_to_message_id_ = reply_id.toLongLong();
    sendMessageObject.input_message_content_ = QSharedPointer<inputMessagePhoto>(new inputMessagePhoto);
    inputMessagePhoto *ptr = static_cast<inputMessagePhoto *>
                             (sendMessageObject.input_message_content_.data());
    auto photoPtr = QSharedPointer<inputFileGenerated>(new inputFileGenerated);
    photoPtr->original_path_ = filepath.toStdString();
    photoPtr->conversion_ = "copy";
    photoPtr->expected_size_ = QFileInfo(filepath).size();
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
    TlStorerToString json;
    sendMessage sendMessageObject;
    sendMessageObject.chat_id_ = m_peerId.toLongLong();
    sendMessageObject.disable_notification_ = false;
    sendMessageObject.from_background_ = false;
    sendMessageObject.reply_to_message_id_ = reply_id.toLongLong();
    sendMessageObject.input_message_content_ = QSharedPointer<inputMessageDocument>
            (new inputMessageDocument);
    inputMessageDocument *ptr = static_cast<inputMessageDocument *>
                                (sendMessageObject.input_message_content_.data());
    auto docPtr = QSharedPointer<inputFileGenerated>(new inputFileGenerated);
    docPtr->original_path_ = filepath.toStdString();
    docPtr->conversion_ = "copy";
    docPtr->expected_size_ = QFileInfo(filepath).size();
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
    TlStorerToString json;
    sendMessage sendMessageObject;
    sendMessageObject.chat_id_ = m_peerId.toLongLong();
    sendMessageObject.disable_notification_ = false;
    sendMessageObject.from_background_ = false;
    sendMessageObject.reply_to_message_id_ = reply_id.toLongLong();
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

void MessagingModel::sendVoiceMessage(const QString &filepath, const int secDuration,
                                      const QString &reply_id, const QString &caption,
                                      const QString &waveform)
{
    TlStorerToString json;
    sendMessage sendMessageObject;
    sendMessageObject.chat_id_ = m_peerId.toLongLong();
    sendMessageObject.disable_notification_ = false;
    sendMessageObject.from_background_ = false;
    sendMessageObject.reply_to_message_id_ = reply_id.toLongLong();
    sendMessageObject.input_message_content_ = QSharedPointer<inputMessageVoiceNote>
            (new inputMessageVoiceNote);
    inputMessageVoiceNote *ptr = static_cast<inputMessageVoiceNote *>
                                 (sendMessageObject.input_message_content_.data());
    auto docPtr = QSharedPointer<inputFileGenerated>(new inputFileGenerated);
    docPtr->original_path_ = filepath.toStdString();
    docPtr->conversion_ = "copy";
    docPtr->expected_size_ = QFileInfo(filepath).size();
    ptr->voice_note_ = docPtr;
    ptr->duration_ = secDuration;
    ptr->caption_ = QSharedPointer<formattedText>(new formattedText);
    ptr->caption_->text_ = caption.toStdString();
    ptr->waveform_ =  waveform.toLatin1().toBase64().toStdString();

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
    int messageIndex = rowIndex - 1;
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

void MessagingModel::cancelDownload(const int rowIndex)
{
    int fileId = -1;
    int messageIndex = rowIndex - 1;
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
    tdlibJson->cancelDownloadFile(fileId);
}

void MessagingModel::cancelUpload(const int rowIndex)
{
    int fileId = -1;
    int messageIndex = rowIndex - 1;

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
    tdlibJson->cancelUploadFile(fileId);
}

void MessagingModel::deleteMessage(const int rowIndex, const bool revoke)
{
    int messageIndex = rowIndex - 1;
    if (messageIndex >= 0   && messageIndex < m_messages.size()) {
        qint64 chatId = m_messages[messageIndex]->chat_id_;
        QVector<qint64> messageIds;
        messageIds.append(m_messages[messageIndex]->id_);

        tdlibJson->deleteMessages(chatId, messageIds, revoke);

        //1. if exists in fileUpdates (messageIndex == fileIndex) -> remove
        //2. if messageIndex > fileIndex -> nothing
        //3. if messageIndex < fileIndex -> decrease by 1
        for (int key : messagePhotoQueue.keys()) {
            if (messageIndex < messagePhotoQueue[key]) {
                messagePhotoQueue[key]--;
                break;
            }
            if (messageIndex == messagePhotoQueue[key]) {
                messagePhotoQueue.remove(key);
            }
        }
        beginRemoveRows(QModelIndex(), rowIndex, rowIndex);
        m_messages.removeAt(messageIndex);
        endRemoveRows();

    }
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
    for (int i = 0; i < m_messages.size(); i++) {
        if (m_messages[i]->id_ == messageId) {
            m_messages.replace(i, messageItem);
            emit dataChanged(index(i + 1), index(i + 1));
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
    for (int i = 0 ; i < m_messages.size(); i++) {
        if (m_messages[i]->id_ == messageId) {
            m_messages[i]->content_ = newContent;
            QVector<int> roles;
            roles.append(CONTENT);
            roles.append(FILE_CAPTION);
            roles.append(RICH_TEXT);
            emit dataChanged(index(i + 1), index(i + 1), roles);
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
    for (int i = 0 ; i < m_messages.size(); i++) {
        if (m_messages[i]->id_ == messageId) {
            m_messages[i]->edit_date_ = editDate;
            m_messages[i]->reply_markup_ = replyMarkup;
            QVector<int> roles;
            roles.append(EDIT_DATE);
            roles.append(REPLY_MARKUP);
            emit dataChanged(index(i + 1), index(i + 1), roles);
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
        for (int i = 0; i < m_messages.size(); i++) {
            if (m_messages[i]->id_ == id) {
                beginRemoveRows(QModelIndex(), i, i);
                m_messages.removeAt(i);
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

void MessagingModel::updateStatus()
{
    auto chatType = static_cast<tdlibQt::Enums::ChatType>(m_chatType["type"].toInt());
    if (chatType == tdlibQt::Enums::ChatType::Private ||
            chatType == tdlibQt::Enums::ChatType::Secret) {
        auto userStatus = UsersModel::instance()->getUserStatus(m_peerId.toInt());
        setAction(UsersModel::getUserStatusAsString(userStatus));
    } else
        setAction("");

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

void MessagingModel::loadAndRefreshRepliedByIndex(const int messageIndex)
{
    loadAndRefreshByMessageId(m_messages[messageIndex]->reply_to_message_id_);
}

void MessagingModel::loadAndRefreshByMessageId(const QVariant messageId)
{
    beginResetModel();
    m_messages.clear();
    setFetching(true);
    tdlibJson->getChatHistory(peerId().toLongLong(), messageId.toLongLong(), -10,
                              MESSAGE_LIMIT, false);
    endResetModel();
}

int MessagingModel::findIndexById(const QString &messageId) const
{
    return findIndexById(messageId.toLongLong());
}

}//namespace tdlibQt

