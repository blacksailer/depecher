#include "UserInfoProvider.hpp"
#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/ParseObject.hpp"
#include "tdlibQt/models/singletons/UsersModel.hpp"
namespace tdlibQt {
static const QString c_extra = QLatin1String("UserInfoProvider %1");
void UserInfoProvider::emitAll()
{
    emit muteFor();
    emit avatarChanged();

    emit firstNameChanged();
    emit lastNameChanged();
    emit statusChanged();
    emit incomingLinkChanged();
    emit outcomingLinkChanged();
    emit phoneNumberChanged();
    emit usernameChanged();
}

UserInfoProvider::UserInfoProvider(QObject *parent) : InfoProvider(parent)
{
    disconnect(m_tdlibJson, &TdlibJsonWrapper::fileReceived, 0, 0);
    connect(m_tdlibJson, &TdlibJsonWrapper::updateUserReceived,
            this, &UserInfoProvider::updateUserReceived);
    connect(m_tdlibJson, &TdlibJsonWrapper::fileReceived,
            this, &UserInfoProvider::processFile);
    connect(m_tdlibJson, &TdlibJsonWrapper::userFullInfoReceived,
            this, &UserInfoProvider::userFullInfoReceived);
    connect(m_tdlibJson, &TdlibJsonWrapper::errorReceived,
            this, &UserInfoProvider::errorReceived);

}

int UserInfoProvider::userId() const
{
    return m_userId;
}

QString UserInfoProvider::firstName() const
{
    if (m_userInfo.data()) {
        return QString::fromStdString(m_userInfo->first_name_);
    }
    return QString();

}

QString UserInfoProvider::lastName() const
{
    if (m_userInfo.data()) {
        return QString::fromStdString(m_userInfo->last_name_);
    }
    return QString();
}

QString UserInfoProvider::avatar() const
{
    if (m_userInfo.data()) {
        if (m_userInfo->profile_photo_.data()) {
            if (m_userInfo->profile_photo_->small_.data()) {
                if (m_userInfo->profile_photo_->small_->local_->is_downloading_completed_)
                    return QString::fromStdString(m_userInfo->profile_photo_->small_->local_->path_);
                else
                    m_tdlibJson->downloadFile(m_userInfo->profile_photo_->small_->id_, 20, c_extra.arg(QString::number(m_userId)));
            }
        }
    }
    return QString();
}

QString UserInfoProvider::username() const
{
    if (m_userInfo.data()) {

        return QString::fromStdString(m_userInfo->username_);
    }
    return QString();

}

QString UserInfoProvider::status() const
{
    if (m_userInfo.data()) {

        return UsersModel::instance()->getUserStatusAsString(m_userInfo->status_);
    }
    return QString();

}

UserInfoProvider::linkState UserInfoProvider::incomingLink() const
{
    if (m_userInfo.data()) {

        switch (m_userInfo->incoming_link_->get_id()) {
        case linkStateIsContact::ID:
            return linkState::IS_CONTACT;
            break;
        case linkStateKnowsPhoneNumber::ID:
            return linkState::KNOWS_PHONE_NUMBER;
            break;
        default:
            return linkState::NONE;
            break;
        }

    }
    return linkState::NONE;

}

UserInfoProvider::linkState UserInfoProvider::outgoingLink() const
{
    if (m_userInfo.data()) {

        switch (m_userInfo->outgoing_link_->get_id()) {
        case linkStateIsContact::ID:
            return linkState::IS_CONTACT;
            break;
        case linkStateKnowsPhoneNumber::ID:
            return linkState::KNOWS_PHONE_NUMBER;
            break;
        default:
            return linkState::NONE;
            break;
        }
    }
    return linkState::NONE;

}

QString UserInfoProvider::phoneNumber() const
{
    if (m_userInfo.data()) {

        return QString::fromStdString(m_userInfo->phone_number_);
    }
    return QString();

}

void UserInfoProvider::updateUserReceived(const QJsonObject &userObject)
{
    if (userObject["user"].toObject()["id"].toInt() == m_userId) {
        m_userInfo = ParseObject::parseUser(userObject["user"].toObject());
        emitAll();
    }
}

void UserInfoProvider::userFullInfoReceived(const QJsonObject &userFullInfoObject)
{
    if (userFullInfoObject["@extra"].toString() == c_extra.arg(QString::number(m_userId))) {
        m_userFullInfo = ParseObject::parseUserFullInfo(userFullInfoObject);
        setGroupCount(m_userFullInfo->group_in_common_count_);
    }
}



void UserInfoProvider::errorReceived(const QJsonObject &errorObject)
{
    if (errorObject["@extra"].toString() == c_extra.arg(QString::number(m_userId))) {
        setError(errorObject["message"].toString());
    }
}

void UserInfoProvider::processFile(const QJsonObject &fileObject)
{
    if (fileObject["@extra"].toString() == c_extra.arg(QString::number(m_userId))) {
        auto file = ParseObject::parseFile(fileObject);
        if (file->local_->is_downloading_completed_) {
            UsersModel::instance()->setSmallAvatar(m_userId, file);
            m_userInfo->profile_photo_->small_ = file;
            emit avatarChanged();
        }
    }
}

void UserInfoProvider::setUserId(int userId)
{
    if (m_userId == userId)
        return;
    m_userId = userId;
    setChatId((double)m_userId);
    m_userInfo = UsersModel::instance()->getUser(m_userId);
    m_tdlibJson->getUserFullInfo(m_userId, c_extra.arg(QString::number(m_userId)));
    emitAll();
    emit userIdChanged(m_userId);
}

void UserInfoProvider::setGroupCount(int groupCount)
{
    if (m_groupCount == groupCount)
        return;

    m_groupCount = groupCount;
    emit groupCountChanged(m_groupCount);
}






} // namespace tdlibQt
