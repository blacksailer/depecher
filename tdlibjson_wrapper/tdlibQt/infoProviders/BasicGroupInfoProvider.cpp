#include "BasicGroupInfoProvider.hpp"
#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/ParseObject.hpp"
#include "tdlibQt/models/singletons/UsersModel.hpp"
#include "tdlibQt/models/ChatMembersModel.hpp"
namespace tdlibQt {

static const QString c_extra = QLatin1String("BasicGroupInfoProvider %1");

BasicGroupInfoProvider::BasicGroupInfoProvider(QObject *parent) : InfoProvider(parent)
{
    connect(m_tdlibJson, &TdlibJsonWrapper::basicGroupFullInfoReceived,
            this, &BasicGroupInfoProvider::basicGroupFullInfoReceived);
    connect(m_tdlibJson, &TdlibJsonWrapper::basicGroupReceived,
            this, &BasicGroupInfoProvider::basicGroupReceived);

    connect(m_tdlibJson, &TdlibJsonWrapper::updateBasicGroupReceived,
            this, &BasicGroupInfoProvider::updateBasicGroupReceived);
    connect(this, &BasicGroupInfoProvider::chatIdChanged,
            this, &BasicGroupInfoProvider::onChatIdChanged);
}

QString BasicGroupInfoProvider::inviteLink() const
{
    if (m_info.data())
        return QString::fromStdString(m_info->invite_link_);
    return QString();
}

QString BasicGroupInfoProvider::name() const
{
    if (m_group.data())
        return UsersModel::instance()->getChatTitle(chatId());
    return QString();
}

int BasicGroupInfoProvider::members() const
{
    if (m_group.data())
        return m_group->member_count_;
    return 0;
}

ChatMembersModel *BasicGroupInfoProvider::membersModel() const
{
    return m_membersModel;
}

void BasicGroupInfoProvider::setGroupId(int groupId)
{
    if (m_groupId == groupId)
        return;

    m_groupId = groupId;
    emit groupIdChanged(m_groupId);
    m_group = UsersModel::instance()->getGroup(m_groupId);
    if (m_group.data() == nullptr) {
        m_tdlibJson->getBasicGroup(m_groupId, c_extra.arg(QString::number(m_groupId)));
    } else {
        m_tdlibJson->getBasicGroupFullInfo(m_groupId, c_extra.arg(QString::number(m_groupId)));
        emitAll();
    }
}

void BasicGroupInfoProvider::basicGroupFullInfoReceived(const QJsonObject &obj)
{
    if (obj["@extra"].toString() == c_extra.arg(QString::number(m_groupId))) {

        m_info = ParseObject::parseBasicGroupFullInfo(obj);
        m_membersModel = new ChatMembersModel(this, false);
        m_membersModel->setMembers(m_info->members_);
        emitInfo();
    }
}

void BasicGroupInfoProvider::updateBasicGroupReceived(const QJsonObject &obj)
{
    if (obj["@extra"].toString() == c_extra.arg(QString::number(m_groupId))) {
        if (m_groupId == obj["basic_group"].toObject()["id"].toInt()) {
            m_group = ParseObject::parseBasicGroup(obj["basic_group"].toObject());
            emitGroup();
        }
    }
}

void BasicGroupInfoProvider::basicGroupReceived(const QJsonObject &obj)
{
    if (obj["@extra"].toString() == c_extra.arg(QString::number(m_groupId))) {
        if (m_groupId == obj["id"].toInt()) {
            m_group = ParseObject::parseBasicGroup(obj);
            emitGroup();
            m_tdlibJson->getBasicGroupFullInfo(m_groupId, c_extra.arg(QString::number(m_groupId)));
        }
    }
}

void BasicGroupInfoProvider::onChatIdChanged(const qint64 &chatId)
{
    Q_UNUSED(chatId)
    if (m_chat.data())
        setGroupId(static_cast<chatTypeBasicGroup *>(m_chat->type_.data())->basic_group_id_);
}

void BasicGroupInfoProvider::emitInfo()
{
    inviteLinkChanged();
    membersModelChanged();
}
void BasicGroupInfoProvider::emitGroup()
{
    nameChanged();
    membersChanged();
}
void BasicGroupInfoProvider::emitAll()
{
    emitGroup();
    emitInfo();
}
}//namespace tdlibQt
