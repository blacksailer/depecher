#include "InfoProvider.hpp"
#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/models/singletons/UsersModel.hpp"
#include "tdlibQt/ParseObject.hpp"
#include <QMetaEnum>
namespace tdlibQt {
static const QString c_extra = QLatin1String("InfoProvider %1");

InfoProvider::InfoProvider(QObject *parent) : QObject(parent)
{
    m_tdlibJson = TdlibJsonWrapper::instance();
    connect(m_tdlibJson, &TdlibJsonWrapper::countReceived,
            this, &InfoProvider::countReceived);
    connect(m_tdlibJson, &TdlibJsonWrapper::fileReceived,
            this, &InfoProvider::processFile);
}
void InfoProvider::processFile(const QJsonObject &fileObject)
{
    if (fileObject["@extra"].toString() == c_extra.arg(QString::number(m_chatId))) {
        auto file = ParseObject::parseFile(fileObject);
        if (file->local_->is_downloading_completed_) {
            m_chat->photo_->small_ = file;
            emit avatarChanged();
        }
    }
}
QString InfoProvider::avatar() const
{
    if (m_chat.data()) {
        if (m_chat->photo_.data()) {
            if (m_chat->photo_->small_.data()) {
                if (m_chat->photo_->small_->local_->is_downloading_completed_)
                    return QString::fromStdString(m_chat->photo_->small_->local_->path_);
                else
                    m_tdlibJson->downloadFile(m_chat->photo_->small_->id_, 20, c_extra.arg(QString::number(m_chatId)));
            }
        }
    }
    return QString();
}



void InfoProvider::countReceived(const QJsonObject &countObject)
{
    if (countObject.keys().contains("@extra")) {
        QString filter = countObject["@extra"].toString();
        TdlibJsonWrapper::SearchFilter searchFilter = (TdlibJsonWrapper::SearchFilter)
                QMetaEnum::fromType<tdlibQt::TdlibJsonWrapper::SearchFilter>().keyToValue(filter.toStdString().c_str());
        switch (searchFilter) {
        case TdlibJsonWrapper::SearchFilter::searchMessagesFilterPhoto:
            setPhotoCount(countObject["count"].toInt());
            break;
        case TdlibJsonWrapper::SearchFilter::searchMessagesFilterVideo:
            setVideoCount(countObject["count"].toInt());
            break;
        case TdlibJsonWrapper::SearchFilter::searchMessagesFilterDocument:
            setFileCount(countObject["count"].toInt());
            break;
        case TdlibJsonWrapper::SearchFilter::searchMessagesFilterAudio:
            setAudioCount(countObject["count"].toInt());
            break;
        case TdlibJsonWrapper::SearchFilter::searchMessagesFilterUrl:
            setLinkCount(countObject["count"].toInt());
            break;
        case TdlibJsonWrapper::SearchFilter::searchMessagesFilterVoiceNote:
            setVoiceCount(countObject["count"].toInt());
            break;
        default:
            break;
        }
    }
}


void InfoProvider::setChatId(double chatId)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_chatId, chatId))
        return;
    m_chatId = chatId;
    m_tdlibJson->getChatMessageCount(m_chatId, TdlibJsonWrapper::SearchFilter::searchMessagesFilterPhoto,
                                     false, "searchMessagesFilterPhoto");
    m_tdlibJson->getChatMessageCount(m_chatId, TdlibJsonWrapper::SearchFilter::searchMessagesFilterVideo,
                                     false, "searchMessagesFilterVideo");
    m_tdlibJson->getChatMessageCount(m_chatId, TdlibJsonWrapper::SearchFilter::searchMessagesFilterDocument,
                                     false, "searchMessagesFilterDocument");
    m_tdlibJson->getChatMessageCount(m_chatId, TdlibJsonWrapper::SearchFilter::searchMessagesFilterAudio,
                                     false, "searchMessagesFilterAudio");
    m_tdlibJson->getChatMessageCount(m_chatId, TdlibJsonWrapper::SearchFilter::searchMessagesFilterUrl,
                                     false, "searchMessagesFilterUrl");
    m_tdlibJson->getChatMessageCount(m_chatId, TdlibJsonWrapper::SearchFilter::searchMessagesFilterVoiceNote,
                                     false, "searchMessagesFilterVoiceNote");
    m_chat = UsersModel::instance()->getChat(m_chatId);
    emit chatIdChanged(m_chatId);
    emit muteForChanged();
}
int InfoProvider::muteFor() const
{
    if (m_chatId != -1)
        return UsersModel::instance()->getChatMuteFor(m_chatId);
    return 0;
}
void InfoProvider::changeNotifications(bool mute)
{
    qDebug() << mute;
    if (m_chatId != -1) {
        qDebug() << mute;

        qint64 chat_id = (qint64)m_chatId;
        setChatNotificationSettings muteFunction;
        muteFunction.chat_id_ = chat_id;
        if (mute)
            muteFunction.notification_settings_ = QSharedPointer<chatNotificationSettings>(new chatNotificationSettings(false, std::numeric_limits<int>::max(), true, std::string(""), true, false, true, false, false, false));
        else
            muteFunction.notification_settings_ = QSharedPointer<chatNotificationSettings>(new chatNotificationSettings(false, 0, true, std::string(""), true, false, true, false, false, false));

        TlStorerToString jsonConverter;
        muteFunction.store(jsonConverter, "muteFunction");
        QString jsonString = QJsonDocument::fromVariant(jsonConverter.doc["muteFunction"]).toJson();
        jsonString = jsonString.replace("\"null\"", "null");

        qDebug() << jsonString;
        m_tdlibJson->sendMessage(jsonString);

        emit muteForChanged();
    }
}
void InfoProvider::joinChat()
{
    m_tdlibJson->joinChat((qint64)chatId(), c_extra.arg(QString::number(m_chatId)));
}

void InfoProvider::leaveChat()
{
    m_tdlibJson->leaveChat((qint64)chatId(), c_extra.arg(QString::number(m_chatId)));
}
} //namespace tdlibQt
