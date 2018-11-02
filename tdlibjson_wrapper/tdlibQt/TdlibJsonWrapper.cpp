#include "TdlibJsonWrapper.hpp"
#include "include/AppApiInfo.hpp"
#include <iostream>
#include <QThread>
#include "ListenObject.hpp"
#include "ParseObject.hpp"
#include <td/telegram/td_log.h>
#include <MGConfItem>


namespace tdlibQt {

TdlibJsonWrapper::TdlibJsonWrapper(QObject *parent) : QObject(parent)
{
    td_set_log_verbosity_level(2);
    client = td_json_client_create();
    //SEG FAULT means that json has error input variable names
    MGConfItem filesDirectory("/apps/depecher/tdlib/files_directory");
    MGConfItem useFileDatabase("/apps/depecher/tdlib/use_file_database");
    MGConfItem useChatInfoDatabase("/apps/depecher/tdlib/use_chat_info_database");
    MGConfItem useMessageDatabase("/apps/depecher/tdlib/use_message_database");
    MGConfItem enableStorageOptimizer("/apps/depecher/tdlib/enable_storage_optimizer");

    QFileInfo checkDir(filesDirectory.value("").toString());
    if (!checkDir.exists() || !(checkDir.isDir() && checkDir.isWritable()))
        filesDirectory.set("");
    else {
        //Disable directory for being tracked by tracker
        QFile file(filesDirectory.value("").toString() + "/.nomedia");
        if (!file.exists()) {
            file.open(QIODevice::WriteOnly);
            file.close();
        }
    }

    QString tdlibParameters = "{\"@type\":\"setTdlibParameters\",\"parameters\":{"
                              "\"database_directory\":\"/home/nemo/.local/share/harbour-depecher\","
                              "\"files_directory\":\"" + filesDirectory.value("").toString() + "\","
                              "\"api_id\":" + tdlibQt::appid + ","
                              "\"api_hash\":\"" + tdlibQt::apphash + "\","
                              "\"system_language_code\":\""
                              + QLocale::languageToString(QLocale::system().language()) + "\","
                              "\"device_model\":\"" + QSysInfo::prettyProductName() + "\","
                              "\"system_version\":\"" + QSysInfo::productVersion() + "\","
                              "\"application_version\":\"0.4\","
                              "\"use_file_database\":" + (useFileDatabase.value(true).toBool() ?
                                      "true" : "false") + ","
                              "\"use_chat_info_database\":" + (useChatInfoDatabase.value(true).toBool() ?
                                      "true" : "false") + ","
                              "\"use_message_database\":" + (useMessageDatabase.value(true).toBool() ?
                                      "true" : "false") + ","
                              "\"use_secret_chats\":false,"
                              "\"enable_storage_optimizer\":" + (enableStorageOptimizer.value(true).toBool() ?
                                      "true" : "false") +
                              "}}";

    QVariantMap parametersObject;
    parametersObject["database_directory"] = "/home/nemo/.local/share/harbour-depecher";
    parametersObject["files_directory"] = filesDirectory.value("").toString();
    parametersObject["api_id"] = tdlibQt::appid.toInt();
    parametersObject["api_hash"] = tdlibQt::apphash;
    parametersObject["system_language_code"] = QLocale::languageToString(QLocale::system().language());
    parametersObject["device_model"] = QSysInfo::prettyProductName();
    parametersObject["system_version"] = QSysInfo::productVersion();
    parametersObject["application_version"] = "0.4";
    parametersObject["use_file_database"] = useFileDatabase.value(true).toBool();
    parametersObject["use_chat_info_database"] = useChatInfoDatabase.value(true).toBool();
    parametersObject["use_message_database"] = useMessageDatabase.value(true).toBool();
    parametersObject["enable_storage_optimizer"] = enableStorageOptimizer.value(true).toBool();
    parametersObject["use_secret_chats"] = false;

    QVariantMap rootObject;
    rootObject["@type"] = "setTdlibParameters";
    rootObject["parameters"] = parametersObject;
    td_json_client_send(client, QJsonDocument::fromVariant(rootObject).toJson(QJsonDocument::Compact).constData());
    //answer is - {"@type":"updateAuthorizationState","authorization_state":{"@type":"authorizationStateWaitEncryptionKey","is_encrypted":false}}
}

TdlibJsonWrapper *TdlibJsonWrapper::instance()
{
    static TdlibJsonWrapper    instance;
    return &instance;
}

TdlibJsonWrapper::~TdlibJsonWrapper()
{
    td_json_client_destroy(client);
}
void TdlibJsonWrapper::startListen()
{
    listenThread = new QThread;
    parseThread = new QThread;
    //    listenSchedulerThread = new QThread;
    //    listenScheduler = new ListenScheduler();
    //    connect(listenSchedulerThread, &QThread::started,
    //            listenScheduler, &ListenScheduler::beginForever, Qt::QueuedConnection);
    //    listenScheduler->moveToThread(listenSchedulerThread);
    //    listenSchedulerThread->start();

    listenObject = new ListenObject(client);//, listenScheduler->getCondition());
    parseObject = new ParseObject();
    listenObject->moveToThread(listenThread);
    connect(listenThread, &QThread::started,
            listenObject, &ListenObject::listen, Qt::QueuedConnection);
    connect(listenThread, &QThread::destroyed,
            listenObject, &ListenObject::deleteLater, Qt::QueuedConnection);
    connect(listenObject, &ListenObject::resultReady,
            parseObject, &ParseObject::parseResponse, Qt::QueuedConnection);

    connect(parseThread, &QThread::destroyed,
            parseObject, &ParseObject::deleteLater, Qt::QueuedConnection);
    connect(parseObject, &ParseObject::updateAuthorizationState,
            this, &TdlibJsonWrapper::setAuthorizationState);
    connect(parseObject, &ParseObject::newAuthorizationState,
            this, &TdlibJsonWrapper::newAuthorizationState);

    connect(parseObject, &ParseObject::updateConnectionState,
            this, &TdlibJsonWrapper::setConnectionState);
    connect(parseObject, &ParseObject::getChat,
            this, &TdlibJsonWrapper::getChat);
    connect(parseObject, &ParseObject::callbackQueryAnswerReceived,
            this, &TdlibJsonWrapper::callbackQueryAnswerReceived);
    connect(parseObject, &ParseObject::stickerSetReceived,
            this, &TdlibJsonWrapper::stickerSetReceived);
    connect(parseObject, &ParseObject::stickerSetsReceived,
            this, &TdlibJsonWrapper::stickerSetsReceived);
    connect(parseObject, &ParseObject::stickersReceived,
            this, &TdlibJsonWrapper::stickersReceived);
    connect(parseObject, &ParseObject::updateNotificationSettingsReceived,
            this, &TdlibJsonWrapper::updateNotificationSettingsReceived);


    connect(parseObject, &ParseObject::updateNewChat,
            this, &TdlibJsonWrapper::updateNewChat);
    connect(parseObject, &ParseObject::updateNewUser,
            this, &TdlibJsonWrapper::updateNewUser);
    connect(parseObject, &ParseObject::newChatReceived,
    [this](const QJsonObject & chat) {
        if (chat.contains("@extra")) {
            if (chat["@extra"].toString() == "EnSailfish") {
                auto chatPtr = ParseObject::parseChat(chat);
                QVariantMap resultType;
                switch (chatPtr->type_->get_id()) {
                case chatTypeBasicGroup::ID: {
                    resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::BasicGroup);
                }
                case chatTypePrivate::ID: {
                    resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Private);
                }
                case chatTypeSecret::ID: {
                    resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Secret);
                }
                case chatTypeSupergroup::ID: {
                    chatTypeSupergroup *superGroupMetaInfo   = static_cast<chatTypeSupergroup *>
                            (chatPtr->type_.data());
                    resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Supergroup);
                    resultType["is_channel"] = superGroupMetaInfo->is_channel_;
                    resultType["supergroup_id"] = superGroupMetaInfo->supergroup_id_;
                }
                }

                emit getChatByLink(QString::fromStdString(chatPtr->title_), QString::number(chatPtr->id_),
                                   resultType, QString::number(chatPtr->last_read_inbox_message_id_),
                                   QString::number(chatPtr->last_read_outbox_message_id_),
                                   QString::number(chatPtr->last_message_->id_));
            }
        }
        emit newChatGenerated(chat);
    });
    connect(parseObject, &ParseObject::updateFile,
            this, &TdlibJsonWrapper::updateFile);
    connect(parseObject, &ParseObject::newMessages,
            this, &TdlibJsonWrapper::newMessages);
    connect(parseObject, &ParseObject::newMessageFromUpdate,
            this, &TdlibJsonWrapper::newMessageFromUpdate);
    connect(parseObject, &ParseObject::updateMessageEdited,
            this, &TdlibJsonWrapper::updateMessageEdited);
    connect(parseObject, &ParseObject::updateMessageContent,
            this, &TdlibJsonWrapper::updateMessageContent);
    connect(parseObject, &ParseObject::updateDeleteMessages,
            this, &TdlibJsonWrapper::updateDeleteMessages);
    connect(parseObject, &ParseObject::updateChatOrder,
            this, &TdlibJsonWrapper::updateChatOrder);
    connect(parseObject, &ParseObject::updateChatLastMessage,
            this, &TdlibJsonWrapper::updateChatLastMessage);
    connect(parseObject, &ParseObject::updateChatReadInbox,
            this, &TdlibJsonWrapper::updateChatReadInbox);
    connect(parseObject, &ParseObject::updateChatReadOutbox,
            this, &TdlibJsonWrapper::updateChatReadOutbox);
    connect(parseObject, &ParseObject::updateTotalCount,
            this, &TdlibJsonWrapper::updateTotalCount);
    connect(parseObject, &ParseObject::updateChatAction,
            this, &TdlibJsonWrapper::updateUserChatAction);
    connect(parseObject, &ParseObject::updateChatMention,
            this, &TdlibJsonWrapper::updateChatMention);
    connect(parseObject, &ParseObject::updateMentionRead,
            this, &TdlibJsonWrapper::updateMentionRead);
    connect(parseObject, &ParseObject::proxyReceived,
            this, &TdlibJsonWrapper::proxyReceived);
    connect(parseObject, &ParseObject::meReceived,
            this, &TdlibJsonWrapper::meReceived);
    connect(parseObject, &ParseObject::errorReceived,
    [this](const QJsonObject & errorObject) {
        emit errorReceived(errorObject);
        emit errorReceivedMap(errorObject.toVariantMap());
    });
    connect(parseObject, &ParseObject::okReceived,
            this, &TdlibJsonWrapper::okReceived);

    connect(parseObject, &ParseObject::fileReceived,
            this, &TdlibJsonWrapper::fileReceived);
    connect(parseObject, &ParseObject::messageReceived,
            this, &TdlibJsonWrapper::messageReceived);
    connect(parseObject, &ParseObject::updateMessageSendSucceeded,
            this, &TdlibJsonWrapper::updateMessageSendSucceeded);
    connect(parseObject, &ParseObject::updateSupergroup,
            this, &TdlibJsonWrapper::updateSupergroup);

    listenThread->start();
    parseThread->start();



}

