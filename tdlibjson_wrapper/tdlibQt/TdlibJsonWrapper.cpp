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
        //Disable directory from being tracked by tracker
        QFile file(filesDirectory.value("").toString() + "/.nomedia");
        if (!file.exists()) {
            file.open(QIODevice::WriteOnly);
            file.close();
        }
    }

    QVariantMap parametersObject;
    parametersObject["database_directory"] = "/home/nemo/.local/share/harbour-depecher";
    parametersObject["files_directory"] = filesDirectory.value("").toString();
    parametersObject["api_id"] = tdlibQt::appid.toInt();
    parametersObject["api_hash"] = tdlibQt::apphash;
    parametersObject["system_language_code"] = QLocale::languageToString(QLocale::system().language());
    parametersObject["device_model"] = QSysInfo::prettyProductName();
    parametersObject["system_version"] = QSysInfo::productVersion();
    parametersObject["application_version"] = APP_VERSION;
    parametersObject["use_file_database"] = useFileDatabase.value(true).toBool();
    parametersObject["use_chat_info_database"] = useChatInfoDatabase.value(true).toBool();
    parametersObject["use_message_database"] = useMessageDatabase.value(true).toBool();
    parametersObject["enable_storage_optimizer"] = enableStorageOptimizer.value(true).toBool();
    parametersObject["use_secret_chats"] = false;
#ifdef TEST_DC
    parametersObject["use_test_dc"] = true;
#endif

    QVariantMap rootObject;
    rootObject["@type"] = "setTdlibParameters";
    rootObject["parameters"] = parametersObject;
    sendToTelegram(client, QJsonDocument::fromVariant(rootObject).toJson(QJsonDocument::Compact).constData());
    //answer is - {"@type":"updateAuthorizationState","authorization_state":{"@type":"authorizationStateWaitEncryptionKey","is_encrypted":false}}
}

void TdlibJsonWrapper::sendToTelegram(void *Client, const char *str)
{
#ifdef QT_DEBUG
    qDebug() << QString::fromLatin1(str);
#endif
    td_json_client_send(Client, str);
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
    connect(parseObject, &ParseObject::updateChatIsMarkedAsUnread,
            this, &TdlibJsonWrapper::updateChatIsMarkedAsUnread);
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
    connect(parseObject, &ParseObject::proxiesReceived,
            this, &TdlibJsonWrapper::proxiesReceived);
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
    connect(parseObject, &ParseObject::secondsReceived,
            this, &TdlibJsonWrapper::secondsReceived);
    connect(parseObject, &ParseObject::textReceived,
            this, &TdlibJsonWrapper::textReceived);
    connect(parseObject, &ParseObject::updateFileGenerationStartReceived,
            this, &TdlibJsonWrapper::updateFileGenerationStartReceived);
    connect(parseObject, &ParseObject::updateFileGenerationStopReceived,
            this, &TdlibJsonWrapper::updateFileGenerationStopReceived);
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
    sendToTelegram(client, openChat.c_str());

}

void TdlibJsonWrapper::closeChat(const QString &chat_id)
{
    std::string closeChat = "{\"@type\":\"closeChat\","
                            "\"chat_id\":\"" + chat_id.toStdString() + "\"}";
    sendToTelegram(client, closeChat.c_str());
}

void TdlibJsonWrapper::getMe()
{
    QString getMe = "{\"@type\":\"getMe\",\"@extra\":\"getMe\"}";
    sendToTelegram(client, getMe.toStdString().c_str());
}

void TdlibJsonWrapper::requestAuthenticationPasswordRecovery()
{
    QString requestAuthenticationPasswordRecovery =
        "{\"@type\":\"requestAuthenticationPasswordRecovery\"}";
    sendToTelegram(client, requestAuthenticationPasswordRecovery.toStdString().c_str());
}

void TdlibJsonWrapper::recoverAuthenticationPassword(const QString &recoveryCode)
{
    QString recoverAuthenticationPassword =
        "{\"@type\":\"recoverAuthenticationPassword\","
        "\"recovery_code\":\"" + recoveryCode + "\","
        "\"@extra\":\"auth\"}";
    sendToTelegram(client, recoverAuthenticationPassword.toStdString().c_str());
}

void TdlibJsonWrapper::cancelDownloadFile(int fileId, bool only_if_pending)
{
    QString Pending = only_if_pending ? "true" : "false";

    QString cancelDownloadFile =
        "{\"@type\":\"cancelDownloadFile\","
        "\"file_id\":" + QString::number(fileId) + ","
        "\"only_if_pending\":" + Pending + "}";
    sendToTelegram(client, cancelDownloadFile.toStdString().c_str());
}

