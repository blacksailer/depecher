#include "ChatsModel.hpp"
#include <QDebug>
#include <memory.h>
#include "../ParseObject.hpp"
#include "../TdlibJsonWrapper.hpp"
#include "tdlibQt/include/TdlibNamespace.hpp"
namespace tdlibQt {
ChatsModel::ChatsModel(QObject *parent) : QAbstractListModel(parent),
    tdlibJson(TdlibJsonWrapper::instance())
{
    connect(this, &ChatsModel::totalUnreadCountChanged,
            tdlibJson, &TdlibJsonWrapper::setTotalUnreadCount);

    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::newChatGenerated,
            this, &tdlibQt::ChatsModel::addChat);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateFile,
            this, &tdlibQt::ChatsModel::updateChatPhoto);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateChatOrder,
            this, &tdlibQt::ChatsModel::updateChatOrder);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateChatLastMessage,
            this, &tdlibQt::ChatsModel::updateChatLastMessage);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateChatReadInbox,
            this, &tdlibQt::ChatsModel::updateChatReadInbox);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateChatReadOutbox,
            this, &tdlibQt::ChatsModel::updateChatReadOutbox);

    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateUserChatAction,
            this, &tdlibQt::ChatsModel::updateChatAction);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateChatMention,
            this, &tdlibQt::ChatsModel::updateChatMentionCount);
    connect(tdlibJson, &tdlibQt::TdlibJsonWrapper::updateMentionRead,
            this, &tdlibQt::ChatsModel::updateMentionRead);
    connect(&chatActionTimer, &QTimer::timeout, this, &tdlibQt::ChatsModel::chatActionCleanUp);
    chatActionTimer.setInterval(5 * 1000);
}
void ChatsModel::changeChatOrder(qint64 chatId, qint64 order)
{
    for (int i = 0; i < chats.size(); i++) {
        if (chats[i]->id_ == chatId) {
            chats[i]->order_ = order;
            sortByOrder();
            emit dataChanged(index(0), index(rowCount(QModelIndex()) - 1));
            break;
        }
    }
}

//Sorts by descending order field
void ChatsModel::sortByOrder()
{
    std::sort(chats.begin(), chats.end(),
              [](const QSharedPointer<chat> a, const QSharedPointer<chat> b) -> bool
    { return a->order_ > b->order_; });

}

void ChatsModel::updateChatMentionCount(const QJsonObject &chatMentionCountObject)
{
    auto chatMentionCount = QSharedPointer<updateChatUnreadMentionCount>(new
                            updateChatUnreadMentionCount);
    chatMentionCount->chat_id_ = ParseObject::getInt64(chatMentionCountObject["chat_id"]);
    chatMentionCount->unread_mention_count_ = chatMentionCountObject["unread_mention_count"].toInt();

    for (int i = 0; i < chats.size(); i++) {
        if (chats[i]->id_ == chatMentionCount->chat_id_) {
            chats[i]->unread_mention_count_ = chatMentionCount->unread_mention_count_;
            QVector<int> mentionRole;
            mentionRole.append(UNREAD_MENTION_COUNT);
            emit dataChanged(index(i), index(i), mentionRole);
            emit totalUnreadCountChanged(totalUnreadCount());
            break;
        }
    }
}

void ChatsModel::updateMentionRead(const QJsonObject &messageMentionReadObject)
{
    qint64 chat_id = ParseObject::getInt64(messageMentionReadObject["chat_id"]);
    int unread_mention = messageMentionReadObject["unread_mention_count"].toInt();
    for (int i = 0; i < chats.size(); i++) {
        if (chats[i]->id_ == chat_id) {
            chats[i]->unread_mention_count_ = unread_mention;
            QVector<int> mentionRole;
            mentionRole.append(UNREAD_MENTION_COUNT);
            emit dataChanged(index(i), index(i), mentionRole);
            emit totalUnreadCountChanged(totalUnreadCount());
            break;
        }
    }

}

int ChatsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return chats.size();
}

