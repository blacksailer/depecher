#include "ContactsModel.hpp"
#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/ParseObject.hpp"
#include "singletons/UsersModel.hpp"
#include <QDebug>
namespace tdlibQt {


ContactsModel::ContactsModel(QObject *parent): QAbstractListModel(parent),
    m_clientJson(TdlibJsonWrapper::instance())
{
    m_clientJson->getContacts();

    connect(m_clientJson, &TdlibJsonWrapper::usersReceived,
            this, &ContactsModel::addContactIds);
    connect(m_clientJson, &TdlibJsonWrapper::userReceived,
            this, &ContactsModel::parseContact);
    connect(m_clientJson, &TdlibJsonWrapper::chatReceived,
            this, &ContactsModel::onChatReceived);
    connect(m_clientJson, &TdlibJsonWrapper::fileReceived,
            this, &ContactsModel::updateContactPhoto);
    connect(m_clientJson, &TdlibJsonWrapper::updateUserStatusReceived,
            this, &ContactsModel::updateStatus);

    m_statusTimer.setInterval(1000 * 60);
    m_statusTimer.setSingleShot(false);
    connect(&m_statusTimer, &QTimer::timeout, [this]() {
        QVector<int> roles;
        roles.append(STATUS);
        emit dataChanged(index(0), index(m_contacts.size() - 1), roles);
    });
    m_statusTimer.start();
}


void ContactsModel::onChatReceived(const QJsonObject &obj)
{
    if (obj["@extra"].toString() == "ContactsModel createPrivateChat") {
        auto chatItem = ParseObject::parseChat(obj);
        emit chatIdReceived(QString::number(chatItem->id_));
    }
}
int ContactsModel::rowCount(const QModelIndex &parent) const
{
    return m_contacts.size();
}

QVariant ContactsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int rowIndex = index.row();
    if (rowIndex < 0 || rowIndex > rowCount(QModelIndex()))
        return QVariant();

    switch (role) {
    case USER_ID:
        return  QString::number(m_contacts[rowIndex]->id_);
    case FIRST_NAME:
        return  QString::fromStdString(m_contacts[rowIndex]->first_name_);
    case LAST_NAME:
        return  QString::fromStdString(m_contacts[rowIndex]->last_name_);
    case USER_NAME:
        return  QString::fromStdString(m_contacts[rowIndex]->username_);
    case PHONE_NUMBER:
        return  QString::fromStdString(m_contacts[rowIndex]->phone_number_);
    case STATUS:
        return UsersModel::getUserStatusAsString(m_contacts[rowIndex]->status_);

    case PHOTO:
        if (m_contacts[rowIndex]->profile_photo_.data() != nullptr) {
            if (m_contacts[rowIndex]->profile_photo_->small_.data() != nullptr)
                if (m_contacts[rowIndex]->profile_photo_->small_->local_->is_downloading_completed_)
                    return QString::fromStdString(m_contacts[rowIndex]->profile_photo_->small_->local_->path_);
                else {
                    int fileId = m_contacts[rowIndex]->profile_photo_->small_->id_;
                    m_clientJson->downloadFile(fileId, 12);
                    return QVariant();
                }
        }
    case IS_VERIFIED:
        return m_contacts[rowIndex]->is_verified_;

        break;
    default:
        break;
    }
}

QHash<int, QByteArray> ContactsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[USER_ID] = "user_id";
    roles[FIRST_NAME] = "first_name";
    roles[LAST_NAME] = "last_name";
    roles[USER_NAME] = "user_name";
    roles[PHONE_NUMBER] = "phone_number";
    roles[STATUS] = "status";
    roles[PHOTO] = "photo";
    roles[IS_VERIFIED] = "is_verified";

    return roles;
}



void ContactsModel::parseContact(const QJsonObject &userObject)
{
    if (userObject["@extra"].toString() == "fetchContact") {
        auto contactItem  = ParseObject::parseUser(userObject);
        appendContact(contactItem);
    }
}
void ContactsModel::appendContact(const QSharedPointer<user> &usr)
{
    beginInsertRows(QModelIndex(), m_contacts.size(), m_contacts.size());
    m_contacts.append(usr);
    endInsertRows();
}
void ContactsModel::addContactIds(const QJsonObject &usersObject)
{
    beginResetModel();
    m_contacts.clear();
    m_contactsIds.clear();
    foreach (auto item, usersObject["user_ids"].toArray()) {
        m_contactsIds.append(item.toInt());
        QSharedPointer<user> userItem = UsersModel::instance()->getUser(m_contactsIds.last());
        if (userItem.data() == nullptr)
            m_clientJson->getUser(m_contactsIds.last(), "fetchContact");
        else {
            appendContact(userItem);
        }
    }
    endResetModel();
}

void ContactsModel::updateContactPhoto(const QJsonObject &updateFileObject)
{
    if (updateFileObject["@type"].toString() == "updateFile") {
        auto fileObject = updateFileObject["file"].toObject();
        for (int i = 0; i < m_contacts.size(); i++) {
            if (m_contacts[i]->profile_photo_.data() != nullptr) {
                if (m_contacts[i]->profile_photo_->small_.data() != nullptr)
                    if (m_contacts[i]->profile_photo_->small_->id_ == fileObject["id"].toInt()) {
                        m_contacts[i]->profile_photo_->small_ = ParseObject::parseFile(fileObject);
                        QVector<int> photoRole;
                        photoRole.append(PHOTO);
                        emit dataChanged(this->createIndex(i, 0), this->createIndex(i, 0), photoRole);
                        break;
                    }
            }
        }
    }
}

void ContactsModel::updateStatus(const QJsonObject &statusObject)
{
    int userId = statusObject["user_id"].toInt();
    if (m_contactsIds.contains(userId)) {
        for (int i = 0; i < m_contacts.size(); i++) {
            if (m_contacts[i]->id_ == userId) {
                m_contacts[i]->status_ = ParseObject::parseUserStatus(statusObject["status"].toObject());
                QVector<int> roles;
                roles.append(STATUS);
                emit dataChanged(index(i), index(i), roles);
                break;
            }
        }
    }
}

QString ContactsModel::getChatId(const int userId)
{
    auto chat = UsersModel::instance()->getChat(userId);
    if (chat.data())
        return QString::number(chat->id_);
    else {
        m_clientJson->createPrivateChat(userId, false, "ContactsModel createPrivateChat");
        return QString::number(-1);
    }
}
} // namespace tdlibQt
