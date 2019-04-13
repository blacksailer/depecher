#include "ParseObject.hpp"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include "NotificationManager.hpp"
#include <QDateTime>
#include <QGuiApplication>
#include <QFile>

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
    QString typeField = doc.object()["@type"].toString();
#ifdef QT_DEBUG
    qDebug() << json;
#endif
#ifdef WITH_LOG
    QFile logFile("/home/nemo/depecherDatabase/depecher.log");
    if (logFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        logFile.write(QString("["
                              + QDateTime::currentDateTime().toString("MM.dd hh:mm:ss") +
                              "] - " + json
                              +
                              "\n").toUtf8());
        logFile.close();
    }
#endif
    //    switch (doc.object()["@type"].toString()) {
    //    case "updateBasicGroup":
    //    case "updateBasicGroupFullInfo":
    //    case "updateCall":
    //    case "updateChatDraftMessage":
    //    case "updateChatIsPinned":
    //    case "updateChatPhoto":
    //    case "updateChatReplyMarkup":
    //    case "updateChatTitle":
    //    case "updateFavoriteStickers":

    //    case "updateInstalledStickerSets":
    //    case "updateMessageContentOpened":
    //    case "updateMessageSendAcknowledged":
    //    case "updateMessageViews":
    //    case "updateNewCallbackQuery":
    //    case "updateNewChosenInlineResult":
    //    case "updateNewCustomEvent":
    //    case "updateNewCustomQuery":
    //    case "updateNewInlineCallbackQuery":
    //    case "updateNewInlineQuery":
    //    case "updateNewPreCheckoutQuery":
    //    case "updateNewShippingQuery":
    //    case "updateOption":
    //    case "updateRecentStickers":
    //    case "updateSavedAnimations":
    //    case "updateSecretChat":
    //    case "updateServiceNotification":
    //    case "updateSupergroupFullInfo":
    //    case "updateTrendingStickerSets":
    //    case "updateUserFullInfo":
    //    case "updateUserPrivacySettingRules":
    //    case "updateUserStatus":
    //        break;
    if (typeField == "error") {
        emit errorReceived(doc.object());
    }
    if (typeField == "ok") {
        emit okReceived(doc.object());
    }
    if (typeField == "updateChatIsMarkedAsUnread") {
        emit updateChatIsMarkedAsUnread(doc.object());
    }
    if (typeField == "updateAuthorizationState") {
        QString authState = doc.object()["authorization_state"].toObject()["@type"].toString();
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

            //          stateCode->terms_of_service_ =  obj["is_registered"].toBool();

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
        auto chatObject = doc.object()["chat"].toObject();
        qint64 chat_id = getInt64(chatObject["id"]);
        chat_title_[chat_id] = chatObject["title"].toString();
        emit updateNewChat(chatObject);
    }
    if (typeField == "updateUser") {
        auto userObject = doc.object()["user"].toObject();
        int user_id = userObject["id"].toInt();

        QString firstName = userObject["first_name"].toString();
        QString lastName = userObject["last_name"].toString();
        users_[user_id] = firstName + " " + lastName;
        emit updateNewUser(userObject);
    }
    if (typeField == "seconds")
        emit secondsReceived(doc.object());
    if (typeField == "text")
        emit textReceived(doc.object());
    if (typeField == "message")
        emit messageReceived(doc.object());
    if (typeField == "stickerSets")
        emit stickerSetsReceived(doc.object());
    if (typeField == "stickerSet")
        emit stickerSetReceived(doc.object());
    if (typeField == "stickers")
        emit stickersReceived(doc.object());
    if (typeField == "file")
        emit fileReceived(doc.object());
    if (typeField == "updateFile") {
        emit updateFile(doc.object());
    }
    if (typeField ==  "updateNotificationSettings") {
        emit updateNotificationSettingsReceived(doc.object());
    }
    if (typeField == "updateFileGenerationStart")
        emit updateFileGenerationStartReceived(doc.object());
    if (typeField == "updateFileGenerationStop")
        emit updateFileGenerationStopReceived(doc.object());

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
    if (typeField == "updateMessageSendSucceeded") {
        emit updateMessageSendSucceeded(doc.object());
    }
    if (typeField == "updateMessageSendFailed") {
        emit updateMessageSendFailed(doc.object());
    }
    if (typeField == "updateChatLastMessage") {
        emit updateChatLastMessage(doc.object());
    }
    if (typeField == "updateMessageMentionRead") {
        emit updateMentionRead(doc.object());
    }
    if (typeField == "updateNewMessage") {
        emit newMessageFromUpdate(doc.object());
    }
    if (typeField == "callbackQueryAnswer") {
        emit callbackQueryAnswerReceived(doc.object());
    }
    if (typeField == "updateMessageEdited") {
        emit updateMessageEdited(doc.object());
    }
    if (typeField == "updateDeleteMessages") {
        emit updateDeleteMessages(doc.object());
    }
    if (typeField == "updateMessageContent") {
        //    case "updateMessageContent":
        emit updateMessageContent(doc.object());
    }
    if (typeField == "updateSupergroup") {
        emit updateSupergroup(doc.object());
    }

    if (typeField == "chats") {
        QJsonArray chat_ids = doc.object()["chat_ids"].toArray();
        QString extra = "";
        if(doc.object().contains("@extra"))
            extra =  doc.object()["@extra"].toString();
        for (auto it = chat_ids.begin(); it != chat_ids.end(); ++it) {
            emit getChat(getInt64(*it),extra);
        }
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
    if (typeField == "proxies") {
        auto proxyItem = doc.object();
        emit proxiesReceived(proxyItem);
    }
    if (typeField == "proxy") {
        auto proxyItem = doc.object();
        emit proxyReceived(proxyItem);
    }
    if (typeField == "messages") {
        emit newMessages(doc.object());
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
        return QSharedPointer<message>(new message);


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
    resultMessage->reply_markup_ = parseReplyMarkup(messageObject["reply_markup"].toObject());
    resultMessage->forward_info_ = parseForwardInfo(messageObject["forward_info"].toObject());
    resultMessage->sending_state_ = parseMessageSendingState(messageObject["sending_state"].toObject());

    return resultMessage;
}

QSharedPointer<ReplyMarkup> ParseObject::parseReplyMarkup(const QJsonObject &replyMarkupObject)
{
    if (replyMarkupObject["@type"].toString() == "replyMarkupShowKeyboard") {
        QSharedPointer<replyMarkupShowKeyboard> resultReply = QSharedPointer<replyMarkupShowKeyboard>(new replyMarkupShowKeyboard);
        resultReply->is_personal_ = replyMarkupObject["is_personal"].toBool();
        resultReply->resize_keyboard_  = replyMarkupObject["resize_keyboard"].toBool();
        resultReply->one_time_  = replyMarkupObject["one_time"].toBool();
        for (auto row : replyMarkupObject["rows"].toArray()) {
            std::vector<object_ptr<keyboardButton>> rowVector;
            for (auto cell : row.toArray()) {
                QJsonObject cellObject = cell.toObject();
                auto Button = QSharedPointer<keyboardButton>(new keyboardButton);
                Button->text_ = cellObject["text"].toString().toStdString();
                auto cellTypeObject = cellObject["type"].toObject();
                if (cellTypeObject["@type"].toString() == "keyboardButtonTypeText")
                    Button->type_ = QSharedPointer<keyboardButtonTypeText>(new keyboardButtonTypeText);
                if (cellTypeObject["@type"].toString() == "keyboardButtonTypeRequestPhoneNumber")
                    Button->type_ = QSharedPointer<keyboardButtonTypeRequestPhoneNumber>(new keyboardButtonTypeRequestPhoneNumber);
                if (cellTypeObject["@type"].toString() == "keyboardButtonTypeRequestLocation")
                    Button->type_ = QSharedPointer<keyboardButtonTypeRequestLocation>(new keyboardButtonTypeRequestLocation);
                rowVector.push_back(Button);
            }
            resultReply->rows_.push_back(rowVector);
        }
        return resultReply;
    }
    if (replyMarkupObject["@type"].toString() == "replyMarkupInlineKeyboard") {
        QSharedPointer<replyMarkupInlineKeyboard> resultReply = QSharedPointer<replyMarkupInlineKeyboard>(new replyMarkupInlineKeyboard);
        for (auto row : replyMarkupObject["rows"].toArray()) {
            std::vector<object_ptr<inlineKeyboardButton>> rowVector;
            for (auto cell : row.toArray()) {
                QJsonObject cellObject = cell.toObject();
                QSharedPointer<inlineKeyboardButton> Button = QSharedPointer<inlineKeyboardButton>(new inlineKeyboardButton);
                Button->text_ = cellObject["text"].toString().toStdString();
                auto cellTypeObject = cellObject["type"].toObject();
                if (cellTypeObject["@type"].toString() == "inlineKeyboardButtonTypeUrl") {
                    auto inlineType = QSharedPointer<inlineKeyboardButtonTypeUrl>(new inlineKeyboardButtonTypeUrl);
                    inlineType->url_ = cellTypeObject["url"].toString().toStdString();
                    Button->type_ = inlineType;
                }
                if (cellTypeObject["@type"].toString() == "inlineKeyboardButtonTypeCallback") {
                    auto inlineType = QSharedPointer<inlineKeyboardButtonTypeCallback>(new inlineKeyboardButtonTypeCallback);
                    inlineType->data_ = cellTypeObject["data"].toString().toStdString();
                    Button->type_ = inlineType;
                }
                if (cellTypeObject["@type"].toString() == "inlineKeyboardButtonTypeSwitchInline") {
                    auto inlineType = QSharedPointer<inlineKeyboardButtonTypeSwitchInline>(new inlineKeyboardButtonTypeSwitchInline);
                    inlineType->query_ = cellTypeObject["query"].toString().toStdString();
                    inlineType->in_current_chat_ = cellTypeObject["in_current_chat"].toBool();
                    Button->type_ = inlineType;
                }
                if (cellTypeObject["@type"].toString() == "inlineKeyboardButtonTypeCallbackGame")
                    Button->type_ = QSharedPointer<inlineKeyboardButtonTypeCallbackGame>(new inlineKeyboardButtonTypeCallbackGame);
                if (cellTypeObject["@type"].toString() == "inlineKeyboardButtonTypeBuy")
                    Button->type_ = QSharedPointer<inlineKeyboardButtonTypeBuy>(new inlineKeyboardButtonTypeBuy);

                rowVector.push_back(Button);
            }
            resultReply->rows_.push_back(rowVector);
        }

        return resultReply;
    }
    if (replyMarkupObject["@type"].toString() == "replyMarkupRemoveKeyboard") {
        QSharedPointer<replyMarkupRemoveKeyboard> resultReply = QSharedPointer<replyMarkupRemoveKeyboard>(new replyMarkupRemoveKeyboard);
        resultReply->is_personal_ = replyMarkupObject["is_personal"].toBool();
        return resultReply;

    }
    if (replyMarkupObject["@type"].toString() == "replyMarkupForceReply") {
        QSharedPointer<replyMarkupForceReply> resultReply = QSharedPointer<replyMarkupForceReply>(new replyMarkupForceReply);
        resultReply->is_personal_ = replyMarkupObject["is_personal"].toBool();
        return resultReply;
    }
    return QSharedPointer<ReplyMarkup>(nullptr);
}

QSharedPointer<contact> ParseObject::parseContact(const QJsonObject &contactObject)
{
    if (contactObject["@type"].toString() != "contact")
        return QSharedPointer<contact>(nullptr);
    QSharedPointer<contact> contactResult = QSharedPointer<contact>(new contact);
    contactResult->first_name_ = contactObject["first_name"].toString().toStdString();
    contactResult->last_name_ = contactObject["last_name"].toString().toStdString();
    contactResult->phone_number_ = contactObject["phone_number"].toString().toStdString();
    contactResult->user_id_  = contactObject["user_id"].toInt();
    return contactResult;
}
QSharedPointer<MessageSendingState> ParseObject::parseMessageSendingState(const QJsonObject
        &messageSendingStateObject)
{
    if (messageSendingStateObject["@type"].toString() == "messageSendingStatePending")
        return QSharedPointer<MessageSendingState>(new messageSendingStatePending);
    if (messageSendingStateObject["@type"].toString() == "messageSendingStateFailed")
        return QSharedPointer<MessageSendingState>(new messageSendingStateFailed);
    return QSharedPointer<MessageSendingState>(nullptr);
}

QSharedPointer<messageDocument> ParseObject::parseMessageDocument(const QJsonObject
        &messageDocumentObject)
{
    if (messageDocumentObject["@type"].toString() != "messageDocument")
        return QSharedPointer<messageDocument>(new messageDocument);
    auto resultDocument = QSharedPointer<messageDocument>(new messageDocument);
    resultDocument->caption_ = parseFormattedTextContent(messageDocumentObject["caption"].toObject());
    resultDocument->document_ = parseDocument(messageDocumentObject["document"].toObject());
    return resultDocument;
}
QSharedPointer<messageBasicGroupChatCreate> ParseObject::parseMessageBasicGroupChatCreate(const QJsonObject
        &messageBasicGroupChatCreateObject)
{
    if (messageBasicGroupChatCreateObject["@type"].toString() != "messageBasicGroupChatCreate")
        return QSharedPointer<messageBasicGroupChatCreate>(new messageBasicGroupChatCreate);
    auto resultMessage = QSharedPointer<messageBasicGroupChatCreate>(new messageBasicGroupChatCreate);
    resultMessage->title_ = messageBasicGroupChatCreateObject["title"].toString().toStdString();
    for (auto val : messageBasicGroupChatCreateObject["member_user_ids"].toArray())
        resultMessage->member_user_ids_.push_back(val.toInt());
    return resultMessage;
}

QSharedPointer<document> ParseObject::parseDocument(const QJsonObject &documentObject)
{
    if (documentObject["@type"].toString() != "document")
        return QSharedPointer<document>(new document);
    auto resultDocument = QSharedPointer<document>(new document);
    resultDocument->document_ = parseFile(documentObject["document"].toObject());
    resultDocument->file_name_ = documentObject["file_name"].toString().toStdString();
    resultDocument->mime_type_ = documentObject["mime_type"].toString().toStdString();
    resultDocument->thumbnail_ = parsePhotoSize(documentObject["thumbnail"].toObject());
    return resultDocument;
}

QSharedPointer<MessageForwardInfo> ParseObject::parseForwardInfo(const QJsonObject &forwardObject)
{
    if (forwardObject["@type"].toString() == "messageForwardedFromUser") {
        auto resultMessageForwardedFromUser = QSharedPointer<messageForwardedFromUser>
                                              (new messageForwardedFromUser);
        resultMessageForwardedFromUser->date_ = forwardObject["date"].toInt();
        resultMessageForwardedFromUser->forwarded_from_chat_id_ = getInt64(
                    forwardObject["forwarded_from_chat_id"]);
        resultMessageForwardedFromUser->forwarded_from_message_id_ = getInt64(
                    forwardObject["forwarded_from_message_id"]);
        resultMessageForwardedFromUser->sender_user_id_ = forwardObject["sender_user_id"].toInt();
        return resultMessageForwardedFromUser;
    }
    if (forwardObject["@type"].toString() == "messageForwardedPost") {
        auto resultMessageForwardedPost = QSharedPointer<messageForwardedPost>
                                          (new messageForwardedPost);
        resultMessageForwardedPost->author_signature_ =
            forwardObject["author_signature"].toString().toStdString();
        resultMessageForwardedPost->chat_id_ = getInt64(forwardObject["chat_id"]);
        resultMessageForwardedPost->date_ = forwardObject["date"].toInt();
        resultMessageForwardedPost->forwarded_from_chat_id_ = getInt64(
                    forwardObject["forwarded_from_chat_id"]);
        resultMessageForwardedPost->forwarded_from_message_id_ = getInt64(
                    forwardObject["forwarded_from_message_id"]);
        resultMessageForwardedPost->message_id_ = getInt64(
                    forwardObject["message_id"]);

        return resultMessageForwardedPost;

    }
    return QSharedPointer<messageForwardedFromUser>
           (nullptr);
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

QSharedPointer<supergroup> ParseObject::parseSupergroup(const QJsonObject &supergroupObject)
{
    if (supergroupObject["@type"].toString() != "supergroup")
        return QSharedPointer<supergroup>(new supergroup);

    QSharedPointer<supergroup> resultSupergroup = QSharedPointer<supergroup>(new supergroup);
    resultSupergroup->anyone_can_invite_ = supergroupObject["anyone_can_invite"].toBool();
    resultSupergroup->date_ = supergroupObject["date"].toInt();
    resultSupergroup->id_ = getInt64(supergroupObject["id"]);
    resultSupergroup->is_channel_  = supergroupObject["is_channel"].toBool();
    resultSupergroup->is_verified_   = supergroupObject["is_verified"].toBool();
    resultSupergroup->member_count_  = supergroupObject["member_count"].toInt();
    resultSupergroup->restriction_reason_ =
        supergroupObject["restriction_reason"].toString().toStdString();
    resultSupergroup->sign_messages_  = supergroupObject["sign_messages_"].toBool();;
    resultSupergroup->username_ =        supergroupObject["username"].toString().toStdString();

    resultSupergroup->status_ = parseChatMemberStatus(supergroupObject["status"].toObject());//ptr
    return resultSupergroup;
}
QSharedPointer<ChatMemberStatus> ParseObject::parseChatMemberStatus(const QJsonObject
        &chatMemberStatusObject)
{
    if (chatMemberStatusObject["@type"].toString() == "chatMemberStatusAdministrator") {
        auto resultStatus = QSharedPointer<chatMemberStatusAdministrator>(new
                            chatMemberStatusAdministrator);
        resultStatus->can_be_edited_ = chatMemberStatusObject["can_be_edited"].toBool();
        resultStatus->can_change_info_ = chatMemberStatusObject["can_change_info"].toBool();
        resultStatus->can_delete_messages_ = chatMemberStatusObject["can_delete_messages"].toBool();
        resultStatus->can_edit_messages_ = chatMemberStatusObject["can_edit_messages"].toBool();
        resultStatus->can_invite_users_ = chatMemberStatusObject["can_invite_users"].toBool();
        resultStatus->can_pin_messages_ = chatMemberStatusObject["can_pin_messages"].toBool();
        resultStatus->can_post_messages_ = chatMemberStatusObject["can_post_messages"].toBool();
        resultStatus->can_promote_members_ = chatMemberStatusObject["can_promote_members"].toBool();
        resultStatus->can_restrict_members_ = chatMemberStatusObject["can_restrict_members"].toBool();
        return resultStatus;
    }
    if (chatMemberStatusObject["@type"].toString() == "chatMemberStatusBanned") {
        auto resultStatus = QSharedPointer<chatMemberStatusBanned>(new chatMemberStatusBanned);
        resultStatus->banned_until_date_ = chatMemberStatusObject["banned_until_date"].toInt();
        return resultStatus;

    }
    if (chatMemberStatusObject["@type"].toString() == "chatMemberStatusCreator") {
        auto resultStatus = QSharedPointer<chatMemberStatusCreator>(new chatMemberStatusCreator);
        resultStatus->is_member_ = chatMemberStatusObject["is_member"].toBool();
        return resultStatus;
    }
    if (chatMemberStatusObject["@type"].toString() == "chatMemberStatusMember") {
        auto resultStatus = QSharedPointer<chatMemberStatusMember>(new chatMemberStatusMember);
        return resultStatus;
    }
    if (chatMemberStatusObject["@type"].toString() == "chatMemberStatusRestricted") {
        auto resultStatus = QSharedPointer<chatMemberStatusRestricted>(new chatMemberStatusRestricted);
        resultStatus->can_add_web_page_previews_ =
            chatMemberStatusObject["can_add_web_page_previews"].toBool();
        resultStatus->can_send_media_messages_ = chatMemberStatusObject["can_send_media_messages"].toBool();
        resultStatus->can_send_messages_ = chatMemberStatusObject["can_send_messages"].toBool();
        resultStatus->can_send_other_messages_ = chatMemberStatusObject["can_send_other_messages"].toBool();

        return resultStatus;
    }
    auto resultStatus = QSharedPointer<chatMemberStatusLeft>(new chatMemberStatusLeft);
    return resultStatus;

}

QSharedPointer<stickerSets> ParseObject::parseStickerSets(const QJsonObject &stickerSetsObject)
{
    if (stickerSetsObject["@type"].toString() != "stickerSets")
        return QSharedPointer<stickerSets>(new stickerSets);
    auto resultStickerSets = QSharedPointer<stickerSets>(new stickerSets);
    resultStickerSets->total_count_ = stickerSetsObject["total_count"].toInt();
    for (auto val : stickerSetsObject["sets"].toArray())
        resultStickerSets->sets_.push_back(parseStickerSetInfo(val.toObject()));
    return resultStickerSets;
}

QSharedPointer<stickerSetInfo> ParseObject::parseStickerSetInfo(const QJsonObject &stickerSetInfoObject)
{
    if (stickerSetInfoObject["@type"].toString() != "stickerSetInfo")
        return QSharedPointer<stickerSetInfo>(new stickerSetInfo);

    auto resultStickerSetInfo = QSharedPointer<stickerSetInfo>(new stickerSetInfo);
    for (auto val : stickerSetInfoObject["covers"].toArray())
        resultStickerSetInfo->covers_.push_back(parseSticker(val.toObject()));
    resultStickerSetInfo->covers_;
    resultStickerSetInfo->id_ = getInt64(stickerSetInfoObject["id"]);
    resultStickerSetInfo->is_archived_ = stickerSetInfoObject["is_archived"].toBool();
    resultStickerSetInfo->is_installed_ = stickerSetInfoObject["is_installed"].toBool();
    resultStickerSetInfo->is_masks_ = stickerSetInfoObject["is_masks"].toBool();
    resultStickerSetInfo->is_official_ = stickerSetInfoObject["is_official"].toBool();
    resultStickerSetInfo->is_viewed_ = stickerSetInfoObject["is_viewed"].toBool();
    resultStickerSetInfo->name_ = stickerSetInfoObject["name"].toString().toStdString();
    resultStickerSetInfo->size_ = stickerSetInfoObject["size"].toInt();
    resultStickerSetInfo->title_ = stickerSetInfoObject["title"].toString().toStdString();
    return resultStickerSetInfo;

}

QSharedPointer<stickerSet> ParseObject::parseStickerSet(const QJsonObject &stickerSetObject)
{
    if (stickerSetObject["@type"].toString() != "stickerSet")
        return QSharedPointer<stickerSet>(new stickerSet);
    auto resultStickerSet = QSharedPointer<stickerSet>(new stickerSet);
    resultStickerSet->id_ = getInt64(stickerSetObject["id"]);
    resultStickerSet->is_archived_ = stickerSetObject["is_archived"].toBool();
    resultStickerSet->is_installed_ = stickerSetObject["is_installed"].toBool();
    resultStickerSet->is_masks_ = stickerSetObject["is_masks"].toBool();
    resultStickerSet->is_official_ = stickerSetObject["is_official"].toBool();
    resultStickerSet->is_viewed_ = stickerSetObject["is_viewed"].toBool();
    resultStickerSet->name_ = stickerSetObject["name"].toString().toStdString();
    resultStickerSet->title_ = stickerSetObject["title"].toString().toStdString();
    for (auto val : stickerSetObject["emojis"].toArray())
        resultStickerSet->emojis_.push_back(parseStickerEmojis(val.toObject()));
    for (auto val : stickerSetObject["stickers"].toArray())
        resultStickerSet->stickers_.push_back(parseSticker(val.toObject()));
    return resultStickerSet;
}

QSharedPointer<stickerEmojis> ParseObject::parseStickerEmojis(const QJsonObject &stickerEmojisObject)
{
    if (stickerEmojisObject["@type"].toString() != "stickerEmojis")
        return QSharedPointer<stickerEmojis>(new stickerEmojis);
    auto resultEmojis = QSharedPointer<stickerEmojis>(new stickerEmojis);
    for (auto val : stickerEmojisObject["emojis"].toArray())
        resultEmojis->emojis_.push_back(val.toString().toStdString());
    return resultEmojis;
}

QSharedPointer<stickers> ParseObject::parseStickers(const QJsonObject &stickersObject)
{
    if (stickersObject["@type"].toString() != "stickers")
        return QSharedPointer<stickers>(new stickers);
    auto resultStickers = QSharedPointer<stickers>(new stickers);
    for (auto val : stickersObject["stickers"].toArray())
        resultStickers->stickers_.push_back(parseSticker(val.toObject()));
    return resultStickers;
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
    if (messageContentObject["@type"].toString() == "messageAnimation")
        return parseMessageAnimation(messageContentObject);
    if (messageContentObject["@type"].toString() == "messageAudio")
        return parseMessageAudio(messageContentObject);
    if (messageContentObject["@type"].toString() == "messageContact") {
        if (messageContentObject["@type"].toString() != "messageContact")
            return QSharedPointer<messageContact>(new messageContact);
        auto resultMessage = QSharedPointer<messageContact>(new messageContact);
        resultMessage->contact_ = parseContact(messageContentObject["contact"].toObject());
        return resultMessage;
    }

    if (messageContentObject["@type"].toString() == "messageDocument")
        return parseMessageDocument(messageContentObject);
    if (messageContentObject["@type"].toString() == "messageVideo")
        return parseMessageVideo(messageContentObject);
    if (messageContentObject["@type"].toString() == "messageVideoNote")
        return parseMessageVideoNote(messageContentObject);
    if (messageContentObject["@type"].toString() == "messageVoiceNote")
        return parseMessageVoiceNote(messageContentObject);
    if (messageContentObject["@type"].toString() == "messageChatJoinByLink") {
        if (messageContentObject["@type"].toString() != "messageChatJoinByLink")
            return QSharedPointer<messageChatJoinByLink>(new messageChatJoinByLink);
        auto resultMessage = QSharedPointer<messageChatJoinByLink>(new messageChatJoinByLink);
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageContactRegistered") {
        if (messageContentObject["@type"].toString() != "messageContactRegistered")
            return QSharedPointer<messageContactRegistered>(new messageContactRegistered);
        auto resultMessage = QSharedPointer<messageContactRegistered>(new messageContactRegistered);
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageSupergroupChatCreate") {
        if (messageContentObject["@type"].toString() != "messageSupergroupChatCreate")
            return QSharedPointer<messageSupergroupChatCreate>(new messageSupergroupChatCreate);
        auto resultMessage = QSharedPointer<messageSupergroupChatCreate>(new messageSupergroupChatCreate);
        resultMessage->title_ = messageContentObject["title"].toString().toStdString();
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageBasicGroupChatCreate") {
        return parseMessageBasicGroupChatCreate(messageContentObject);
    }
    return typeMessageText;
    if (messageContentObject["@type"].toString() == "messageCall") {
        if (messageContentObject["@type"].toString() != "messageCall")
            return QSharedPointer<messageCall>(new messageCall);
        auto resultMessage = QSharedPointer<messageCall>(new messageCall);
        resultMessage->duration_ = messageContentObject["duration"].toInt();
        resultMessage->discard_reason_ = QSharedPointer<CallDiscardReason>(nullptr);
#warning "TODO discard_reason_"
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageChatAddMembers") {
        if (messageContentObject["@type"].toString() != "messageChatAddMembers")
            return QSharedPointer<messageChatAddMembers>(new messageChatAddMembers);
        auto resultMessage = QSharedPointer<messageChatAddMembers>(new messageChatAddMembers);
        for (auto val : messageContentObject["member_user_ids"].toArray())
            resultMessage->member_user_ids_.push_back(val.toInt());
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageChatChangePhoto") {
        if (messageContentObject["@type"].toString() != "messageChatChangePhoto")
            return QSharedPointer<messageChatChangePhoto>(new messageChatChangePhoto);
        auto resultMessage = QSharedPointer<messageChatChangePhoto>(new messageChatChangePhoto);
        resultMessage->photo_ = parsePhoto(messageContentObject["photo"].toObject());
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageChatChangeTitle") {
        if (messageContentObject["@type"].toString() != "messageChatChangeTitle")
            return QSharedPointer<messageChatChangeTitle>(new messageChatChangeTitle);
        auto resultMessage = QSharedPointer<messageChatChangeTitle>(new messageChatChangeTitle);
        resultMessage->title_ = messageContentObject["title"].toString().toStdString();
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageChatDeleteMember") {
        if (messageContentObject["@type"].toString() != "messageChatDeleteMember")
            return QSharedPointer<messageChatDeleteMember>(new messageChatDeleteMember);
        auto resultMessage = QSharedPointer<messageChatDeleteMember>(new messageChatDeleteMember);
        resultMessage->user_id_ = messageContentObject["user_id"].toInt();
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageChatDeletePhoto") {
        if (messageContentObject["@type"].toString() != "messageChatDeletePhoto")
            return QSharedPointer<messageChatDeletePhoto>(new messageChatDeletePhoto);
        auto resultMessage = QSharedPointer<messageChatDeletePhoto>(new messageChatDeletePhoto);
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageChatSetTtl") {
        if (messageContentObject["@type"].toString() != "messageChatSetTtl")
            return QSharedPointer<messageChatSetTtl>(new messageChatSetTtl);
        auto resultMessage = QSharedPointer<messageChatSetTtl>(new messageChatSetTtl);
        resultMessage->ttl_ = messageContentObject["ttl"].toInt();
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageChatUpgradeFrom") {
        if (messageContentObject["@type"].toString() != "messageChatUpgradeFrom")
            return QSharedPointer<messageChatUpgradeFrom>(new messageChatUpgradeFrom);
        auto resultMessage = QSharedPointer<messageChatUpgradeFrom>(new messageChatUpgradeFrom);
        resultMessage->title_ = messageContentObject["title"].toString().toStdString();
        resultMessage->basic_group_id_ = messageContentObject["basic_group_id"].toInt();

        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageChatUpgradeTo") {
        if (messageContentObject["@type"].toString() != "messageChatUpgradeTo")
            return QSharedPointer<messageChatUpgradeTo>(new messageChatUpgradeTo);
        auto resultMessage = QSharedPointer<messageChatUpgradeTo>(new messageChatUpgradeTo);
        resultMessage->supergroup_id_ = messageContentObject["supergroup_id"].toInt();
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageCustomServiceAction") {
        if (messageContentObject["@type"].toString() != "messageCustomServiceAction")
            return QSharedPointer<messageCustomServiceAction>(new messageCustomServiceAction);
        auto resultMessage = QSharedPointer<messageCustomServiceAction>(new messageCustomServiceAction);
        resultMessage->text_ = messageContentObject["text"].toString().toStdString();
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageExpiredPhoto") {
        if (messageContentObject["@type"].toString() != "messageExpiredPhoto")
            return QSharedPointer<messageExpiredPhoto>(new messageExpiredPhoto);
        auto resultMessage = QSharedPointer<messageExpiredPhoto>(new messageExpiredPhoto);
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageExpiredVideo") {
        if (messageContentObject["@type"].toString() != "messageExpiredVideo")
            return QSharedPointer<messageExpiredVideo>(new messageExpiredVideo);
        auto resultMessage = QSharedPointer<messageExpiredVideo>(new messageExpiredVideo);
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageGame") {
        if (messageContentObject["@type"].toString() != "messageGame")
            return QSharedPointer<messageGame>(new messageGame);
        auto resultMessage = QSharedPointer<messageGame>(new messageGame);
        resultMessage->game_ = QSharedPointer<game>(nullptr);
#warning "TODO game"
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageGameScore") {
        if (messageContentObject["@type"].toString() != "messageGameScore")
            return QSharedPointer<messageGameScore>(new messageGameScore);
        auto resultMessage = QSharedPointer<messageGameScore>(new messageGameScore);
        resultMessage->game_message_id_ = getInt64(messageContentObject["game_message_id"]);
        resultMessage->game_id_ = getInt64(messageContentObject["game_id"]);
        resultMessage->score_ = messageContentObject["score"].toInt();
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageInvoice") {
        if (messageContentObject["@type"].toString() != "messageInvoice")
            return QSharedPointer<messageInvoice>(new messageInvoice);
        auto resultMessage = QSharedPointer<messageInvoice>(new messageInvoice);
        resultMessage->title_ = messageContentObject["title"].toString().toStdString();
        resultMessage->description_ = messageContentObject["description"].toString().toStdString();
        resultMessage->start_parameter_ = messageContentObject["start_parameter"].toString().toStdString();
        resultMessage->photo_ = parsePhoto(messageContentObject["photo"].toObject());
        resultMessage->is_test_ = messageContentObject["is_test"].toBool();
        resultMessage->need_shipping_address_ = messageContentObject["need_shipping_address"].toBool();
        resultMessage->total_amount_ = getInt64(messageContentObject["total_amount"]);
        resultMessage->receipt_message_id_ = getInt64(messageContentObject["receipt_message_id"]);
        resultMessage->currency_ = messageContentObject["currency"].toString().toStdString();

        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageLocation") {
        if (messageContentObject["@type"].toString() != "messageLocation")
            return QSharedPointer<messageLocation>(new messageLocation);
        auto resultMessage = QSharedPointer<messageLocation>(new messageLocation);
        resultMessage->location_ = QSharedPointer<location>(nullptr);
#warning "TODO location"
        resultMessage->live_period_ = messageContentObject["live_period"].toInt();
        resultMessage->expires_in_ =  messageContentObject["expires_in"].toInt();
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messagePaymentSuccessful") {
        if (messageContentObject["@type"].toString() != "messagePaymentSuccessful")
            return QSharedPointer<messagePaymentSuccessful>(new messagePaymentSuccessful);
        auto resultMessage = QSharedPointer<messagePaymentSuccessful>(new messagePaymentSuccessful);
        resultMessage->total_amount_ = getInt64(messageContentObject["total_amount"]);
        resultMessage->invoice_message_id_ = getInt64(messageContentObject["invoice_message_id"]);
        resultMessage->currency_ = messageContentObject["currency"].toString().toStdString();
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messagePaymentSuccessfulBot") {
        if (messageContentObject["@type"].toString() != "messagePaymentSuccessfulBot")
            return QSharedPointer<messagePaymentSuccessfulBot>(new messagePaymentSuccessfulBot);
        auto resultMessage = QSharedPointer<messagePaymentSuccessfulBot>(new messagePaymentSuccessfulBot);
        resultMessage->order_info_ = QSharedPointer<orderInfo>(nullptr);
#warning "TODO orderinfo"
        resultMessage->currency_ = messageContentObject["currency"].toString().toStdString();
        resultMessage->invoice_payload_ = messageContentObject["invoice_payload"].toString().toStdString();
        resultMessage->shipping_option_id_ = messageContentObject["shipping_option_id"].toString().toStdString();
        resultMessage->telegram_payment_charge_id_ = messageContentObject["telegram_payment_charge_id"].toString().toStdString();
        resultMessage->provider_payment_charge_id_ = messageContentObject["provider_payment_charge_id"].toString().toStdString();
        resultMessage->invoice_message_id_ = getInt64(messageContentObject["invoice_message_id"]);
        resultMessage->total_amount_ = getInt64(messageContentObject["total_amount"]);
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messagePinMessage") {
        if (messageContentObject["@type"].toString() != "messagePinMessage")
            return QSharedPointer<messagePinMessage>(new messagePinMessage);
        auto resultMessage = QSharedPointer<messagePinMessage>(new messagePinMessage);
        resultMessage->message_id_ = getInt64(messageContentObject["message_id"]);
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageScreenshotTaken") {
        if (messageContentObject["@type"].toString() != "messageScreenshotTaken")
            return QSharedPointer<messageScreenshotTaken>(new messageScreenshotTaken);
        auto resultMessage = QSharedPointer<messageScreenshotTaken>(new messageScreenshotTaken);
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageUnsupported") {
        if (messageContentObject["@type"].toString() != "messageUnsupported")
            return QSharedPointer<messageUnsupported>(new messageUnsupported);
        auto resultMessage = QSharedPointer<messageUnsupported>(new messageUnsupported);
        return resultMessage;
    }
    if (messageContentObject["@type"].toString() == "messageVenue") {
        if (messageContentObject["@type"].toString() != "messageVenue")
            return QSharedPointer<messageVenue>(new messageVenue);
        auto resultMessage = QSharedPointer<messageVenue>(new messageVenue);
        resultMessage->venue_ = QSharedPointer<venue>(nullptr);
#warning "TODO venue"
        return resultMessage;
    }

    return typeMessageText;
}

QSharedPointer<messageText> ParseObject::parseMessageText(const QJsonObject &messageTextObject)
{
    if (messageTextObject["@type"].toString() != "messageText")
        return QSharedPointer<messageText>(new messageText);

    auto resultMessageContent = QSharedPointer<messageText>(new messageText);
    resultMessageContent->web_page_  = QSharedPointer<webPage>(new webPage);
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
    resultMessageContent->is_secret_ = messageAnimationObject["is_secret"].toBool();
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

    return resultAnimation;
}
QSharedPointer<messageVideo> ParseObject::parseMessageVideo(const QJsonObject
        &messageVideoObject)
{
    if (messageVideoObject["@type"].toString() != "messageVideo")
        return QSharedPointer<messageVideo>(new messageVideo);

    auto resultVideo = QSharedPointer<messageVideo>(new messageVideo);


    resultVideo->caption_ = parseFormattedTextContent(messageVideoObject["caption"].toObject());
    resultVideo->is_secret_ = messageVideoObject["is_secret"].toBool();
    resultVideo->video_ = parseVideo(messageVideoObject["video"].toObject());


    return resultVideo;

}

QSharedPointer<video> ParseObject::parseVideo(const QJsonObject &videoObject)
{
    if (videoObject["@type"].toString() != "video")
        return QSharedPointer<video>(new video);

    auto resultVideo = QSharedPointer<video>(new video);

    resultVideo->duration_ = videoObject["duration"].toInt();
    resultVideo->file_name_ = videoObject["file_name"].toString().toStdString();
    resultVideo->has_stickers_ = videoObject["has_stickers"].toBool();
    resultVideo->height_ = videoObject["height"].toInt();
    resultVideo->mime_type_ = videoObject["mime_type"].toString().toStdString();
    resultVideo->supports_streaming_ = videoObject["supports_streaming"].toBool();
    resultVideo->thumbnail_ = parsePhotoSize(videoObject["thumbnail"].toObject());
    resultVideo->video_ = parseFile(videoObject["video"].toObject());
    resultVideo->width_ = videoObject["width"].toInt();

    return resultVideo;
}

QSharedPointer<videoNote> ParseObject::parseVideoNote(const QJsonObject &videoNoteObject)
{
    if (videoNoteObject["@type"].toString() != "videoNote")
        return QSharedPointer<videoNote>(new videoNote);

    auto resultVideoNote = QSharedPointer<videoNote>(new videoNote);

    resultVideoNote->duration_  = videoNoteObject["duration"].toInt();
    resultVideoNote->length_  = videoNoteObject["length"].toInt();
    resultVideoNote->thumbnail_ = parsePhotoSize(videoNoteObject["thumbnail"].toObject());
    resultVideoNote->video_ = parseFile(videoNoteObject["video"].toObject());


    return resultVideoNote;
}
QSharedPointer<messageVideoNote> ParseObject::parseMessageVideoNote(const QJsonObject
        &messageVideoNoteObject)
{
    if (messageVideoNoteObject["@type"].toString() != "messageVideoNote")
        return QSharedPointer<messageVideoNote>(new messageVideoNote);

    auto resultVideoNote = QSharedPointer<messageVideoNote>(new messageVideoNote);
    resultVideoNote->is_secret_ = messageVideoNoteObject["is_secret"].toBool();
    resultVideoNote->is_viewed_ = messageVideoNoteObject["is_viewed"].toBool();
    resultVideoNote->video_note_ = parseVideoNote(messageVideoNoteObject["video_note"].toObject());

    return resultVideoNote;
}

QSharedPointer<messageVoiceNote> ParseObject::parseMessageVoiceNote(const QJsonObject
        &messageVoiceNoteObject)
{
    if (messageVoiceNoteObject["@type"].toString() != "messageVoiceNote")
        return QSharedPointer<messageVoiceNote>(new messageVoiceNote);

    auto resultVoiceNote = QSharedPointer<messageVoiceNote>(new messageVoiceNote);

    auto voiceNoteObject = messageVoiceNoteObject["voice_note"].toObject();
    resultVoiceNote->voice_note_ = QSharedPointer<voiceNote>(new voiceNote);
    resultVoiceNote->voice_note_->duration_ = voiceNoteObject["duration"].toInt();
    resultVoiceNote->voice_note_->waveform_ = voiceNoteObject["waveform"].toString().toStdString();
    resultVoiceNote->voice_note_->mime_type_ = voiceNoteObject["mime_type"].toString().toStdString();
    resultVoiceNote->voice_note_->voice_ = parseFile(voiceNoteObject["voice"].toObject());

    resultVoiceNote->caption_ = parseFormattedTextContent(messageVoiceNoteObject["caption"].toObject());
    resultVoiceNote->is_listened_ = messageVoiceNoteObject["is_listened"].toBool();

    return resultVoiceNote;
}

QSharedPointer<messageAudio> ParseObject::parseMessageAudio(const QJsonObject
        &messageAudioObject)
{
    if (messageAudioObject["@type"].toString() != "messageAudio")
        return QSharedPointer<messageAudio>(new messageAudio);

    auto resultAudio = QSharedPointer<messageAudio>(new messageAudio);
    auto audioObject = messageAudioObject["audio"].toObject();
    resultAudio->audio_ = QSharedPointer<audio>(new audio);
    resultAudio->audio_->duration_ = audioObject["duration"].toInt();
    resultAudio->audio_->title_ = audioObject["title"].toString().toStdString();
    resultAudio->audio_->performer_ = audioObject["performer"].toString().toStdString();
    resultAudio->audio_->file_name_ = audioObject["file_name"].toString().toStdString();
    resultAudio->audio_->mime_type_ = audioObject["mime_type"].toString().toStdString();
    resultAudio->audio_->album_cover_thumbnail_ = parsePhotoSize(audioObject["album_cover_thumbnail"].toObject());
    resultAudio->audio_->audio_ = parseFile(audioObject["audio"].toObject());

    resultAudio->caption_ = parseFormattedTextContent(messageAudioObject["caption"].toObject());

    return resultAudio;
}

QSharedPointer<proxy> ParseObject::parseProxy(const QJsonObject &proxyObject)
{
    if (proxyObject["@type"].toString() != "proxy")
        return QSharedPointer<proxy>(new proxy);

    auto proxyPtr = QSharedPointer<proxy>(new proxy);
    proxyPtr->id_ = proxyObject["id"].toInt();
    proxyPtr->is_enabled_ = proxyObject["is_enabled"].toBool();
    proxyPtr->server_ = proxyObject["server"].toString().toStdString();
    proxyPtr->port_ = proxyObject["port"].toInt();
    proxyPtr->last_used_date_ = proxyObject["last_used_date"].toInt();
    proxyPtr->type_ = parseProxyType(proxyObject["type"].toObject());

    return proxyPtr;

}

QSharedPointer<ProxyType> ParseObject::parseProxyType(const QJsonObject &proxyTypeObject)
{
    if (proxyTypeObject["@type"].toString() == "proxyTypeSocks5") {
        QSharedPointer<proxyTypeSocks5> proxyTypePtr = QSharedPointer<proxyTypeSocks5>(new proxyTypeSocks5);
        proxyTypePtr->username_ = proxyTypeObject["username"].toString().toStdString();
        proxyTypePtr->password_ = proxyTypeObject["password"].toString().toStdString();
        return proxyTypePtr;
    }
    if (proxyTypeObject["@type"] == "proxyTypeHttp") {
        QSharedPointer<proxyTypeHttp> proxyTypePtr = QSharedPointer<proxyTypeHttp>(new proxyTypeHttp);
        proxyTypePtr->username_ = proxyTypeObject["username"].toString().toStdString();
        proxyTypePtr->password_ = proxyTypeObject["password"].toString().toStdString();
        proxyTypePtr->http_only_ = proxyTypeObject["http_only"].toBool();
        return proxyTypePtr;
    }
    if (proxyTypeObject["@type"] == "proxyTypeMtproto") {
        QSharedPointer<proxyTypeMtproto> proxyTypePtr = QSharedPointer<proxyTypeMtproto>(new proxyTypeMtproto);
        proxyTypePtr->secret_ = proxyTypeObject["secret"].toString().toStdString();
        return proxyTypePtr;
    }
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
    sticker_->set_id_ = getInt64(stickerObject["set_id"]);
    sticker_->mask_position_ = parseMaskPosition(stickerObject["mask_position"].toObject());
    sticker_->sticker_ = parseFile(stickerObject["sticker"].toObject());
    sticker_->thumbnail_ = parsePhotoSize(stickerObject["thumbnail"].toObject());
    return sticker_;
}

QSharedPointer<maskPosition> ParseObject::parseMaskPosition(const QJsonObject &maskPositionObject)
{
    auto maskPositionPtr =  QSharedPointer<maskPosition>(new maskPosition);
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

QSharedPointer<chatNotificationSettings> ParseObject::parseNotificationSettings(
    const QJsonObject &notificationSettingsObject)
{
    auto settingsResult = QSharedPointer<chatNotificationSettings>(new chatNotificationSettings);
    settingsResult->mute_for_ = notificationSettingsObject["mute_for"].toInt();
    settingsResult->sound_ = notificationSettingsObject["sound"].toString().toStdString();
    settingsResult->show_preview_ = notificationSettingsObject["show_preview"].toBool();

    settingsResult->use_default_mute_for_ = notificationSettingsObject["use_default_mute_for"].toBool();
    settingsResult->use_default_sound_ = notificationSettingsObject["use_default_sound"].toBool();
    settingsResult->use_default_show_preview_ = notificationSettingsObject["use_default_show_preview"].toBool();
    return settingsResult;
}

QSharedPointer<messagePhoto> ParseObject::parseMessagePhoto(const QJsonObject &messagePhotoObject)
{
    if (messagePhotoObject["@type"].toString() != "messagePhoto")
        return QSharedPointer<messagePhoto>(new messagePhoto);

    auto resultMessagePhoto = QSharedPointer <messagePhoto>(new messagePhoto);
    resultMessagePhoto->photo_ = parsePhoto(messagePhotoObject["photo"].toObject());

    resultMessagePhoto->caption_ = parseFormattedTextContent(messagePhotoObject["caption"].toObject());
    return resultMessagePhoto;
}

QSharedPointer<photo> ParseObject::parsePhoto(const QJsonObject &photoObject)
{

    //HAS ADDITIONAL TYPE field
    if (photoObject["@type"].toString() != "photo")
        return QSharedPointer<photo>(new photo);

    auto resultMessagePhoto = QSharedPointer <photo>(new photo);
    resultMessagePhoto->id_ = getInt64(photoObject["id"]);
    resultMessagePhoto->has_stickers_ = photoObject["has_stickers"].toBool();
    for (auto photoSize : photoObject["sizes"].toArray())
        resultMessagePhoto->sizes_.push_back(parsePhotoSize(photoSize.toObject()));
    return resultMessagePhoto;
}

QSharedPointer<photoSize> ParseObject::parsePhotoSize(const QJsonObject &photoSizeObject)
{
    if (photoSizeObject["@type"].toString() != "photoSize")
        return QSharedPointer<photoSize>(nullptr); //Checked for nullptr in  StickerModel
    auto resultPhotoSize = QSharedPointer <photoSize>(new photoSize);
    resultPhotoSize->type_ = photoSizeObject["type"].toString().toStdString();
    resultPhotoSize->width_ = photoSizeObject["width"].toInt();
    resultPhotoSize->height_ = photoSizeObject["height"].toInt();
    resultPhotoSize->photo_ = parseFile(photoSizeObject["photo"].toObject());
    return resultPhotoSize;
}

QSharedPointer<formattedText> ParseObject::parseFormattedTextContent(const QJsonObject
        &formattedTextObject)
{
    if (formattedTextObject["@type"].toString() != "formattedText")
        return QSharedPointer<formattedText>(new formattedText);

    auto resultFormattedText  = QSharedPointer<formattedText>(new formattedText);
    resultFormattedText->text_ = formattedTextObject["text"].toString().toStdString();
#warning "TODO Entities, Webpage"
    return resultFormattedText;
}

QSharedPointer<chatPhoto> ParseObject::parseChatPhoto(const QJsonObject &chatPhotoObject)
{
    if (chatPhotoObject["@type"].toString() != "chatPhoto")
        return QSharedPointer<chatPhoto>(new chatPhoto);

    auto resultChatPhoto = QSharedPointer<chatPhoto>(new chatPhoto);
    resultChatPhoto->small_ = parseFile(chatPhotoObject["small"].toObject());
    resultChatPhoto->big_ = parseFile(chatPhotoObject["big"].toObject());
    return resultChatPhoto;
}

QSharedPointer<file> ParseObject::parseFile(const QJsonObject &fileObject)
{
    if (fileObject["@type"].toString() != "file")
        return QSharedPointer<file>(new file);

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

QSharedPointer<chat> ParseObject::parseChat(const QJsonObject &chatObject)
{
    if (chatObject["@type"].toString() != "chat")
        return QSharedPointer<chat>(new chat);
    QSharedPointer<chat> chatItem = QSharedPointer<chat>(new chat);
    chatItem->is_marked_as_unread_ = chatObject["is_marked_as_unread"].toBool();
    chatItem->is_sponsored_ = chatObject["is_sponsored"].toBool();
    chatItem->can_be_reported_ =  chatObject["can_be_reported"].toBool();
    chatItem->default_disable_notification_ =  chatObject["default_disable_notification"].toBool();

    chatItem->client_data_ = chatObject["client_data"].toString().toStdString();
    chatItem->id_ =  getInt64(chatObject["id"]);
    chatItem->is_pinned_ = chatObject["is_pinned"].toBool();
    chatItem->last_read_inbox_message_id_ =  getInt64(
                chatObject["last_read_inbox_message_id"]);
    chatItem->last_read_outbox_message_id_ =  getInt64(
                chatObject["last_read_outbox_message_id"]);
    chatItem->order_ =  chatObject["order"].toString().toLongLong();
    chatItem->reply_markup_message_id_ = getInt64(chatObject["reply_markup_message_id"]);
    chatItem->title_ = chatObject["title"].toString().toStdString();
    chatItem->unread_count_ = chatObject["unread_count"].toInt();
    chatItem->unread_mention_count_ = chatObject["unread_mention_count"].toInt();
    chatItem->last_message_ = parseMessage(chatObject["last_message"].toObject());
    chatItem->type_ = parseType(chatObject["type"].toObject());
    chatItem->photo_ = parseChatPhoto(chatObject["photo"].toObject());
    chatItem->notification_settings_ = parseNotificationSettings(
                                           chatObject["notification_settings"].toObject());

#warning TODO draftMessage
    chatItem->draft_message_ = QSharedPointer<draftMessage>(nullptr);
    return chatItem;


}

QSharedPointer<user> ParseObject::parseUser(const QJsonObject &userObject)
{
    if (userObject["@type"].toString() != "user")
        return QSharedPointer<user>(new user);

    QSharedPointer<user> resultUser =  QSharedPointer<user>(new user);
    resultUser->id_ = getInt64(userObject["id"]);
    resultUser->first_name_ = userObject["first_name"].toString().toStdString();
    resultUser->have_access_ = userObject["have_access"].toBool();
    resultUser->incoming_link_ = parseLinkState(userObject["incoming_link"].toObject());
    resultUser->outgoing_link_ = parseLinkState(userObject["outgoing_link"].toObject());
    resultUser->is_verified_ = userObject["is_verified"].toBool();
    resultUser->language_code_ = userObject["language_code"].toString().toStdString();
    resultUser->last_name_ = userObject["last_name"].toString().toStdString();
    resultUser->username_ = userObject["username"].toString().toStdString();
    resultUser->type_ = parseUserType(userObject["type"].toObject());
    resultUser->status_ = parseUserStatus(userObject["status"].toObject());
    resultUser->restriction_reason_ = userObject["restriction_reason"].toString().toStdString();
    resultUser->profile_photo_ = parseProfilePhoto(userObject["profile_photo"].toObject());
    resultUser->phone_number_ = userObject["phone_number"].toString().toStdString();

    return resultUser;
}

QSharedPointer<profilePhoto> ParseObject::parseProfilePhoto(const QJsonObject &profilePhotoObject)
{
    if (profilePhotoObject["@type"].toString() != "profilePhoto")
        return QSharedPointer<profilePhoto>(new profilePhoto);

    auto resultPhoto = QSharedPointer<profilePhoto>(new profilePhoto);
    resultPhoto->id_ = getInt64(profilePhotoObject["id"]);
    resultPhoto->small_ = parseFile(profilePhotoObject["small"].toObject());
    resultPhoto->big_ = parseFile(profilePhotoObject["big"].toObject());

    return resultPhoto;
}

QSharedPointer<UserStatus> ParseObject::parseUserStatus(const QJsonObject &userStatusObject)
{
    if (userStatusObject["@type"] == "userStatusRecently")
        return QSharedPointer<UserStatus>(new userStatusRecently);
    if (userStatusObject["@type"] == "userStatusOnline") {
        QSharedPointer<userStatusOnline> statusObject = QSharedPointer<userStatusOnline>
                (new userStatusOnline);
        statusObject->expires_ = userStatusObject["expires"].toInt();
        return statusObject;
    }
    if (userStatusObject["@type"] == "userStatusOffline") {
        QSharedPointer<userStatusOffline> statusObject = QSharedPointer<userStatusOffline>
                (new userStatusOffline);
        statusObject->was_online_ = userStatusObject["was_online"].toInt();
        return statusObject;
    }
    if (userStatusObject["@type"] == "userStatusLastMonth")
        return QSharedPointer<UserStatus>(new userStatusLastMonth);
    if (userStatusObject["@type"] == "userStatusLastWeek")
        return QSharedPointer<UserStatus>(new userStatusLastWeek);

    return QSharedPointer<UserStatus>(new userStatusEmpty);
}

QSharedPointer<UserType> ParseObject::parseUserType(const QJsonObject &userTypeObject)
{
    if (userTypeObject["@type"] == "userTypeRegular")
        return QSharedPointer<UserType>(new userTypeRegular);
    if (userTypeObject["@type"] == "userTypeDeleted")
        return QSharedPointer<UserType>(new userTypeDeleted);
    if (userTypeObject["@type"] == "userTypeBot") {
        QSharedPointer<userTypeBot> resultTypeBot = QSharedPointer<userTypeBot>(new userTypeBot);
        resultTypeBot->can_join_groups_ = userTypeObject["can_join_groups"].toBool();
        resultTypeBot->can_read_all_group_messages_ =
            userTypeObject["can_read_all_group_messages"].toBool();
        resultTypeBot->inline_query_placeholder_ =
            userTypeObject["inline_query_placeholder"].toString().toStdString();
        resultTypeBot->is_inline_ = userTypeObject["is_inline"].toBool();
        resultTypeBot->need_location_ = userTypeObject["need_location"].toBool();
        return resultTypeBot;
    }

    return QSharedPointer<UserType>(new userTypeUnknown);
}

QSharedPointer<LinkState> ParseObject::parseLinkState(const QJsonObject &linkStateObject)
{
    if (linkStateObject["@type"].toString() == "linkStateKnowsPhoneNumber")
        return QSharedPointer<LinkState>(new linkStateKnowsPhoneNumber);
    if (linkStateObject["@type"].toString() == "linkStateIsContact")
        return QSharedPointer<LinkState>(new linkStateIsContact);

    return QSharedPointer<LinkState>(new linkStateNone);
}


}//namespace tdlibQt