QVariant ChatsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    int rowIndex = index.row();

    switch (role) {
    case ID: //int64
        return QString::number(chats[rowIndex]->id_);
    case LAST_MESSAGE_ID: //int64
        return QString::number(chats[rowIndex]->last_message_->id_);
    case LAST_MESSAGE_INBOX_ID: //int64
        return QString::number(chats[rowIndex]->last_read_inbox_message_id_);
    case LAST_MESSAGE_OUTBOX_ID: //int64
        return QString::number(chats[rowIndex]->last_read_outbox_message_id_);

    case IS_PINNED:
        return chats[rowIndex]->is_pinned_;
    case TYPE:
        switch (chats[rowIndex]->type_->get_id()) {
        case chatTypeBasicGroup::ID: {
            QVariantMap resultType;
            resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::BasicGroup);
            return resultType;
        }
        case chatTypePrivate::ID: {
            QVariantMap resultType;
            resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Private);
            return resultType;
        }
        case chatTypeSecret::ID: {
            QVariantMap resultType;
            resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Secret);
            return resultType;
        }
        case chatTypeSupergroup::ID: {
            chatTypeSupergroup *superGroupMetaInfo   = static_cast<chatTypeSupergroup *>
                    (chats[rowIndex]->type_.data());
            QVariantMap resultType;
            resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Supergroup);
            resultType["is_channel"] = superGroupMetaInfo->is_channel_;
            resultType["supergroup_id"] = superGroupMetaInfo->supergroup_id_;
            return resultType;
        }
        }
    case TITLE:
        return QString::fromStdString(chats[rowIndex]->title_);
    case UNREAD_COUNT:
        return chats[rowIndex]->unread_count_;
    case UNREAD_MENTION_COUNT:
        return chats[rowIndex]->unread_mention_count_;
    case CHAT_ACTION:
        if (chatActionMap.contains(chats[rowIndex]->id_)) {
            if (chatActionMap.count(chats[rowIndex]->id_) > 1)
                return  QString::number(chatActionMap.count(chats[rowIndex]->id_)) + " are typing";
            auto chatAction = chatActionMap.value(chats[rowIndex]->id_);
            return tdlibJson->parseObject->getFirstName(chatAction->user_id_) + " is typing";
        }
        return QVariant();
    case LAST_MESSAGE:
        if (chats[rowIndex]->last_message_.data() != nullptr) {
            //Return content
            if (chats[rowIndex]->last_message_->content_.data() != nullptr) {
                if (chats[rowIndex]->last_message_->content_->get_id() == messageText::ID) {
                    auto contentPtr = static_cast<messageText *>
                                      (chats[rowIndex]->last_message_->content_.data());
                    if (contentPtr->text_.data() != nullptr) {
                        return QString::fromStdString(contentPtr->text_->text_);
                    }
                }
                if (chats[rowIndex]->last_message_->content_->get_id() == messagePhoto::ID)
                    return tr("Photo");
                if (chats[rowIndex]->last_message_->content_->get_id() == messageDocument::ID)
                    return tr("Document");

                if (chats[rowIndex]->last_message_->content_->get_id() == messageSticker::ID)
                    return tr("Sticker");
                if (chats[rowIndex]->last_message_->content_->get_id() == messageAnimation::ID)
                    return tr("Animation");
                return QVariant();
            }
        }
    case LAST_MESSAGE_AUTHOR:
        return tdlibJson->parseObject->getFirstName(
                   chats[rowIndex]->last_message_->sender_user_id_);
    case DATE:
        if (chats[rowIndex]->last_message_.data() != nullptr) {
            return chats[rowIndex]->last_message_->date_;
        }
    case MUTE_FOR:
        if (chats[rowIndex]->notification_settings_.data() != nullptr) {
            return chats[rowIndex]->notification_settings_->mute_for_;
        }

    case PHOTO:
        if (chats[rowIndex]->photo_.data() != nullptr) {
            if (chats[rowIndex]->photo_->small_.data() != nullptr)
                return QString::fromStdString(chats[rowIndex]->photo_->small_->local_->path_);
        }
        return QVariant();
    case SENDING_STATE: {
        if (chats[rowIndex]->last_message_->sending_state_.data()) {
            if (chats[rowIndex]->last_message_->sending_state_->get_id() == messageSendingStatePending::ID)
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Pending);
            if (chats[rowIndex]->last_message_->sending_state_->get_id() == messageSendingStateFailed::ID)
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Failed);
        }
        if (chats[rowIndex]->last_message_->is_outgoing_) {
            if (chats[rowIndex]->last_message_->id_ <= chats[rowIndex]->last_read_outbox_message_id_)
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Read);
            else
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Not_Read);
        } else {
            if (chats[rowIndex]->last_message_->id_ <= chats[rowIndex]->last_read_inbox_message_id_)
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Read);
            else
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Not_Read);
        }

    }

    default:
        return QVariant();
    }

    return QVariant();
}