bool TdlibJsonWrapper::isCredentialsEmpty() const
{
    return m_isCredentialsEmpty;
}

Enums::AuthorizationState TdlibJsonWrapper::authorizationState() const
{
    return m_authorizationState;
}

Enums::ConnectionState TdlibJsonWrapper::connectionState() const
{
    return m_connectionState;
}

void TdlibJsonWrapper::openChat(const QString &chat_id)
{
    std::string openChat = "{\"@type\":\"openChat\","
                           "\"chat_id\":\"" + chat_id.toStdString() + "\"}";
    td_json_client_send(client, openChat.c_str());

}

void TdlibJsonWrapper::closeChat(const QString &chat_id)
{
    std::string closeChat = "{\"@type\":\"closeChat\","
                            "\"chat_id\":\"" + chat_id.toStdString() + "\"}";
    td_json_client_send(client, closeChat.c_str());
}

void TdlibJsonWrapper::getMe()
{
    QString getMe = "{\"@type\":\"getMe\",\"@extra\":\"getMe\"}";
    td_json_client_send(client, getMe.toStdString().c_str());
}

void TdlibJsonWrapper::requestAuthenticationPasswordRecovery()
{
    QString requestAuthenticationPasswordRecovery =
        "{\"@type\":\"requestAuthenticationPasswordRecovery\"}";
    td_json_client_send(client, requestAuthenticationPasswordRecovery.toStdString().c_str());
}

