#include "ChatMembersModel.hpp"
#include "tdlibQt/models/singletons/UsersModel.hpp"
#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/ParseObject.hpp"
namespace tdlibQt {
static const QString c_extra = QLatin1String("ChatMembersModel");

ChatMembersModel::ChatMembersModel(QObject *parent) : QAbstractListModel(parent)
{
    m_supergroupMode = true;
    m_tdlibJson = TdlibJsonWrapper::instance();
    connect(m_tdlibJson, &TdlibJsonWrapper::fileReceived,
            this, &ChatMembersModel::processFile);
    connect(this, &ChatMembersModel::downloadAvatar,
            this, &ChatMembersModel::getFile);
    connect(m_tdlibJson, &TdlibJsonWrapper::updateUserStatusReceived,
            this, &ChatMembersModel::userStatusReceived);


}

ChatMembersModel::ChatMembersModel(QObject *parent, bool mode) : QAbstractListModel(parent),
    m_supergroupMode(mode)
{
    m_tdlibJson = TdlibJsonWrapper::instance();
    connect(m_tdlibJson, &TdlibJsonWrapper::fileReceived,
            this, &ChatMembersModel::processFile);
    connect(this, &ChatMembersModel::downloadAvatar,
            this, &ChatMembersModel::getFile);
    connect(m_tdlibJson, &TdlibJsonWrapper::updateUserStatusReceived,
            this, &ChatMembersModel::userStatusReceived);

}

void ChatMembersModel::setMembers(const std::vector<QSharedPointer<chatMember> > &members)
{
    beginInsertRows(QModelIndex(), 0, members.size() - 1);
    for (int i = 0; i < members.size(); ++i)
        m_members.push_back(members[i]);
    qDebug() << m_members.size();

    endInsertRows();
}

int ChatMembersModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_members.size();
}

QVariant ChatMembersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int rowIndex = index.row();
    if (rowIndex < 0 || rowIndex > rowCount(QModelIndex()))
        return QVariant();
    switch (role) {
    case AVATAR: {
        auto profilePhotoPtr = UsersModel::instance()->getUserPhoto(m_members[rowIndex]->user_id_);
        if (profilePhotoPtr.data()) {
            if (profilePhotoPtr->small_.data()) {
                if (profilePhotoPtr->small_->local_->is_downloading_completed_)
                    return QString::fromStdString(profilePhotoPtr->small_->local_->path_);
                else {
                    int fileId = profilePhotoPtr->small_->id_;
                    emit downloadAvatar(fileId, rowIndex, 12);

                }
            }
        }
        return QVariant();
    }
    break;
    case USER_ID:
        return  QString::number(m_members[rowIndex]->user_id_);
    case STATUS: {
        switch (m_members[rowIndex]->status_->get_id()) {
        case chatMemberStatusCreator::ID:
            return Creator;
            break;
        case chatMemberStatusRestricted::ID:
            return Restricted;
            break;
        case chatMemberStatusMember::ID:
            return Member;
            break;
        case chatMemberStatusBanned::ID:
            return Banned;
            break;
        case chatMemberStatusLeft::ID:
            return Left;
            break;
        default:
            return Left;
            break;
        }
    }
    case NAME:
        return  UsersModel::instance()->getUserFullName(m_members[rowIndex]->user_id_);
    case ONLINE_STATUS:
        return  UsersModel::getUserStatusAsString(UsersModel::instance()->getUserStatus(m_members[rowIndex]->user_id_));
    }
}

void ChatMembersModel::processFile(const QJsonObject &fileObject)
{
    if (fileObject["@extra"].toString() == c_extra) {
        auto file = ParseObject::parseFile(fileObject);

        if (file->local_->is_downloading_completed_) {
            int rowIndex = avatarPhotoMap[file->id_];
            avatarPhotoMap.remove(file->id_);
            UsersModel::instance()->setSmallAvatar(m_members[rowIndex]->user_id_, file);
            QVector<int> avatarRole;
            avatarRole.append(AVATAR);
            emit dataChanged(index(rowIndex), QModelIndex(), avatarRole);
        }
    }
}

void ChatMembersModel::getFile(const int fileId, const int rowIndex, const int priority)
{
    if (!avatarPhotoMap.contains(fileId)) {
        m_tdlibJson->downloadFile(fileId, priority, c_extra);
        avatarPhotoMap[fileId] = rowIndex;
    }
}

void ChatMembersModel::userStatusReceived(const QJsonObject &userStatusObject)
{
    int user_id = userStatusObject["user_id"].toInt();
    for (int i = 0; i < m_members.size(); ++i) {
        if (m_members[i]->user_id_ == user_id) {
            QVector<int> roles;
            roles.append(ONLINE_STATUS);
            emit dataChanged(index(i), QModelIndex(), roles);
            break;
        }
    }
}

void ChatMembersModel::setSupergroupMode(bool supergroupMode)
{
    if (m_supergroupMode == supergroupMode)
        return;

    m_supergroupMode = supergroupMode;
    emit supergroupModeChanged(m_supergroupMode);
}

QHash<int, QByteArray> ChatMembersModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames[USER_ID] = "user_id";
    roleNames[AVATAR] = "avatar";
    roleNames[NAME] = "name";
    roleNames[STATUS] = "status";
    roleNames[ONLINE_STATUS] = "online_status";

    return roleNames;

}

bool ChatMembersModel::supergroupMode() const
{
    return m_supergroupMode;
}
} // namespace tdlibQt
