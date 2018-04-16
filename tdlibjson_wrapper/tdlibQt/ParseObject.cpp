#include "ParseObject.hpp"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include "NotificationManager.hpp"
#include <QDateTime>
#include <QGuiApplication>

namespace tdlibQt {
ParseObject::ParseObject(QObject *parent) : QObject(parent)
{

}
void ParseObject::parseResponse(const QByteArray &json)
{
    QJsonParseError err;
    auto doc = QJsonDocument::fromJson(json, &err);
    if (err.error != QJsonParseError::NoError) {
        qDebug() << err.errorString();
        return;
    }
    //    jsonWriter.writeJson(doc);
    QString typeField = doc.object()["@type"].toString();
//    qDebug() << json;

    //    switch (doc.object()["@type"].toString()) {
    //    case "updateBasicGroup":
    //    case "updateBasicGroupFullInfo":
    //    case "updateCall":
    //    case "updateChatDraftMessage":
    //    case "updateChatIsPinned":
    //    case "updateChatPhoto":
    //    case "updateChatReadOutbox":
    //    case "updateChatReplyMarkup":
    //    case "updateChatTitle":
    //    case "updateDeleteMessages":
    //    case "updateFavoriteStickers":
    //    case "updateFileGenerationStart":
    //    case "updateFileGenerationStop":
    //    case "updateInstalledStickerSets":
    //    case "updateMessageContent":
    //    case "updateMessageContentOpened":
    //    case "updateMessageEdited":
    //    case "updateMessageMentionRead":
    //    case "updateMessageSendAcknowledged":
    //    case "updateMessageSendFailed":
    //    case "updateMessageSendSucceeded":
    //    case "updateMessageViews":
    //    case "updateNewCallbackQuery":
    //    case "updateNewChat":
    //    case "updateNewChosenInlineResult":
    //    case "updateNewCustomEvent":
    //    case "updateNewCustomQuery":
    //    case "updateNewInlineCallbackQuery":
    //    case "updateNewInlineQuery":
    //    case "updateNewPreCheckoutQuery":
    //    case "updateNewShippingQuery":
    //    case "updateNotificationSettings":
    //    case "updateOption":
    //    case "updateRecentStickers":
    //    case "updateSavedAnimations":
    //    case "updateSecretChat":
    //    case "updateServiceNotification":
    //    case "updateSupergroup":
    //    case "updateSupergroupFullInfo":
    //    case "updateTrendingStickerSets":
    //    case "updateUser":
    //    case "updateUserChatAction":
    //    case "updateUserFullInfo":
    //    case "updateUserPrivacySettingRules":
    //    case "updateUserStatus":
    //        break;
    if (typeField == "updateAuthorizationState") {
        QString authState = doc.object()["authorization_state"].toObject()["@type"].toString();
        bool isUserRegistered = true;
        auto authorizationState = Enums::AuthorizationState::AuthorizationStateWaitTdlibParameters;
        if (authState == "authorizationStateWaitEncryptionKey")
            authorizationState = Enums::AuthorizationState::AuthorizationStateWaitEncryptionKey;
        if (authState == "authorizationStateWaitPhoneNumber")
            authorizationState = Enums::AuthorizationState::AuthorizationStateWaitPhoneNumber;
        if (authState == "authorizationStateWaitCode") {
            authorizationState = Enums::AuthorizationState::AuthorizationStateWaitCode;
            QJsonObject obj = doc.object()["authorization_state"].toObject();
            QSharedPointer<authorizationStateWaitCode> stateCode = QSharedPointer<authorizationStateWaitCode>
                                                                   (new  authorizationStateWaitCode);
            stateCode->is_registered_ =  obj["is_registered"].toBool();
            stateCode->code_info_ = QSharedPointer<authenticationCodeInfo>
                                    (new  authenticationCodeInfo);
            QJsonObject objInfo = obj["code_info"].toObject();
            stateCode->code_info_->timeout_ = objInfo["timeout"].toBool();
            QJsonObject objTypeInfo = objInfo["type"].toObject();
            if (objTypeInfo["@type"].toString() == "authenticationCodeTypeCall")
                stateCode->code_info_->type_ =  QSharedPointer<authenticationCodeTypeCall>
                                                (new authenticationCodeTypeCall);
            if (objTypeInfo["@type"].toString() == "authenticationCodeTypeFlashCall")
                stateCode->code_info_->type_ =  QSharedPointer<authenticationCodeTypeFlashCall>(new
                                                                                                authenticationCodeTypeFlashCall);
            if (objTypeInfo["@type"].toString() == "authenticationCodeTypeSms")
                stateCode->code_info_->type_ =  QSharedPointer<authenticationCodeTypeSms>
                                                (new authenticationCodeTypeSms);
            if (objTypeInfo["@type"].toString() == "authenticationCodeTypeTelegramMessage")
                stateCode->code_info_->type_ =  QSharedPointer<authenticationCodeTypeTelegramMessage>
                                                (new authenticationCodeTypeTelegramMessage);

            objTypeInfo = objInfo["next_type"].toObject();
            if (objTypeInfo["@type"].toString() == "authenticationCodeTypeCall")
                stateCode->code_info_->next_type_ =  QSharedPointer<authenticationCodeTypeCall>
                                                     (new authenticationCodeTypeCall);
            if (objTypeInfo["@type"].toString() == "authenticationCodeTypeFlashCall")
                stateCode->code_info_->next_type_ =  QSharedPointer<authenticationCodeTypeFlashCall>
                                                     (new authenticationCodeTypeFlashCall);
            if (objTypeInfo["@type"].toString() == "authenticationCodeTypeSms")
                stateCode->code_info_->next_type_ =  QSharedPointer<authenticationCodeTypeSms>
                                                     (new authenticationCodeTypeSms);
            if (objTypeInfo["@type"].toString() == "authenticationCodeTypeTelegramMessage")
                stateCode->code_info_->next_type_ =  QSharedPointer<authenticationCodeTypeTelegramMessage>
                                                     (new authenticationCodeTypeTelegramMessage);
            emit newAuthorizationState(stateCode);
        }
        if (authState == "authorizationStateWaitPassword") {
            auto authState =
                QSharedPointer<authorizationStateWaitPassword>(new authorizationStateWaitPassword);
            authState->has_recovery_email_address_ =
                doc.object()["authorization_state"].toObject()["has_recovery_email_address"].toBool();
            authState->password_hint_ =
                doc.object()["authorization_state"].toObject()["password_hint"].toString().toStdString();
            authState->recovery_email_address_pattern_ =
                doc.object()["authorization_state"].toObject()["recovery_email_address_pattern"].toString().toStdString();
            emit newAuthorizationState(authState);
            authorizationState = Enums::AuthorizationState::AuthorizationStateWaitPassword;

        }
        if (authState == "authorizationStateLoggingOut")
            authorizationState = Enums::AuthorizationState::AuthorizationStateLoggingOut;
        if (authState == "authorizationStateClosing")
            authorizationState = Enums::AuthorizationState::AuthorizationStateClosing;
        if (authState == "authorizationStateClosed")
            authorizationState = Enums::AuthorizationState::AuthorizationStateClosed;
        if (authState == "authorizationStateReady")
            authorizationState = Enums::AuthorizationState::AuthorizationStateReady;
        emit updateAuthorizationState(authorizationState);
    }
    if (typeField == "updateConnectionState") {
        QString connState = doc.object()["state"].toObject()["@type"].toString();
        auto connectionState = Enums::ConnectionState::ConnectionStateWaitingForNetwork;
        if (connState == "connectionStateWaitingForNetwork")
            connectionState = Enums::ConnectionState::ConnectionStateWaitingForNetwork;
        if (connState == "connectionStateConnecting")
            connectionState = Enums::ConnectionState::ConnectionStateConnecting;
        if (connState == "connectionStateConnectingToProxy")
            connectionState = Enums::ConnectionState::ConnectionStateConnectingToProxy;
        if (connState == "connectionStateUpdating")
            connectionState = Enums::ConnectionState::ConnectionStateUpdating;
        if (connState == "connectionStateReady")
            connectionState = Enums::ConnectionState::ConnectionStateReady;

        emit updateConnectionState(connectionState);
    }
    if (typeField == "updateNewChat") {
        qint64 chat_id = getInt64(doc.object()["chat"].toObject()["id"]);
        auto chatObject = doc.object()["chat"].toObject();
        chat_title_[chat_id] = chatObject["title"].toString();
    }
    if (typeField == "updateUser") {
        int user_id = doc.object()["user"].toObject()["id"].toInt();
        auto userObject = doc.object()["user"].toObject();
        QString firstName = userObject["first_name"].toString();
        QString lastName = userObject["last_name"].toString();
        users_[user_id] = firstName + " " + lastName;
    }
    if (typeField == "updateFile") {
        emit updateFile(doc.object());
    }
    if (typeField == "updateChatOrder") {
        emit updateChatOrder(doc.object());
    }
    if (typeField == "updateChatReadInbox") {
        emit updateChatReadInbox(doc.object());
    }
    if (typeField == "updateChatReadOutbox") {
        emit updateChatReadOutbox(doc.object());
    }
    if (typeField == "updateChatUnreadMentionCount") {
        emit updateChatMention(doc.object());
    }
    if (typeField == "updateChatLastMessage") {
        emit updateChatLastMessage(doc.object());
    }
    if (typeField == "updateMessageMentionRead") {
        emit updateMentionRead(doc.object());
    }
    if (typeField == "updateNewMessage") {
        auto rootNewMessage = doc.object();
        emit newMessageFromUpdate(rootNewMessage);
        if (rootNewMessage["disable_notification"].toBool() != true) {
            auto messageObject = rootNewMessage["message"].toObject();

            auto notificationTimestamp = qint64(messageObject["date"].toInt());
            QString notificationSummary;
            QString notificationBody;
            qint64 chatId = getInt64(messageObject["chat_id"]);
            auto chatIt = chat_title_.find(chatId);
            if (chatIt == chat_title_.end())
                notificationSummary = "unknown chat";
            else
                notificationSummary = chatIt->second;

            auto userIt = users_.find(messageObject["sender_user_id"].toInt());

            if (userIt == users_.end())
                notificationBody = "unknown user:";
            else
                notificationBody = userIt.value() + ":";


            if (messageObject["content"].toObject()["@type"] == "messageText")
                notificationBody.append(" " +
                                        messageObject["content"].toObject()["text"].toObject()["text"].toString());
            NotificationManager::instance()->notifySummary(notificationTimestamp, notificationSummary,
                                                           notificationBody,
                                                           chatId);
        }

    }
    if (typeField == "chats") {
        QJsonArray chat_ids = doc.object()["chat_ids"].toArray();
        for (auto it = chat_ids.begin(); it != chat_ids.end(); ++it) {
            emit getChat(getInt64(*it));
        }
        emit chatIds(chat_ids.toVariantList());
    }
    if (typeField == "chat") {
        auto chatItem = doc.object();
        emit newChatReceived(chatItem);
    }
    if (typeField == "user") {
        auto userItem = doc.object();
        if (userItem["@extra"].toString() == "getMe")
            emit meReceived(userItem);
    }
    if (typeField == "proxyEmpty" || typeField == "proxySocks5") {
        auto proxyItem = doc.object();
        emit proxyReceived(proxyItem);
    }

    if (typeField == "messages") {
        emit newMessages(doc.object());

//        int totalCount = doc.object()["total_count"].toInt();
//        emit updateTotalCount(totalCount);

//        QVariantList messagesIds;

//        QJsonArray messagesArray = doc.object()["messages"].toArray();
//        for (auto obj : messagesArray) {
//            emit newMessage(obj.toObject());
//            messagesIds.append(obj.toObject()["id"].toVariant());
//        }
//        emit messageIds(messagesIds);
    }
    if (typeField == "updateUserChatAction") {
        emit updateChatAction(doc.object());
    }


}

QString ParseObject::getUserName(int userId)
{
    if (users_.contains(userId))
        return users_[userId];
    return "Unknown";
}
QString ParseObject::getFirstName(int userId)
{
    if (users_.contains(userId))
        return users_[userId].split(' ').at(0);
    return "Unknown";
}
QSharedPointer<message> ParseObject::parseMessage(const QJsonObject &messageObject)
{

    if (messageObject["@type"].toString() != "message")
        return QSharedPointer<message>(nullptr);


    auto resultMessage =  QSharedPointer<message>(new message);
    resultMessage->id_ = getInt64(messageObject["id"]);
    resultMessage->sender_user_id_ = getInt64(messageObject["sender_user_id"]);
    resultMessage->chat_id_ = getInt64(messageObject["chat_id"]);
    resultMessage->is_outgoing_ = messageObject["is_outgoing"].toBool();
    resultMessage->can_be_edited_ = messageObject["can_be_edited"].toBool();
    resultMessage->can_be_forwarded_ = messageObject["can_be_forwarded"].toBool();
    resultMessage->can_be_deleted_only_for_self_ =
        messageObject["can_be_deleted_only_for_self"].toBool();
    resultMessage->can_be_deleted_for_all_users_ =
        messageObject["can_be_deleted_for_all_users"].toBool();
    resultMessage->is_channel_post_ = messageObject["is_channel_post"].toBool();
    resultMessage->contains_unread_mention_ =
        messageObject["contains_unread_mention"].toBool();
    resultMessage->date_ = messageObject["date"].toInt();
    resultMessage->edit_date_ = messageObject["edit_date"].toInt();
    resultMessage->reply_to_message_id_ = getInt64(messageObject["reply_to_message_id"]);
    resultMessage->ttl_ = messageObject["ttl"].toInt();
    resultMessage->ttl_expires_in_ = getInt64(messageObject["ttl_expires_in"]);
    resultMessage->via_bot_user_id_ = messageObject["via_bot_user_id"].toInt();
    resultMessage->author_signature_ =
        messageObject["author_signature"].toString().toStdString();
    resultMessage->views_ = messageObject["views"].toInt();
    resultMessage->media_album_id_ = getInt64(messageObject["media_album_id"]);

    resultMessage->content_ = parseMessageContent(messageObject["content"].toObject());
    resultMessage->reply_markup_ = QSharedPointer<ReplyMarkup>(nullptr);
    resultMessage->forward_info_ = QSharedPointer<MessageForwardInfo>(nullptr);
    resultMessage->sending_state_ = QSharedPointer<MessageSendingState>(nullptr);

    return resultMessage;
}

QSharedPointer<ChatType> ParseObject::parseType(const QJsonObject &typeObject)
{
    if (typeObject["@type"].toString() == "chatTypeBasicGroup") {
        auto resultType = QSharedPointer<chatTypeBasicGroup>
                          (new chatTypeBasicGroup);
        resultType->basic_group_id_ = typeObject["basic_group_id"].toInt();
        return resultType;
    }
    if (typeObject["@type"].toString() == "chatTypePrivate") {
        auto resultType = QSharedPointer<chatTypePrivate>
                          (new chatTypePrivate);
        resultType->user_id_ = typeObject["user_id"].toInt();
        return resultType;
    }
    if (typeObject["@type"].toString() == "chatTypeSupergroup") {
        auto resultType = QSharedPointer<chatTypeSupergroup>
                          (new chatTypeSupergroup);
        resultType->is_channel_ = typeObject["is_channel"].toBool();
        resultType->supergroup_id_ = typeObject["supergroup_id"].toInt();
        return resultType;
        return QSharedPointer<chatTypeSupergroup>(new chatTypeSupergroup);
    }
    if (typeObject["@type"].toString() == "chatTypeSecret") {
        auto resultType = QSharedPointer<chatTypeSecret>
                          (new chatTypeSecret);
        resultType->secret_chat_id_ = typeObject["secret_chat_id"].toInt();
        resultType->user_id_ = typeObject["user_id"].toInt();
        return resultType;
    }

    return QSharedPointer<chatTypePrivate>
           (new chatTypePrivate);
}

QSharedPointer<MessageContent> ParseObject::parseMessageContent(const QJsonObject
                                                                &messageContentObject)
{

    auto typeMessageText = parseMessageText(QJsonObject());
    typeMessageText->text_ = QSharedPointer<formattedText> (new formattedText);
    typeMessageText->text_->text_ = "Unsupported";

    if (messageContentObject["@type"].toString() == "messagePhoto")
        return parseMessagePhoto(messageContentObject);
    if (messageContentObject["@type"].toString() == "messageText")
        return parseMessageText(messageContentObject);
    if (messageContentObject["@type"].toString() == "messageSticker")
        return parseMessageSticker(messageContentObject);
    if (messageContentObject["@type"].toString() == "messageAnimation") {
        typeMessageText->text_->text_ = "Animation";
        return typeMessageText;
    }
    if (messageContentObject["@type"].toString() == "messageAudio") {
        typeMessageText->text_->text_ = "Audio";
        return typeMessageText;
    }
    if (messageContentObject["@type"].toString() == "messageContact") {
        typeMessageText->text_->text_ = "Contact";
        return typeMessageText;
    }
    if (messageContentObject["@type"].toString() == "messageDocument") {
        typeMessageText->text_->text_ = "Document";
        return typeMessageText;
    }
    if (messageContentObject["@type"].toString() == "messageVideo") {
        typeMessageText->text_->text_ = "Video";
        return typeMessageText;
    }

    /* messageAnimation
     * messageAudio
     * messageBasicGroupChatCreate,
     * messageCall,
     * messageChatAddMembers,
     * messageChatChangePhoto,
     * messageChatChangeTitle,
     * messageChatDeleteMember,
     * messageChatDeletePhoto,
     * messageChatJoinByLink,
     * messageChatSetTtl,
     * messageChatUpgradeFrom,
     * messageChatUpgradeTo,
     * messageContact,
     * messageContactRegistered,
     * messageCustomServiceAction,
     * messageDocument,
     * messageExpiredPhoto,
     * messageExpiredVideo,
     * messageGame,
     * messageGameScore,
     * messageInvoice,
     * messageLocation,
     * messagePaymentSuccessful,
     * messagePaymentSuccessfulBot,
     * messagePinMessage,
     * messageScreenshotTaken,
     * messageSupergroupChatCreate,
     * messageUnsupported,
     * messageVenue,
     * messageVideo,
     * messageVideoNote,
     * messageVoiceNote.
    */
    return typeMessageText;
}

QSharedPointer<messageText> ParseObject::parseMessageText(const QJsonObject &messageTextObject)
{
    if (messageTextObject["@type"].toString() != "messageText")
        return QSharedPointer<messageText>(new messageText);

    auto resultMessageContent = QSharedPointer<messageText>(new messageText);
    resultMessageContent->web_page_  = QSharedPointer<webPage>(nullptr);
    resultMessageContent->text_  = parseFormattedTextContent(messageTextObject["text"].toObject());
    return resultMessageContent;
}
QSharedPointer<messageAnimation> ParseObject::parseMessageAnimation(const QJsonObject
                                                                    &messageAnimationObject)
{
    if (messageAnimationObject["@type"].toString() != "messageAnimation")
        return QSharedPointer<messageAnimation>(new messageAnimation);

    auto resultMessageContent = QSharedPointer<messageAnimation> (new messageAnimation);
    resultMessageContent->animation_  = parseAnimation(messageAnimationObject["animation"].toObject());
    resultMessageContent->caption_  = parseFormattedTextContent(
                                          messageAnimationObject["caption"].toObject());
//    resultMessageContent->is_secret_ = messageAnimationObject["is_secret"].toBool();
    return resultMessageContent;
}
QSharedPointer<animation> ParseObject::parseAnimation(const QJsonObject
                                                      &animationObject)
{
    if (animationObject["@type"].toString() != "animation")
        return QSharedPointer<animation>(new animation);
    auto resultAnimation = QSharedPointer<animation>(new animation);
    resultAnimation->animation_ = parseFile(animationObject["animation"].toObject());
    resultAnimation->duration_ = animationObject["duration"].toInt();
    resultAnimation->file_name_ = animationObject["file_name"].toString().toStdString();
    resultAnimation->height_ = animationObject["height"].toInt();
    resultAnimation->mime_type_ = animationObject["mime_type"].toString().toStdString();
    resultAnimation->width_ = animationObject["width"].toInt();
    resultAnimation->thumbnail_ = parsePhotoSize(animationObject["thumbnail"].toObject());


}
QSharedPointer<messageSticker> ParseObject::parseMessageSticker(const QJsonObject
                                                                &messageStikerObject)
{
    if (messageStikerObject["@type"].toString() != "messageSticker")
        return QSharedPointer<messageSticker>(new messageSticker);

    auto resultSticker = QSharedPointer<messageSticker>(new messageSticker);
    resultSticker->sticker_ = parseSticker(messageStikerObject["sticker"].toObject());

    return resultSticker;
}

QSharedPointer<sticker> ParseObject::parseSticker(const QJsonObject &stickerObject)
{
    if (stickerObject["@type"].toString() != "sticker")
        return QSharedPointer<sticker>(new sticker);

    QSharedPointer<sticker> sticker_ =  QSharedPointer<sticker>(new sticker);
    sticker_->emoji_ = stickerObject["emoji"].toString().toStdString();
    sticker_->height_ = stickerObject["height"].toInt();
    sticker_->width_ = stickerObject["width"].toInt();
    sticker_->is_mask_ = stickerObject["is_mask"].toBool();
    sticker_->set_id_ = stickerObject["set_id"].toBool();
    sticker_->mask_position_ = parseMaskPosition(stickerObject["mask_position"].toObject());
    sticker_->sticker_ = parseFile(stickerObject["sticker"].toObject());
    sticker_->thumbnail_ = parsePhotoSize(stickerObject["thumbnail"].toObject());
    return sticker_;
}

QSharedPointer<maskPosition> ParseObject::parseMaskPosition(const QJsonObject &maskPositionObject)
{
    QSharedPointer<maskPosition> maskPositionPtr =  QSharedPointer<maskPosition>(new maskPosition);
    maskPositionPtr->x_shift_ = maskPositionObject["x_shift"].toDouble();
    maskPositionPtr->y_shift_ = maskPositionObject["y_shift"].toDouble();
    maskPositionPtr->scale_ = maskPositionObject["scale"].toDouble();
    if (maskPositionObject["point"].toObject()["@type"].toString() == "maskPointChin")
        maskPositionPtr->point_ = QSharedPointer<maskPointChin>(new maskPointChin);
    if (maskPositionObject["point"].toObject()["@type"].toString() == "maskPointMouth")
        maskPositionPtr->point_ = QSharedPointer<maskPointMouth>(new maskPointMouth);
    if (maskPositionObject["point"].toObject()["@type"].toString() == "maskPointEyes")
        maskPositionPtr->point_ = QSharedPointer<maskPointEyes>(new maskPointEyes);
    if (maskPositionObject["point"].toObject()["@type"].toString() == "maskPointForehead")
        maskPositionPtr->point_ = QSharedPointer<maskPointForehead>(new maskPointForehead);
    return maskPositionPtr;
}

QSharedPointer<notificationSettings> ParseObject::parseNotificationSettings(
    const QJsonObject &notificationSettingsObject)
{
    auto settingsResult = QSharedPointer<notificationSettings>(new notificationSettings);
    settingsResult->mute_for_ = notificationSettingsObject["mute_for"].toInt();
    settingsResult->sound_ = notificationSettingsObject["sound"].toString().toStdString();
    settingsResult->show_preview_ = notificationSettingsObject["show_preview"].toBool();
    return settingsResult;
}

QSharedPointer<messagePhoto> ParseObject::parseMessagePhoto(const QJsonObject &messagePhotoObject)
{
    if (messagePhotoObject["@type"].toString() != "messagePhoto")
        return QSharedPointer<messagePhoto>(nullptr);

    auto resultMessagePhoto = QSharedPointer <messagePhoto>(new messagePhoto);
    resultMessagePhoto->photo_ = parsePhoto(messagePhotoObject["photo"].toObject());

    resultMessagePhoto->caption_ = parseFormattedTextContent(messagePhotoObject["caption"].toObject());
    return resultMessagePhoto;
}

QSharedPointer<photo> ParseObject::parsePhoto(const QJsonObject &photoObject)
{

    //HAS ADDITIONAL TYPE field
    if (photoObject["@type"].toString() != "photo")
        return QSharedPointer<photo>(nullptr);

    auto resultMessagePhoto = QSharedPointer <photo>(new photo);
    resultMessagePhoto->id_ = getInt64(photoObject["id"]);
    resultMessagePhoto->has_stickers_ = photoObject["has_stickers"].toBool();
    for (auto photoSize : photoObject["sizes"].toArray() )
        resultMessagePhoto->sizes_.push_back(parsePhotoSize(photoSize.toObject()));
    return resultMessagePhoto;
}

QSharedPointer<photoSize> ParseObject::parsePhotoSize(const QJsonObject &photoSizeObject)
{
    if (photoSizeObject["@type"].toString() != "photoSize")
        return QSharedPointer<photoSize>(nullptr);
    auto resultPhotoSize = QSharedPointer <photoSize>(new photoSize);
    resultPhotoSize->width_ = photoSizeObject["width"].toInt();
    resultPhotoSize->height_ = photoSizeObject["height"].toInt();
    resultPhotoSize->photo_ = parseFile(photoSizeObject["photo"].toObject());
    return resultPhotoSize;
}

QSharedPointer<formattedText> ParseObject::parseFormattedTextContent(const QJsonObject
                                                                     &formattedTextObject)
{
    if (formattedTextObject["@type"].toString() != "formattedText")
        return QSharedPointer<formattedText>(nullptr);

    auto resultFormattedText  = QSharedPointer<formattedText>(new formattedText);
    resultFormattedText->text_ = formattedTextObject["text"].toString().toStdString();
#warning "TODO Entities, Webpage"
    return resultFormattedText;
}

QSharedPointer<chatPhoto> ParseObject::parseChatPhoto(const QJsonObject &chatPhotoObject)
{
    if (chatPhotoObject["@type"].toString() != "chatPhoto")
        return QSharedPointer<chatPhoto>(nullptr);

    auto resultChatPhoto = QSharedPointer<chatPhoto>(new chatPhoto);
    resultChatPhoto->small_ = parseFile(chatPhotoObject["small"].toObject());
    resultChatPhoto->big_ = parseFile(chatPhotoObject["big"].toObject());
    return resultChatPhoto;
}

QSharedPointer<file> ParseObject::parseFile(const QJsonObject &fileObject)
{
    if (fileObject["@type"].toString() != "file")
        return QSharedPointer<file>(nullptr);

    QSharedPointer<file> resultFile;
    auto smallPhotoObject = fileObject;
    resultFile =  QSharedPointer<file>(new file);

    resultFile->id_ = smallPhotoObject["id"].toInt();
    resultFile->size_ = smallPhotoObject["size"].toInt();
    resultFile->expected_size_ = smallPhotoObject["expected_size"].toInt();
    resultFile->local_ = QSharedPointer<localFile>(new localFile);
    resultFile->remote_ = QSharedPointer<remoteFile>(new remoteFile);

    auto localFileObject = smallPhotoObject["local"].toObject();
    resultFile->local_->path_ = localFileObject["path"].toString().toStdString();
    resultFile->local_->can_be_downloaded_ =
        localFileObject["can_be_downloaded"].toBool();
    resultFile->local_->can_be_deleted_ = localFileObject["can_be_deleted"].toBool();
    resultFile->local_->is_downloading_active_ =
        localFileObject["is_downloading_active"].toBool();
    resultFile->local_->is_downloading_completed_ =
        localFileObject["is_downloading_completed"].toBool();
    resultFile->local_->downloaded_prefix_size_ =
        localFileObject["downloaded_prefix_size"].toInt();
    resultFile->local_->downloaded_size_ = localFileObject["downloaded_size"].toInt();

    auto remoteFileObject = smallPhotoObject["remote"].toObject();
    resultFile->remote_->id_ = remoteFileObject["id"].toString().toStdString();
    resultFile->remote_->is_uploading_active_ =
        remoteFileObject["is_uploading_active"].toBool();
    resultFile->remote_->is_uploading_completed_ =
        remoteFileObject["is_uploading_completed"].toBool();
    resultFile->remote_->uploaded_size_ =
        remoteFileObject["uploaded_size"].toInt();

    return resultFile;
}

QSharedPointer<updateUserChatAction> ParseObject::parseChatAction(const QJsonObject
                                                                  &chatActionObject)
{
    if (chatActionObject["@type"].toString() != "updateUserChatAction")
        return QSharedPointer<updateUserChatAction>(new updateUserChatAction);
    auto resultChatAction = QSharedPointer<updateUserChatAction>(new updateUserChatAction);
    resultChatAction->chat_id_ = getInt64(chatActionObject["chat_id"]);
    resultChatAction->user_id_ = getInt64(chatActionObject["user_id"]);
    //By default
    resultChatAction->action_ = QSharedPointer<chatActionCancel>(new chatActionCancel);

    if (chatActionObject["action"].toObject()["@type"].toString() == "chatActionTyping")
        resultChatAction->action_ = QSharedPointer<chatActionTyping>(new chatActionTyping);
    if (chatActionObject["action"].toObject()["@type"].toString() == "chatActionChoosingContact")
        resultChatAction->action_ = QSharedPointer<chatActionChoosingContact>(new
                                                                              chatActionChoosingContact);
    if (chatActionObject["action"].toObject()["@type"].toString() == "chatActionRecordingVideo")
        resultChatAction->action_ = QSharedPointer<chatActionRecordingVideo>(new chatActionRecordingVideo);
    if (chatActionObject["action"].toObject()["@type"].toString() == "chatActionChoosingLocation")
        resultChatAction->action_ = QSharedPointer<chatActionChoosingLocation>
                                    (new chatActionChoosingLocation);
    if (chatActionObject["action"].toObject()["@type"].toString() == "chatActionRecordingVideoNote")
        resultChatAction->action_ = QSharedPointer<chatActionRecordingVideoNote>
                                    (new chatActionRecordingVideoNote);
    if (chatActionObject["action"].toObject()["@type"].toString() == "chatActionRecordingVoiceNote")
        resultChatAction->action_ = QSharedPointer<chatActionRecordingVoiceNote>
                                    (new chatActionRecordingVoiceNote);
    if (chatActionObject["action"].toObject()["@type"].toString() == "chatActionStartPlayingGame")
        resultChatAction->action_ = QSharedPointer<chatActionStartPlayingGame>
                                    (new chatActionStartPlayingGame);
    if (chatActionObject["action"].toObject()["@type"].toString() == "chatActionUploadingDocument") {
        auto tempAction = QSharedPointer<chatActionUploadingDocument>
                          (new chatActionUploadingDocument);
        tempAction->progress_ = chatActionObject["action"].toObject()["progress"].toInt();
        resultChatAction->action_ = tempAction;
    }
    if (chatActionObject["action"].toObject()["@type"].toString() == "chatActionUploadingPhoto") {
        auto tempAction = QSharedPointer<chatActionUploadingPhoto>(new chatActionUploadingPhoto);
        tempAction->progress_ = chatActionObject["action"].toObject()["progress"].toInt();
        resultChatAction->action_ = tempAction;
    }
    if (chatActionObject["action"].toObject()["@type"].toString() == "chatActionUploadingVideo") {
        auto tempAction = QSharedPointer<chatActionUploadingVideo>(new chatActionUploadingVideo);
        tempAction->progress_ = chatActionObject["action"].toObject()["progress"].toInt();
        resultChatAction->action_ = tempAction;

    }
    if (chatActionObject["action"].toObject()["@type"].toString() == "chatActionUploadingVideoNote") {
        auto tempAction = QSharedPointer<chatActionUploadingVideoNote>
                          (new chatActionUploadingVideoNote);
        tempAction->progress_ = chatActionObject["action"].toObject()["progress"].toInt();
        resultChatAction->action_ = tempAction;

    }
    if (chatActionObject["action"].toObject()["@type"].toString() == "chatActionUploadingVoiceNote") {
        auto tempAction = QSharedPointer<chatActionUploadingVoiceNote>
                          (new chatActionUploadingVoiceNote);
        tempAction->progress_ = chatActionObject["action"].toObject()["progress"].toInt();
        resultChatAction->action_ = tempAction;

    }

    return resultChatAction;
}


}//namespace tdlibQt
