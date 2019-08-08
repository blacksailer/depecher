#include "DBusShareAdaptor.hpp"
#include "DBusShareAdaptorWrapper.hpp"
#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/ParseObject.hpp"
#include <QDebug>
#include <QFile>
#include <QDBusServer>

static const QString c_dbusServiceName = QStringLiteral("org.blacksailer.depecher");
static const QString c_dbusObjectPath = QStringLiteral("/org/blacksailer/depecher/share");
static const QString c_dbusInterface = QStringLiteral("org.blacksailer.depecher.share");
static const QString c_extraName = QStringLiteral("dbus");

void DBusShareAdaptor::sendPhoto(const QList<qlonglong> &chat_ids, const QString &filepath)
{
    QFile fileInfo(filepath);
    if (fileInfo.exists() && chat_ids.size() > 0) {
        connect(m_tdlibJson, &tdlibQt::TdlibJsonWrapper::updateFile,
                this, &DBusShareAdaptor::updateFileReceived);
        m_filesPending[filepath] = chat_ids.size();
        for (int i = 0; i < chat_ids.size(); i++) {
            tdlibQt::TlStorerToString json;
            tdlibQt::sendMessage sendMessageObject;
            sendMessageObject.chat_id_ = chat_ids[i];
            sendMessageObject.disable_notification_ = false;
            sendMessageObject.from_background_ = false;
            sendMessageObject.input_message_content_ = QSharedPointer<tdlibQt::inputMessagePhoto>(new tdlibQt::inputMessagePhoto);
            tdlibQt::inputMessagePhoto *ptr = static_cast<tdlibQt::inputMessagePhoto *>
                                              (sendMessageObject.input_message_content_.data());
            auto photoPtr = QSharedPointer<tdlibQt::inputFileGenerated>(new tdlibQt::inputFileGenerated);
            photoPtr->original_path_ = filepath.toStdString();
            photoPtr->conversion_ = "copy";
            photoPtr->expected_size_ = QFileInfo(filepath).size();
            ptr->photo_ = photoPtr;
            sendMessageObject.store(json, "input_message_content");
            QString jsonString = QJsonDocument::fromVariant(json.doc["input_message_content"]).toJson();
            jsonString = jsonString.replace("\"null\"", "null");

            m_tdlibJson->sendMessage(jsonString);
        }
    }
}

void DBusShareAdaptor::sendDocument(const QList<qlonglong> &chat_ids, const QString &filepath)
{
    QFile fileInfo(filepath);
    if (fileInfo.exists() && chat_ids.size() > 0) {
        connect(m_tdlibJson, &tdlibQt::TdlibJsonWrapper::updateFile,
                this, &DBusShareAdaptor::updateFileReceived);
        m_filesPending[filepath] = chat_ids.size();
        for (int i = 0; i < chat_ids.size(); i++) {
            tdlibQt::TlStorerToString json;
            tdlibQt::sendMessage sendMessageObject;
            sendMessageObject.chat_id_ = chat_ids[i];
            sendMessageObject.disable_notification_ = false;
            sendMessageObject.from_background_ = true;
            sendMessageObject.input_message_content_ = QSharedPointer<tdlibQt::inputMessageDocument>(new tdlibQt::inputMessageDocument);
            tdlibQt::inputMessageDocument *ptr = static_cast<tdlibQt::inputMessageDocument *>
                                                 (sendMessageObject.input_message_content_.data());
            auto photoPtr = QSharedPointer<tdlibQt::inputFileGenerated>(new tdlibQt::inputFileGenerated);
            photoPtr->original_path_ = filepath.toStdString();
            photoPtr->conversion_ = "copy";
            photoPtr->expected_size_ = QFileInfo(filepath).size();
            ptr->document_ = photoPtr;
            sendMessageObject.store(json, "input_message_content");
            QString jsonString = QJsonDocument::fromVariant(json.doc["input_message_content"]).toJson();
            jsonString = jsonString.replace("\"null\"", "null");

            m_tdlibJson->sendMessage(jsonString);
        }
    }
}

void DBusShareAdaptor::sendText(const QList<qlonglong> &chat_ids, const QString &data)
{
    qDebug() << data;
    QString name = QJsonDocument::fromJson(data.toUtf8()).object()["name"].toString();
    QString content = QJsonDocument::fromJson(data.toUtf8()).object()["data"].toString();
    for (int i = 0; i < chat_ids.size(); i++) {
        emit uploadStarted("0", QString::number(i), name);
        tdlibQt::TlStorerToString json;
        tdlibQt::sendMessage sendMessageObject;
        sendMessageObject.chat_id_ = chat_ids[i];
        sendMessageObject.disable_notification_ = false;
        sendMessageObject.from_background_ = true;
        sendMessageObject.input_message_content_ = QSharedPointer<tdlibQt::inputMessageText>(new tdlibQt::inputMessageText);
        tdlibQt::inputMessageText *ptr = static_cast<tdlibQt::inputMessageText *>
                                         (sendMessageObject.input_message_content_.data());
        ptr->clear_draft_ = true;
        ptr->disable_web_page_preview_ = true;
        ptr->text_ = QSharedPointer<tdlibQt::formattedText>(new tdlibQt::formattedText);
        ptr->text_->text_ = content.toStdString();

        sendMessageObject.store(json, "input_message_content");
        QVariantMap originalObject = json.doc["input_message_content"].toMap();
        originalObject.remove("reply_markup");
        auto jsonObject = QJsonDocument::fromVariant(originalObject);
        m_tdlibJson->sendMessage(jsonObject.toJson());
        emit uploadFinished("0", QString::number(i), QString::number(i));
    }
}