void TdlibJsonWrapper::recoverAuthenticationPassword(const QString &recoveryCode)
{
    QString recoverAuthenticationPassword =
        "{\"@type\":\"recoverAuthenticationPassword\","
        "\"recovery_code\":\"" + recoveryCode + "\","
        "\"@extra\":\"auth\"}";
    td_json_client_send(client, recoverAuthenticationPassword.toStdString().c_str());
}

void TdlibJsonWrapper::cancelDownloadFile(int fileId, bool only_if_pending)
{
    QString Pending = only_if_pending ? "true" : "false";

    QString cancelDownloadFile =
        "{\"@type\":\"cancelDownloadFile\","
        "\"file_id\":" + QString::number(fileId) + ","
        "\"only_if_pending\":" + Pending + "}";
    td_json_client_send(client, cancelDownloadFile.toStdString().c_str());
}

void TdlibJsonWrapper::cancelUploadFile(int fileId)
{
    QString cancelUploadFile =
        "{\"@type\":\"cancelUploadFile\","
        "\"file_id\":" + QString::number(fileId)  + "}";
    td_json_client_send(client, cancelUploadFile.toStdString().c_str());
}

void TdlibJsonWrapper::joinChatByInviteLink(const QString &link, const QString &extra)
{
    QString joinChatByInviteLink =
        "{\"@type\":\"joinChatByInviteLink\","
        "\"invite_link\":\"" + link  + "\"}";
    if (extra != "") {
        joinChatByInviteLink.remove(joinChatByInviteLink.size() - 1, 1);
        joinChatByInviteLink.append(",\"@extra\":\"" + extra + "\"}");
    }

    td_json_client_send(client, joinChatByInviteLink.toStdString().c_str());
}