void TdlibJsonWrapper::cancelUploadFile(int fileId)
{
    QString cancelUploadFile =
        "{\"@type\":\"cancelUploadFile\","
        "\"file_id\":" + QString::number(fileId)  + "}";
    sendToTelegram(client, cancelUploadFile.toStdString().c_str());
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

    sendToTelegram(client, joinChatByInviteLink.toStdString().c_str());
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
    sendToTelegram(client, changeStickerSet.toStdString().c_str());
}


void TdlibJsonWrapper::getProxies()
{
    QString getProxies = "{\"@type\":\"getProxies\"}";
    sendToTelegram(client, getProxies.toStdString().c_str());
}

void TdlibJsonWrapper::addProxy(const QString &address, const int port,
                                const bool &enabled, const QVariantMap &type)
{

    QString proxyType;
    if (type["@type"] == "proxyTypeSocks5")
        proxyType = "{\"@type\":\"proxyTypeSocks5\","
                    "\"username\":\"" + type["username"].toString() + "\","
                    "\"password\":\"" + type["password"].toString() + "\""
                    "}";
    else if (type["@type"] == "proxyTypeHttp") {
        proxyType = "{\"@type\":\"proxyTypeHttp\","
                    "\"username\":\"%1\","
                    "\"password\":\"%2\","
                    "\"http_only\":%3"
                    "}";
        proxyType = proxyType.arg(type["username"].toString(), type["password"].toString(), type["http_only"].toBool() ? QString("true") : QString("false"));
    } else if (type["@type"] == "proxyTypeMtproto")
        proxyType = "{\"@type\":\"proxyTypeMtproto\","
                    "\"secret\":\"" + type["secret"].toString() + "\""
                    "}";
    QString proxy = "{\"@type\":\"addProxy\","
                    "\"server\":\"%1\","
                    "\"port\":%2,"
                    "\"enable\":%3,"
                    "\"type\":%4"
                    "}";
    proxy = proxy.arg(address, QString::number(port), enabled ? QString("true") : QString("false"), proxyType);
    qDebug() << proxy;
    sendToTelegram(client, proxy.toStdString().c_str());
}

void TdlibJsonWrapper::editProxy(const int id, const QString &address, const int port, const bool &enabled, const QVariantMap &type)
{
    QString proxyType;
    if (type["@type"] == "proxyTypeSocks5")
        proxyType = "{\"@type\":\"proxyTypeSocks5\","
                    "\"username\":\"" + type["username"].toString() + "\","
                    "\"password\":\"" + type["password"].toString() + "\""
                    "}";
    else if (type["@type"] == "proxyTypeHttp") {
        proxyType = "{\"@type\":\"proxyTypeHttp\","
                    "\"username\":\"%1\","
                    "\"password\":\"%2\","
                    "\"http_only\":%3"
                    "}";
        proxyType = proxyType.arg(type["username"].toString(), type["password"].toString(), type["http_only"].toBool() ? QString("true") : QString("false"));
    } else if (type["@type"] == "proxyTypeMtproto")
        proxyType = "{\"@type\":\"proxyTypeMtproto\","
                    "\"secret\":\"" + type["secret"].toString() + "\""
                    "}";

    QString proxy = "{\"@type\":\"editProxy\","
                    "\"server\":\"%1\","
                    "\"port\":%2,"
                    "\"enable\":%3,"
                    "\"type\":%4,"
                    "\"proxy_id\":%5"
                    "}";
    proxy = proxy.arg(address, QString::number(port), enabled ? QString("true") : QString("false"), proxyType, QString::number(id));

    sendToTelegram(client, proxy.toStdString().c_str());

}

void TdlibJsonWrapper::disableProxy()
{
    QString str = "{\"@type\":\"disableProxy\"}";
    sendToTelegram(client, str.toStdString().c_str());
}

void TdlibJsonWrapper::enableProxy(const int id)
{
    QString str = "{\"@type\":\"enableProxy\","
                  "\"proxy_id\":%1,"
                  "\"@extra\":\"%2\"}";

    str = str.arg(QString::number(id), "enableProxy_" + QString::number(id));
    sendToTelegram(client, str.toStdString().c_str());
}
void TdlibJsonWrapper::getProxyLink(const int id)
{
    QString str = "{\"@type\":\"getProxyLink\","
                  "\"proxy_id\":%1,"
                  "\"@extra\":\"%2\"}";
    str = str.arg(QString::number(id), "getProxyLink_" + QString::number(id));

    sendToTelegram(client, str.toStdString().c_str());
}

void TdlibJsonWrapper::removeProxy(const int id)
{
    QString str = "{\"@type\":\"removeProxy\","
                  "\"proxy_id\":" + QString::number(id) + "}";
    sendToTelegram(client, str.toStdString().c_str());
}