void ChatsModel::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent)
    fetchPending = true;
    if (rowCount(QModelIndex()) > 0)
        tdlibJson->getChats(chats.last()->id_, chats.last()->order_, 100);
    else
        tdlibJson->getChats();

}

QHash<int, QByteArray> ChatsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ID] = "id";
    roles[TYPE] = "type";
    roles[PHOTO] = "photo";
    roles[ORDER] = "order";
    roles[DATE] = "date";
    roles[MUTE_FOR] = "mute_for";
    roles[TITLE] = "title";
    roles[CHAT_ACTION] = "action";
    roles[LAST_MESSAGE] = "last_message";
    roles[LAST_MESSAGE_ID] = "last_message_id";

    roles[LAST_MESSAGE_AUTHOR] = "last_message_author";
    roles[LAST_MESSAGE_INBOX_ID] = "last_message_inbox_id";
    roles[LAST_MESSAGE_OUTBOX_ID] = "last_message_outbox_id";
    roles[IS_PINNED] = "is_pinned";
    roles[UNREAD_COUNT] = "unread_count";
    roles[UNREAD_MENTION_COUNT] = "unread_mention_count";
    roles[NOTIFICATION_SETTINGS] = "notification_settings";
    roles[REPLY_MARKUP_MESSAGE_ID] = "reply_markup_message_id";
    roles[DRAFT_MESSAGE] = "draft_message";
    roles[CLIENT_DATA] = "client_data";
    roles[SENDING_STATE] = "sending_state";
    return roles;
}

bool ChatsModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return !fetchPending;
}

int ChatsModel::getIndex(const qint64 chatId)
{
    for (int i = 0; i < chats.size(); i++)
        if (chats[i]->id_ == chatId)
            return i;
    return -1;
}

void ChatsModel::chatActionCleanUp()
{
    chatActionMap.clear();
    QVector<int> actionRole;
    actionRole.append(CHAT_ACTION);
    for (int i : chatActionIndices)
        emit dataChanged(index(i), index(i), actionRole);
    chatActionTimer.stop();

}

void ChatsModel::addChat(const QJsonObject &chatObject)
{
    fetchPending = false;

    QSharedPointer<chat> chatItem = ParseObject::parseChat(chatObject);
    if (chatItem->last_message_->get_id() == messagePhoto::ID) {
        auto photoItemPtr = static_cast<messagePhoto *>(chatItem->last_message_->content_.data());
        if (photoItemPtr->photo_->sizes_.size() > 0) {
            if (!photoItemPtr->photo_->sizes_[0]->photo_->local_->is_downloading_completed_) {
                tdlibJson->downloadFile(photoItemPtr->photo_->sizes_[0]->photo_->id_, 16, "messageHistory");
            }
        }
    }
    if (chatItem->last_message_->get_id() == messageAnimation::ID) {
        auto photoItemPtr = static_cast<messageAnimation *>(chatItem->last_message_->content_.data());
        if (!photoItemPtr->animation_->thumbnail_->photo_->local_->is_downloading_completed_) {
            tdlibJson->downloadFile(photoItemPtr->animation_->thumbnail_->photo_->id_, 16, "messageHistory");
        }
    }

    //    if (chatItem->notification_settings_->mute_for_ == 0)
    //        emit totalUnreadCountChanged(totalUnreadCount());

    beginInsertRows(QModelIndex(), chats.size(), chats.size());
    chats.append(chatItem);
    endInsertRows();

    //getChatPhotos
    if (chatItem->photo_.data() != nullptr) {
        if (chatItem->photo_->small_.data() != nullptr)
            if (!chatItem->photo_->small_->local_->is_downloading_completed_)
                tdlibJson->downloadFile(chatItem->photo_->small_->id_, 1, "chatPhoto");
    }
}

