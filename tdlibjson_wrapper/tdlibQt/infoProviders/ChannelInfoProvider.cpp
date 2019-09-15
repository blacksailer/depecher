#include "ChannelInfoProvider.hpp"
#include "tdlibQt/models/singletons/UsersModel.hpp"
#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/ParseObject.hpp"
namespace tdlibQt {
static const QString c_extra = QLatin1String("ChannelInfoProvider %1");

ChannelInfoProvider::ChannelInfoProvider(QObject *parent) : InfoProvider(parent)
{
    connect(m_tdlibJson, &TdlibJsonWrapper::supergroupFullInfoReceived,
            this, &ChannelInfoProvider::infoChanged);
    connect(m_tdlibJson, &TdlibJsonWrapper::updateSupergroup,
            this, &ChannelInfoProvider::supergroupChanged);
    connect(this, &ChannelInfoProvider::chatIdChanged,
            this, &ChannelInfoProvider::onChatIdChanged);
}

QString ChannelInfoProvider::name() const
{
    if (m_supergroup.data())
        return UsersModel::instance()->getChatTitle(chatId());
    return QString();
}

QString ChannelInfoProvider::link() const
{
    if (m_supergroup.data())
        return QString::fromStdString(m_supergroup->username_);
    return QString();
}

int ChannelInfoProvider::members() const
{
    if (m_supergroupFullInfo.data())
        return m_supergroupFullInfo->member_count_;
    return 0;
}

int ChannelInfoProvider::supergroupId() const
{
    return m_supergroupId;
}

QString ChannelInfoProvider::description() const
{
    if (m_supergroupFullInfo.data())
        return QString::fromStdString(m_supergroupFullInfo->description_);
    return QString();
}

QString ChannelInfoProvider::inviteLink() const
{
    if (m_supergroupFullInfo.data())
        return QString::fromStdString(m_supergroupFullInfo->invite_link_);
    return QString();
}

bool ChannelInfoProvider::canBeEdited() const
{
    if (m_supergroup.data())
        if (m_supergroup->status_->get_id() == chatMemberStatusAdministrator::ID)
            return static_cast<chatMemberStatusAdministrator *>(m_supergroup->status_.data())->can_be_edited_;
    return false;
}

bool ChannelInfoProvider::canPostMessages() const
{
    if (m_supergroup.data())
        if (m_supergroup->status_->get_id() == chatMemberStatusAdministrator::ID)
            return static_cast<chatMemberStatusAdministrator *>(m_supergroup->status_.data())->can_post_messages_;
    return false;
}

bool ChannelInfoProvider::canChangeInfo() const
{
    if (m_supergroup.data())
        if (m_supergroup->status_->get_id() == chatMemberStatusAdministrator::ID)
            return static_cast<chatMemberStatusAdministrator *>(m_supergroup->status_.data())->can_change_info_;
    return false;
}

bool ChannelInfoProvider::canEditMmessages() const
{
    if (m_supergroup.data())
        if (m_supergroup->status_->get_id() == chatMemberStatusAdministrator::ID)
            return static_cast<chatMemberStatusAdministrator *>(m_supergroup->status_.data())->can_edit_messages_;
    return false;
}

bool ChannelInfoProvider::canDeleteMessages() const
{
    if (m_supergroup.data())
        if (m_supergroup->status_->get_id() == chatMemberStatusAdministrator::ID)
            return static_cast<chatMemberStatusAdministrator *>(m_supergroup->status_.data())->can_delete_messages_;
    return false;
}

bool ChannelInfoProvider::canInviteUsers() const
{
    if (m_supergroup.data())
        if (m_supergroup->status_->get_id() == chatMemberStatusAdministrator::ID)
            return static_cast<chatMemberStatusAdministrator *>(m_supergroup->status_.data())->can_invite_users_;
    return false;
}

bool ChannelInfoProvider::canPromoteMembers() const
{
    if (m_supergroup.data())
        if (m_supergroup->status_->get_id() == chatMemberStatusAdministrator::ID)
            return static_cast<chatMemberStatusAdministrator *>(m_supergroup->status_.data())->can_promote_members_;
    return false;
}

bool ChannelInfoProvider::isMember() const
{
    if (m_supergroup.data()) {
        switch (m_supergroup->status_->get_id()) {
        case chatMemberStatusCreator::ID:
            return static_cast<chatMemberStatusCreator *>(m_supergroup->status_.data())->is_member_;
            break;
        case chatMemberStatusRestricted::ID:
            return static_cast<chatMemberStatusRestricted *>(m_supergroup->status_.data())->is_member_;
            break;
        case chatMemberStatusMember::ID:
            return true;
            break;
        case chatMemberStatusBanned::ID:
            return true;
            break;
        case chatMemberStatusLeft::ID:
            return false;
            break;
        default:
            return false;
            break;
        }
    }
    return false;
}

bool ChannelInfoProvider::canRestrictMembers() const
{
    if (m_supergroup.data())
        if (m_supergroup->status_->get_id() == chatMemberStatusAdministrator::ID)
            return static_cast<chatMemberStatusAdministrator *>(m_supergroup->status_.data())->can_restrict_members_;
    return false;

}

bool ChannelInfoProvider::canSendMediaMessages() const
{
    if (m_supergroup.data())
        if (m_supergroup->status_->get_id() == chatMemberStatusRestricted::ID)
            return static_cast<chatMemberStatusRestricted *>(m_supergroup->status_.data())->can_send_media_messages_;
    return false;
}

bool ChannelInfoProvider::canSendMessages() const
{
    if (m_supergroup.data())
        if (m_supergroup->status_->get_id() == chatMemberStatusRestricted::ID)
            return static_cast<chatMemberStatusRestricted *>(m_supergroup->status_.data())->can_send_messages_;
    return false;
}

bool ChannelInfoProvider::canSendOtherMessages() const
{
    if (m_supergroup.data())
        if (m_supergroup->status_->get_id() == chatMemberStatusRestricted::ID)
            return static_cast<chatMemberStatusRestricted *>(m_supergroup->status_.data())->can_send_other_messages_;
    return false;
}

bool ChannelInfoProvider::canAddWebPagePreviews() const
{
    if (m_supergroup.data())
        if (m_supergroup->status_->get_id() == chatMemberStatusRestricted::ID)
            return static_cast<chatMemberStatusRestricted *>(m_supergroup->status_.data())->can_add_web_page_previews_;
    return false;
}

int ChannelInfoProvider::untilDate() const
{
    if (m_supergroup.data()) {
        switch (m_supergroup->status_->get_id()) {
        case chatMemberStatusRestricted::ID:
            return static_cast<chatMemberStatusRestricted *>(m_supergroup->status_.data())->restricted_until_date_;
            break;
        case chatMemberStatusBanned::ID:
            return static_cast<chatMemberStatusBanned *>(m_supergroup->status_.data())->banned_until_date_;

            break;
        default:
            return 0;
            break;

        }
    }
    return 0;
}

ChannelInfoProvider::MemberStatus ChannelInfoProvider::status() const
{
    if (m_supergroup.data()) {
        switch (m_supergroup->status_->get_id()) {
        case chatMemberStatusCreator::ID:
            return Creator;
            break;
        case chatMemberStatusAdministrator::ID:
            return Administrator;
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
    return Left;
}

bool ChannelInfoProvider::canPinMessages() const
{
    if (m_supergroup.data())
        if (m_supergroup->status_->get_id() == chatMemberStatusAdministrator::ID)
            return static_cast<chatMemberStatusAdministrator *>(m_supergroup->status_.data())->can_pin_messages_;
    return false;
}

void ChannelInfoProvider::infoChanged(const QJsonObject &obj)
{
    if (obj["@extra"].toString() == c_extra.arg(QString::number(m_supergroupId))) {
        m_supergroupFullInfo = ParseObject::parseSupergroupFullInfo(obj);
        emitAll();
    }
}

void ChannelInfoProvider::supergroupChanged(const QJsonObject &obj)
{
    if (obj["supergroup"].toObject()["id"].toInt() == m_supergroupId) {
        m_supergroup = ParseObject::parseSupergroup(obj["supergroup"].toObject());
        emitGroup();
    }
}

void ChannelInfoProvider::onChatIdChanged(const double chatId)
{
    Q_UNUSED(chatId)
    if (m_chat.data())
        setSupergroupId(static_cast<chatTypeSupergroup *>(m_chat->type_.data())->supergroup_id_);
}

void ChannelInfoProvider::emitAll()
{
    emit muteFor();
    emit avatarChanged();
    emitGroup();
    emitInfo();
}

void ChannelInfoProvider::emitGroup()
{
    emit nameChanged();
    emit linkChanged();
    emit membersChanged();
    emit canEditMmessages();
    emit canDeleteMessages();
    emit canInviteUsers();
    emit canPinMessages();
    emit canPostMessages();
    emit canPromoteMembers();
    emit isMemberChanged();
    emit canRestrictMembers();
    emit canSendMediaMessages();
    emit canSendMessages();
    emit canSendOtherMessages();
    emit canAddWebPagePreviews();
}

void ChannelInfoProvider::emitInfo()
{
    emit descriptionChanged();
    emit inviteLinkChanged();

}


void ChannelInfoProvider::setSupergroupId(int supergroupId)
{
    if (m_supergroupId == supergroupId)
        return;

    m_supergroupId = supergroupId;
    m_supergroup = UsersModel::instance()->getSupergroup(m_supergroupId);
    m_tdlibJson->getSupergroupFullInfo(m_supergroupId, c_extra.arg(QString::number(m_supergroupId)));
    emitAll();
    emit supergroupIdChanged(m_supergroupId);
}



} // namespace tdlibQt