void TdlibJsonWrapper::pingProxy(const int id)
{
    QString str = "{\"@type\":\"pingProxy\","
                  "\"proxy_id\":%1,"
                  "\"@extra\":\"%2\"}";
    str = str.arg(QString::number(id), "pingProxy_" + QString::number(id));
    sendToTelegram(client, str.toStdString().c_str());
}

void TdlibJsonWrapper::setEncryptionKey(const QString &key)
{
    std::string setDatabaseKey =
        "{\"@type\":\"setDatabaseEncryptionKey\","
        "\"new_encryption_key\":\"" + key.toStdString() + "\"}";
    sendToTelegram(client, setDatabaseKey.c_str());
    //Debug answer - Sending result for request 1: ok {}
}

void TdlibJsonWrapper::setPhoneNumber(const QString &phone)
{
    std::string setAuthenticationPhoneNumber =
        "{\"@type\":\"setAuthenticationPhoneNumber\","
        "\"phone_number\":\"" + phone.toStdString() + "\","
        "\"allow_flash_call\":false,"
        "\"is_current_phone_number\":false}";
    sendToTelegram(client, setAuthenticationPhoneNumber.c_str());

}

void TdlibJsonWrapper::checkCode(const QString &code)
{
    std::string setAuthenticationCode =
        "{\"@type\":\"checkAuthenticationCode\","
        "\"code\":\"" + code.toStdString() + "\","
        "\"@extra\":\"checkCode\"}";

    sendToTelegram(client, setAuthenticationCode.c_str());

}

void TdlibJsonWrapper::checkPassword(const QString &password)
{
    std::string setAuthenticationPassword =
        "{\"@type\":\"checkAuthenticationPassword\","
        "\"password\":\"" + password.toStdString() + "\","
        "\"@extra\":\"checkPassword\"}";

    sendToTelegram(client, setAuthenticationPassword.c_str());
}
void TdlibJsonWrapper::setCodeIfNewUser(const QString &code, const QString &firstName,
                                        const QString &lastName)
{
    std::string AuthCodeIfNewUser =
        "{\"@type\":\"checkAuthenticationCode\","
        "\"code\":\"" + code.toStdString() + "\","
        "\"first_name\":\"" + firstName.toStdString() + "\","
        "\"last_name\":\"" + lastName.toStdString() + "\"}";

    sendToTelegram(client, AuthCodeIfNewUser.c_str());

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
    sendToTelegram(client, getChats.c_str());
}

void TdlibJsonWrapper::getChat(const qint64 chatId, const QString &extra)
{
    QString str;
    if(extra != "")
    {
        str = "{\"@type\":\"getChat\","
              "\"chat_id\":\"%1\","
              "\"@extra\":\"%2\""
              "}";
        str = str.arg(QString::number(chatId),extra);
    }
    else
    {
        str = "{\"@type\":\"getChat\","
              "\"chat_id\":\"%1\"}";
        str = str.arg(QString::number(chatId));
    }

    sendToTelegram(client, str.toStdString().c_str());

}

void TdlibJsonWrapper::searchChatsOnServer(const QString &query, const int limit)
{
    QString str = "{\"@type\":\"searchChatsOnServer\","
                  "\"query\":\"%1\","
                  "\"limit\":%2,"
                  "\"@extra\":\"searchChatsOnServer\""
                  "}";

    str = str.arg(query,QString::number(limit));
    sendToTelegram(client, str.toStdString().c_str());
}

void TdlibJsonWrapper::searchChats(const QString &query, const int limit)
{
    QString str = "{\"@type\":\"searchChats\","
                  "\"query\":\"%1\","
                  "\"limit\":%2,"
                  "\"@extra\":\"searchChats\""
                  "}";

    str = str.arg(query,QString::number(limit));
    sendToTelegram(client, str.toStdString().c_str());
}

void TdlibJsonWrapper::markChatUnread(const qint64 chatId, const bool flag)
{
    QString str = "{\"@type\":\"toggleChatIsMarkedAsUnread\","
                  "\"chat_id\":\"%1\","
                  "\"is_marked_as_unread\":%2}";

    str = str.arg(QString::number(chatId), flag ? "true" : "false");
    sendToTelegram(client, str.toStdString().c_str());

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
    sendToTelegram(client, getFile.toUtf8().constData());
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
    sendToTelegram(client, getChatHistory.toStdString().c_str());
}