void TdlibJsonWrapper::setTotalUnreadCount(int totalUnreadCount)
{
    if (m_totalUnreadCount == totalUnreadCount)
        return;

    m_totalUnreadCount = totalUnreadCount;
    emit totalUnreadCountChanged(totalUnreadCount);
}

void TdlibJsonWrapper::changeStickerSet(const qint64 set_id, const bool is_installed, const bool is_archived)
{
    QString isInstalled = is_installed ? "true" : "false";
    QString isArchived = is_archived ? "true" : "false";

    QString changeStickerSet = "{\"@type\":\"changeStickerSet\","
                               "\"set_id\":\"" + QString::number(set_id) + "\","
                               "\"is_installed\":" + isInstalled + ","
                               "\"is_archived\":" + isArchived + "}";
    td_json_client_send(client, changeStickerSet.toStdString().c_str());
}


void TdlibJsonWrapper::getProxy()
{
    QString getProxy = "{\"@type\":\"getProxy\"}";
    td_json_client_send(client, getProxy.toStdString().c_str());
}

void TdlibJsonWrapper::setProxy(const QString &type, const QString &address, const int port,
                                const QString &username, const QString &password)
{
    QString proxy = "{\"@type\":\"setProxy\","
                    "\"proxy\":{\"@type\":\"proxyEmpty\"}"
                    "}";
    if (type == "proxySocks5")
        proxy = "{\"@type\":\"setProxy\","
                "\"proxy\":"
                "{\"@type\":\"proxySocks5\","
                "\"server\":\"" + address + "\","
                "\"port\":" + QString::number(port) + ","
                "\"username\":\"" + username + "\","
                "\"password\":\"" + password + "\""
                "}"
                "}";

    td_json_client_send(client, proxy.toStdString().c_str());

}