DBusShareAdaptor::DBusShareAdaptor(QObject *parent) : QObject(parent)
{

    auto adaptor = new DBusShareAdaptorWrapper(this);
    QDBusConnection dbus = QDBusConnection::sessionBus();
    qDebug() << dbus.registerObject(c_dbusObjectPath, c_dbusInterface, this);

    adaptor->initPolicy();
    m_tdlibJson = tdlibQt::TdlibJsonWrapper::instance();

    connect(m_tdlibJson, &tdlibQt::TdlibJsonWrapper::updateFileGenerationStartReceived,
            this, &DBusShareAdaptor::fileGenerationStarted);
    connect(m_tdlibJson, &tdlibQt::TdlibJsonWrapper::updateFileGenerationStopReceived,
            this, &DBusShareAdaptor::fileGenerationStoped);
//    connect(m_tdlibJson, &TdlibJsonWrapper::updateFile,
//            this, &DBusShareAdaptor::updateSendingState);
}

DBusShareAdaptor::~DBusShareAdaptor()
{
    QDBusConnection dbus = QDBusConnection::sessionBus();
    dbus.unregisterObject(c_dbusObjectPath); //object path
}


/*
 * "{\"@type\":\"updateFile\",\"file\":{\"@type\":\"file\",\"id\":1149,\"size\":0,
 * \"expected_size\":1818210,\"local\":{\"@type\":\"localFile\",\"path\":\"\",
 * \"can_be_downloaded\":true,\"can_be_deleted\":false,\"is_downloading_active\":false,
 * \"is_downloading_completed\":false,\"downloaded_prefix_size\":0,\"downloaded_size\":0},
 * \"remote\":{\"@type\":\"remoteFile\",\"id\":\"\",\"is_uploading_active\":true,
 * \"is_uploading_completed\":false,\"uploaded_size\":0}}}"
 * */
void DBusShareAdaptor::updateFileReceived(const QJsonObject &updateFileObject)
{
    QSharedPointer<tdlibQt::file> tmp = tdlibQt::ParseObject::parseFile(updateFileObject["file"].toObject());
    if (tmp->remote_->is_uploading_active_) {
        if (m_files.contains(tmp->id_)) {
            m_files[tmp->id_] = tmp;
            int percent = int((qreal)tmp->remote_->uploaded_size_ / (qreal)tmp->local_->downloaded_size_ * 100);
            qDebug() << percent;
            emit uploadProgress("0", QString::number(m_fileIdToGenerationIdMap[tmp->id_]), percent);
            if (percent >= 100) {
                qDebug() << "Upload Finished" << percent;

                emit uploadFinished("0", QString::number(m_fileIdToGenerationIdMap[tmp->id_]), "0");
                m_files.remove(tmp->id_);
                m_fileIdToGenerationIdMap.remove(tmp->id_);
            }
        } else {
            //Initial addition of file
            for (int i = 0; i < m_generationIdPathMap.keys().size(); ++i) {
                qint64 key = m_generationIdPathMap.keys()[i];
                if (m_generationIdPathMap[key].second == QString::fromStdString(tmp->local_->path_)) {
                    m_fileIdToGenerationIdMap[tmp->id_] = key;
                    m_files[tmp->id_] = tmp;
                }
            }
        }
    }

}

void DBusShareAdaptor::fileGenerationStarted(const QJsonObject &updateFileGenerationStartObject)
{
    if (m_filesPending.contains(updateFileGenerationStartObject["original_path"].toString())) {
        m_generationIdPathMap[tdlibQt::ParseObject::getInt64(updateFileGenerationStartObject["generation_id"])]
            = QPair<QString, QString>(updateFileGenerationStartObject["original_path"].toString(), updateFileGenerationStartObject["destination_path"].toString());
        emit uploadStarted("0", updateFileGenerationStartObject["generation_id"].toString(),
                           updateFileGenerationStartObject["original_path"].toString());
    }
}

void DBusShareAdaptor::fileGenerationStoped(const QJsonObject &updateFileGenerationStopObject)
{
    if (m_filesPending.contains(updateFileGenerationStopObject["original_path"].toString())) {
//        disconnect(m_tdlibJson, &tdlibQt::TdlibJsonWrapper::updateFile,
//                   this, &DBusShareAdaptor::updateFileReceived);
//        m_generationIdPathMap.remove(tdlibQt::ParseObject::getInt64(updateFileGenerationStopObject["generation_id"]));

        //        emit uploadFailed(0, updateFileGenerationStopObject["generation_id"].toString());
    }
}




void DBusShareAdaptor::sendMedia(const QList<qlonglong> &chat_ids, const QString &filepath, const QString &mimeType)
{
    if (mimeType.contains("image")) {
        sendPhoto(chat_ids, filepath);
    } else if (mimeType.contains("text")) {
        sendText(chat_ids, filepath);
    } else {
        sendDocument(chat_ids, filepath);
    }

}

void DBusShareAdaptor::sendVCard(const QList<qlonglong> &chat_ids, const QString &data)
{

}