void ChatsModel::updateChatPhoto(const QJsonObject &chatObject)
{
    if (chatObject["@type"].toString() == "updateFile") {
        auto fileObject = chatObject["file"].toObject();
        for (int i = 0; i < chats.size(); i++) {
            if (chats[i]->photo_.data() != nullptr) {
                if (chats[i]->photo_->small_.data() != nullptr)
                    if (chats[i]->photo_->small_->id_ == fileObject["id"].toInt()) {
                        chats[i]->photo_->small_ = ParseObject::parseFile(fileObject);
                        QVector<int> photoRole;
                        photoRole.append(PHOTO);
                        emit dataChanged(this->createIndex(i, 0), this->createIndex(i, 0), photoRole);
                        break;
                    }
            }
        }
    }
}

void ChatsModel::updateChatOrder(const QJsonObject &chatOrderObject)
{
    qint64 chatId = ParseObject::getInt64(chatOrderObject["chat_id"]);
    qint64 order =  ParseObject::getInt64(chatOrderObject["order"]);
    changeChatOrder(chatId, order);
}

void ChatsModel::updateChatLastMessage(const QJsonObject &chatLastMessageObject)
{
    qint64 chatId = chatLastMessageObject["chat_id"].toVariant().toString().toLongLong();
    qint64 order =  chatLastMessageObject["order"].toString().toLongLong();
    auto lastMessage = ParseObject::parseMessage(chatLastMessageObject["last_message"].toObject());
    for (int i = 0; i < chats.size(); i++) {
        if (chats[i]->id_ == chatId) {
            chats[i]->last_message_ = lastMessage;
            break;
        }
    }
    changeChatOrder(chatId, order);
}

void ChatsModel::updateChatReadInbox(const QJsonObject &chatReadInboxObject)
{
    qint64 chatId = ParseObject::getInt64(chatReadInboxObject["chat_id"]);
    qint64 lastReadId = ParseObject::getInt64(chatReadInboxObject["last_read_inbox_message_id"]);
    int unreadCount = chatReadInboxObject["unread_count"].toInt();
    for (int i = 0 ; i < chats.size(); i++) {
        if (chats[i]->id_ == chatId) {
            chats[i]->last_read_inbox_message_id_ = lastReadId;
            chats[i]->unread_count_ = unreadCount;
            if (chats[i]->notification_settings_->mute_for_ == 0)
                emit totalUnreadCountChanged(totalUnreadCount());
            QVector<int> roles;
            roles.append(UNREAD_COUNT);
            roles.append(LAST_MESSAGE_INBOX_ID);
            roles.append(SENDING_STATE);

            emit dataChanged(index(i), index(i), roles);
            break;
        }
    }
}

void ChatsModel::updateChatReadOutbox(const QJsonObject &chatReadOutboxObject)
{
    qint64 chatId = ParseObject::getInt64(chatReadOutboxObject["chat_id"]);
    qint64 lastOutboxId = ParseObject::getInt64(chatReadOutboxObject["last_read_outbox_message_id"]);
    for (int i = 0; i < chats.size(); i++) {
        if (chats[i]->id_ == chatId) {
            chats[i]->last_read_outbox_message_id_ = lastOutboxId;
            QVector<int> roles;
            roles.append(LAST_MESSAGE_OUTBOX_ID);
            roles.append(SENDING_STATE);
            emit dataChanged(index(i), index(i), roles);
            return;
        }
    }
}

void ChatsModel::updateChatAction(const QJsonObject &chatActionObject)
{
    QSharedPointer<updateUserChatAction> chatAction = ParseObject::parseChatAction(chatActionObject);
    chatActionMap[chatAction->chat_id_] = chatAction;
    int rowIndex = 0;
    for (int i = 0; i < chats.size(); i++) {
        if (chats[i]->id_ == chatAction->chat_id_) {
            rowIndex = i;
            break;
        }
    }
    chatActionIndices.push_front(rowIndex);
    QVector<int> actionRole;
    actionRole.append(CHAT_ACTION);
    emit dataChanged(index(rowIndex), index(rowIndex), actionRole);
    if (chatActionMap.size() == 1)
        chatActionTimer.start();

}

void ChatsModel::reset()
{
    beginResetModel();
    chats.clear();
    emit totalUnreadCountChanged(totalUnreadCount());
    fetchMore(QModelIndex());
    endResetModel();
}
}//namespace tdlibQt