void TdlibJsonWrapper::setEncryptionKey(const QString &key)
{
    std::string setDatabaseKey =
        "{\"@type\":\"setDatabaseEncryptionKey\","
        "\"new_encryption_key\":\"" + key.toStdString() + "\"}";
    td_json_client_send(client, setDatabaseKey.c_str());
    //Debug answer - Sending result for request 1: ok {}
}

void TdlibJsonWrapper::setPhoneNumber(const QString &phone)
{
    std::string setAuthenticationPhoneNumber =
        "{\"@type\":\"setAuthenticationPhoneNumber\","
        "\"phone_number\":\"" + phone.toStdString() + "\","
        "\"allow_flash_call\":false}";
    td_json_client_send(client, setAuthenticationPhoneNumber.c_str());

}

void TdlibJsonWrapper::checkCode(const QString &code)
{
    std::string setAuthenticationCode =
        "{\"@type\":\"checkAuthenticationCode\","
        "\"code\":\"" + code.toStdString() + "\","
        "\"@extra\":\"checkCode\"}";

    td_json_client_send(client, setAuthenticationCode.c_str());

}

void TdlibJsonWrapper::checkPassword(const QString &password)
{
    std::string setAuthenticationPassword =
        "{\"@type\":\"checkAuthenticationPassword\","
        "\"password\":\"" + password.toStdString() + "\","
        "\"@extra\":\"checkPassword\"}";

    td_json_client_send(client, setAuthenticationPassword.c_str());
}
void TdlibJsonWrapper::setCodeIfNewUser(const QString &code, const QString &firstName,
                                        const QString &lastName)
{
    std::string AuthCodeIfNewUser =
        "{\"@type\":\"checkAuthenticationCode\","
        "\"code\":\"" + code.toStdString() + "\","
        "\"first_name\":\"" + firstName.toStdString() + "\","
        "\"last_name\":\"" + lastName.toStdString() + "\"}";

    td_json_client_send(client, AuthCodeIfNewUser.c_str());

}
void TdlibJsonWrapper::getChats(const qint64 offset_chat_id, const qint64 offset_order,
                                const int limit)
{
    auto max_order = std::to_string(offset_order);
    std::string getChats =
        "{\"@type\":\"getChats\","
        "\"offset_order\":\"" + max_order + "\","
        "\"offset_chat_id\":\"" + std::to_string(offset_chat_id) + "\","
        "\"limit\":" + std::to_string(limit) + "}";
    td_json_client_send(client, getChats.c_str());
}

void TdlibJsonWrapper::getChat(const qint64 chatId)
{
    std::string getChat = "{\"@type\":\"getChat\","
                          "\"chat_id\":\"" + std::to_string(chatId) + "\""
                          "}";
    td_json_client_send(client, getChat.c_str());

}

void TdlibJsonWrapper::downloadFile(int fileId, int priority, const QString &extra)
{
    if (priority > 32)
        priority = 32;
    if (priority < 1)
        priority = 1;
    QString getFile = "{\"@type\":\"downloadFile\","
                      "\"file_id\":" + QString::number(fileId) + ","
                      "\"priority\":" + QString::number(priority) +
                      "}";
    if (extra != "") {
        getFile.remove(getFile.size() - 1, 1);
        getFile.append(",\"@extra\":\"" + extra + "\"}");
    }
    td_json_client_send(client, getFile.toUtf8().constData());
}

