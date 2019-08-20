#include "AboutMeDAO.hpp"
#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/ParseObject.hpp"
namespace tdlibQt {

AboutMeDAO::AboutMeDAO(QObject *parent) : QObject(parent),
    m_client(TdlibJsonWrapper::instance())
{
    connect(m_client, &TdlibJsonWrapper::meReceived,
            this, &AboutMeDAO::setInfo);
    connect(m_client, &TdlibJsonWrapper::updateFile,
    [this](const QJsonObject & file) {
        if (file["@type"].toString() == "updateFile") {
            auto photoObj = ParseObject::parseFile(file["file"].toObject());
            if (m_profilePhotoId == photoObj->id_
                    && photoObj->local_->is_downloading_completed_) {
                m_profilePhotoId = 0;
                setPhotoPath(QString::fromStdString(photoObj->local_->path_));
            }
        }
    });
}

QString AboutMeDAO::firstName() const
{
    return m_firstName;
}

QString AboutMeDAO::lastName() const
{
    return m_lastName;
}

QString AboutMeDAO::fullName() const
{
    return m_fullName;
}

QString AboutMeDAO::phoneNumber() const
{
    return m_phoneNumber;
}

QString AboutMeDAO::photoPath() const
{
    return m_photoPath;
}

QString AboutMeDAO::id() const
{
    return m_id;
}

bool AboutMeDAO::disableGetMe() const
{
    return m_disableGetMe;
}

void AboutMeDAO::setInfo(const QJsonObject &meObject)
{
    setId(QString::number(ParseObject::getInt64(meObject["id"])));
    setFirstName(meObject["first_name"].toString());
    setLastName(meObject["last_name"].toString());
    setFullName(firstName() + " " + lastName());
    setPhoneNumber("+" + meObject["phone_number"].toString());
    if (meObject.contains("profile_photo")) {
        auto photoObject = meObject["profile_photo"].toObject();
        auto smallPhoto = ParseObject::parseFile(photoObject["small"].toObject());
        if (smallPhoto->local_->is_downloading_completed_)
            setPhotoPath(QString::fromStdString(smallPhoto->local_->path_));
        else {
            m_profilePhotoId = smallPhoto->id_;
            m_client->downloadFile(m_profilePhotoId);
        }
    }
}

void AboutMeDAO::setFirstName(QString firstName)
{
    if (m_firstName == firstName)
        return;

    m_firstName = firstName;
    emit firstNameChanged(firstName);
}

void AboutMeDAO::setLastName(QString lastName)
{
    if (m_lastName == lastName)
        return;

    m_lastName = lastName;
    emit lastNameChanged(lastName);
}

void AboutMeDAO::setFullName(QString fullName)
{
    if (m_fullName == fullName)
        return;

    m_fullName = fullName;
    emit fullNameChanged(fullName);
}

void AboutMeDAO::setPhoneNumber(QString phoneNumber)
{
    if (m_phoneNumber == phoneNumber)
        return;

    m_phoneNumber = phoneNumber;
    emit phoneNumberChanged(phoneNumber);
}

void AboutMeDAO::setPhotoPath(QString photoPath)
{
    if (m_photoPath == photoPath)
        return;

    m_photoPath = photoPath;
    emit photoPathChanged(photoPath);
}

void AboutMeDAO::setId(QString id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged(id);
}

void AboutMeDAO::setDisableGetMe(bool disableGetMe)
{
    if (!disableGetMe)
        m_client->getMe();

    if (m_disableGetMe == disableGetMe)
        return;

    m_disableGetMe = disableGetMe;

    emit disableGetMeChanged(m_disableGetMe);
}
} //namespace tdlibQt