void TdlibJsonWrapper::getAttachedStickerSets(const int file_id)
{
    QString getAttachedStickerSetsStr = "{\"@type\":\"getAttachedStickerSets\","
                                        "\"file_id\":" + QString::number(file_id) +
                                        ",\"@extra\": \"getAttachedStickerSets\"}";
    sendToTelegram(client, getAttachedStickerSetsStr.toStdString().c_str());
}
void TdlibJsonWrapper::getStickerSet(const qint64 set_id)
{
    QString getStickerSetStr = "{\"@type\":\"getStickerSet\","
                               "\"set_id\":" + QString::number(set_id) + "}";
    sendToTelegram(client, getStickerSetStr.toStdString().c_str());
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
    sendToTelegram(client, getInstalledStickerSetsStr.toStdString().c_str());
}
void TdlibJsonWrapper::getTrendingStickerSets()
{
    QString getTrendingStickerSetsStr = QString("{\"@type\":\"getTrendingStickerSets\","
                                        "\"@extra\": \"getTrendingStickerSets\"}");
    sendToTelegram(client, getTrendingStickerSetsStr.toStdString().c_str());
}
void TdlibJsonWrapper::getFavoriteStickers()
{
    QString getFavoriteStickersStr = "{\"@type\":\"getFavoriteStickers\""
                                     ",\"@extra\": \"getFavoriteStickers\"}";
    sendToTelegram(client, getFavoriteStickersStr.toStdString().c_str());
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
    sendToTelegram(client, getRecentStickersStr.toStdString().c_str());
}

void TdlibJsonWrapper::logOut()
{
    std::string logOut = "{\"@type\":\"logOut\"}";
    sendToTelegram(client, logOut.c_str());
}

void TdlibJsonWrapper::sendMessage(const QString &json)
{
    QString jsonStr = json;
    //Bug in TDLib
    while (jsonStr.at(jsonStr.length() - 1) == '\n')
        jsonStr = jsonStr.remove(jsonStr.length() - 1, 1);
    sendToTelegram(client, jsonStr.toStdString().c_str());
}

void TdlibJsonWrapper::forwardMessage(const qint64 chat_id, const qint64 from_chat_id, const QVector<qint64> message_ids, const bool disable_notification, const bool from_background, const bool as_album)
{
    QString ids = "";
    for (auto id : message_ids)
        ids.append(QString::number(id) + ",");

    ids = ids.remove(ids.length() - 1, 1);

    QString forwardMessagesStr = "{\"@type\":\"forwardMessages\","
                                 "\"chat_id\":\"%1\","
                                 "\"from_chat_id\":\"%2\","
                                 "\"message_ids\":[%3],"
                                 "\"disable_notification\":%4,"
                                 "\"from_background\":%5,"
                                 "\"as_album\":%6,"
                                 "\"@extra\":\"forwardMessagesExtra\"}";
    forwardMessagesStr = forwardMessagesStr.arg(QString::number(chat_id),
                         QString::number(from_chat_id),
                         ids,
                         disable_notification ? QString("true") : QString("false"),
                         from_background ? QString("true") : QString("false"),
                         as_album ? QString("true") : QString("false"));

    sendToTelegram(client, forwardMessagesStr.toStdString().c_str());
}

void TdlibJsonWrapper::getMessage(const qint64 chat_id, const qint64 message_id, const QString extra)
{
    QString viewMessageStr = "{\"@type\":\"getMessage\","
                             "\"chat_id\":\"%1\","
                             "\"message_id\":\"%2\"}";
    viewMessageStr = viewMessageStr.arg(chat_id, message_id);
    if (extra == "") {
        viewMessageStr = "{\"@type\":\"getMessage\","
                         "\"chat_id\":\"%1\","
                         "\"message_id\":\"%2\"}";
        viewMessageStr = viewMessageStr.arg(chat_id, message_id);
    } else {
        viewMessageStr = "{\"@type\":\"getMessage\","
                         "\"chat_id\":\"%1\","
                         "\"message_id\":\"%2\","
                         "\"extra\":\"%3\"}";
        viewMessageStr = viewMessageStr.arg(QString::number(chat_id), QString::number(message_id), extra);
    }
    sendToTelegram(client, viewMessageStr.toStdString().c_str());
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

    sendToTelegram(client, getMessagesStr.toStdString().c_str());
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
    sendToTelegram(client, viewMessageStr.toStdString().c_str());


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
    sendToTelegram(client, deleteMessagesStr.toStdString().c_str());
}

void TdlibJsonWrapper::setChatMemberStatus(const qint64 chat_id, const int user_id,
        const QString &status)
{
    QString setChatMemberStatusStr = "{\"@type\":\"deleteMessages\","
                                     "\"chat_id\":\"" + QString::number(chat_id) + "\","
                                     "\"user_id\":" + QString::number(user_id) + ","
                                     "\"status\":\"" + status + "\"}";
    sendToTelegram(client, setChatMemberStatusStr.toStdString().c_str());
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