void TdlibJsonWrapper::getChatHistory(qint64 chat_id, qint64 from_message_id,
                                      int offset,
                                      int limit, bool only_local, const QString &extra)
{
    QString getChatHistory = "{\"@type\":\"getChatHistory\","
                             "\"chat_id\":\"" + QString::number(chat_id) + "\","
                             "\"from_message_id\":\"" + QString::number(from_message_id) + "\","
                             "\"offset\":" + QString::number(offset) + ","
                             "\"limit\":" + QString::number(limit) + ",";
    if (only_local)
        getChatHistory.append("\"only_local\": true");
    else
        getChatHistory.append("\"only_local\": false");

    if (extra != "")
        getChatHistory.append(",\"@extra\": \"" + extra + "\"");
    getChatHistory.append("}");
    td_json_client_send(client, getChatHistory.toStdString().c_str());
}

void TdlibJsonWrapper::getAttachedStickerSets(const int file_id)
{
    QString getAttachedStickerSetsStr = "{\"@type\":\"getAttachedStickerSets\","
                                        "\"file_id\":" + QString::number(file_id) +
                                        ",\"@extra\": \"getAttachedStickerSets\"}";
    td_json_client_send(client, getAttachedStickerSetsStr.toStdString().c_str());
}
void TdlibJsonWrapper::getStickerSet(const qint64 set_id)
{
    QString getStickerSetStr = "{\"@type\":\"getStickerSet\","
                               "\"set_id\":" + QString::number(set_id) + "}";
    td_json_client_send(client, getStickerSetStr.toStdString().c_str());
}
void TdlibJsonWrapper::getInstalledStickerSets(const bool is_masks)
{
    QString getInstalledStickerSetsStr = QString("{\"@type\":\"getInstalledStickerSets\","
                                         "\"is_masks\":");
    if (is_masks)
        getInstalledStickerSetsStr.append("true");
    else
        getInstalledStickerSetsStr.append("false");
    getInstalledStickerSetsStr.append(",\"@extra\": \"getInstalledStickerSets\"}");
    td_json_client_send(client, getInstalledStickerSetsStr.toStdString().c_str());
}
void TdlibJsonWrapper::getTrendingStickerSets()
{
    QString getTrendingStickerSetsStr = QString("{\"@type\":\"getTrendingStickerSets\","
                                        "\"@extra\": \"getTrendingStickerSets\"}");
    td_json_client_send(client, getTrendingStickerSetsStr.toStdString().c_str());
}
void TdlibJsonWrapper::getFavoriteStickers()
{
    QString getFavoriteStickersStr = "{\"@type\":\"getFavoriteStickers\""
                                     ",\"@extra\": \"getFavoriteStickers\"}";
    td_json_client_send(client, getFavoriteStickersStr.toStdString().c_str());
}
void TdlibJsonWrapper::getRecentStickers(const bool is_attached)
{
    QString getRecentStickersStr = QString("{\"@type\":\"getRecentStickers\","
                                           "\"is_attached\":");
    if (is_attached)
        getRecentStickersStr.append("true");
    else
        getRecentStickersStr.append("false");
    getRecentStickersStr.append(",\"@extra\": \"getRecentStickers\"}");
    td_json_client_send(client, getRecentStickersStr.toStdString().c_str());
}

void TdlibJsonWrapper::logOut()
{
    std::string logOut = "{\"@type\":\"logOut\"}";
    td_json_client_send(client, logOut.c_str());
}

void TdlibJsonWrapper::sendMessage(const QString &json)
{
    QString jsonStr = json;
    //Bug in TDLib
    while (jsonStr.at(jsonStr.length() - 1) == '\n')
        jsonStr = jsonStr.remove(jsonStr.length() - 1, 1);
    td_json_client_send(client, jsonStr.toStdString().c_str());
}

void TdlibJsonWrapper::getMessage(const qint64 chat_id, const qint64 message_id, const QString extra)
{
    QString viewMessageStr = "{\"@type\":\"getMessage\","
                             "\"chat_id\":\"%1\","
                             "\"message_id\":\"%2\"}";
    viewMessageStr.arg(chat_id, message_id);
    if (extra == "") {
        viewMessageStr = "{\"@type\":\"getMessage\","
                         "\"chat_id\":\"%1\","
                         "\"message_id\":\"%2\"}";
        viewMessageStr.arg(chat_id, message_id);
    } else {
        viewMessageStr = "{\"@type\":\"getMessage\","
                         "\"chat_id\":\"%1\","
                         "\"message_id\":\"%2\","
                         "\"extra\":\"%3\"}";
        viewMessageStr.arg(QString::number(chat_id), QString::number(message_id), extra);
    }
    td_json_client_send(client, viewMessageStr.toStdString().c_str());
}

void TdlibJsonWrapper::getMessages(const qint64 chat_id, QVector<qint64> message_ids, const QString &extra)
{
    QString getMessagesStr = "{\"@type\":\"getMessages\","
                             "\"chat_id\":\"%1\","
                             "\"message_ids\":%2,"
                             "\"@extra\":\"%3\"}";
    QString messageIdsStr = "[%1]";
    QString messagesIds = "";

    for (int i = 0; i < message_ids.size(); i++)
        if (i == 0)
            messagesIds += "\"" + QString::number(message_ids[i]) + "\"";
        else
            messagesIds += ",\"" + QString::number(message_ids[i]) + "\"";

    getMessagesStr = getMessagesStr.arg(QString::number(chat_id), messageIdsStr.arg(messagesIds), extra);

    qDebug() << getMessagesStr;

    td_json_client_send(client, getMessagesStr.toStdString().c_str());
}

void TdlibJsonWrapper::viewMessages(const QString &chat_id, const QVariantList &messageIds,
                                    const bool force_read)
{
    QString ids = "";
    for (auto id : messageIds)
        ids.append(QString::number(id.toLongLong()) + ",");

    ids = ids.remove(ids.length() - 1, 1);

    QString force_readStr = force_read ? "true" : "false";
    QString viewMessageStr = "{\"@type\":\"viewMessages\","
                             "\"chat_id\":\"" + chat_id + "\","
                             "\"forceRead\":" + force_readStr + ","
                             "\"message_ids\":[" + ids + "]}";
    td_json_client_send(client, viewMessageStr.toStdString().c_str());


}

void TdlibJsonWrapper::deleteMessages(const qint64 chat_id, const QVector<qint64> message_ids,
                                      const bool revoke)
{
    QString ids = "";
    for (auto id : message_ids)
        ids.append(QString::number(id) + ",");

    ids = ids.remove(ids.length() - 1, 1);

    QString revokeStr = revoke ? "true" : "false";
    QString deleteMessagesStr = "{\"@type\":\"deleteMessages\","
                                "\"chat_id\":\"" + QString::number(chat_id) + "\","
                                "\"revoke\":" + revokeStr + ","
                                "\"message_ids\":[" + ids + "]}";
    td_json_client_send(client, deleteMessagesStr.toStdString().c_str());
}

void TdlibJsonWrapper::setChatMemberStatus(const qint64 chat_id, const int user_id,
        const QString &status)
{
    QString setChatMemberStatusStr = "{\"@type\":\"deleteMessages\","
                                     "\"chat_id\":\"" + QString::number(chat_id) + "\","
                                     "\"user_id\":" + QString::number(user_id) + ","
                                     "\"status\":\"" + status + "\"}";
    td_json_client_send(client, setChatMemberStatusStr.toStdString().c_str());
}

void TdlibJsonWrapper::setIsCredentialsEmpty(bool isCredentialsEmpty)
{
    if (m_isCredentialsEmpty == isCredentialsEmpty)
        return;

    m_isCredentialsEmpty = isCredentialsEmpty;
    emit isCredentialsEmptyChanged(isCredentialsEmpty);
}

void TdlibJsonWrapper::setAuthorizationState(Enums::AuthorizationState &authorizationState)
{

    if (m_authorizationState == authorizationState)
        return;

    m_authorizationState = authorizationState;
    emit authorizationStateChanged(authorizationState);
}

void TdlibJsonWrapper::setConnectionState(Enums::ConnectionState &connState)
{
    auto connectionState = connState;

    if (m_connectionState == connectionState)
        return;

    m_connectionState = connectionState;
    emit connectionStateChanged(connectionState);
}

}// namespace tdlibQt
