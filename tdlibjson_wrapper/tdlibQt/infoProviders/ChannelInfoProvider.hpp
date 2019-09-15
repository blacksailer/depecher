#ifndef CHANNELINFOPROVIDER_HPP
#define CHANNELINFOPROVIDER_HPP

#include <QObject>
#include "InfoProvider.hpp"
#include "tdlibQt/items/TdApi.hpp"
namespace tdlibQt {

class ChannelInfoProvider : public InfoProvider
{
    Q_OBJECT
    Q_PROPERTY(int supergroupId READ supergroupId WRITE setSupergroupId NOTIFY supergroupIdChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString link READ link NOTIFY linkChanged)
    Q_PROPERTY(QString inviteLink READ inviteLink NOTIFY inviteLinkChanged)

    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    Q_PROPERTY(int members READ members NOTIFY membersChanged)
    Q_PROPERTY(MemberStatus status READ status NOTIFY statusChanged)
    Q_PROPERTY(bool canBeEdited READ canBeEdited  NOTIFY canBeEditedChanged)
    Q_PROPERTY(bool canChangeInfo READ canChangeInfo  NOTIFY canChangeInfoChanged)
    Q_PROPERTY(bool canPostMessages READ canPostMessages NOTIFY canPostMessagesChanged)
    Q_PROPERTY(bool canEditMmessages READ canEditMmessages  NOTIFY canEditMmessagesChanged)
    Q_PROPERTY(bool canDeleteMessages READ canDeleteMessages  NOTIFY canDeleteMessagesChanged)
    Q_PROPERTY(bool canInviteUsers READ canInviteUsers NOTIFY canInviteUsersChanged)
    Q_PROPERTY(bool canRestrictMembers READ canRestrictMembers  NOTIFY canRestrictMembersChanged)
    Q_PROPERTY(bool canPinMessages READ canPinMessages  NOTIFY canPinMessagesChanged)
    Q_PROPERTY(bool canPromoteMembers READ canPromoteMembers  NOTIFY canPromoteMembersChanged)
    //Restricted
    Q_PROPERTY(bool isMember READ isMember  NOTIFY isMemberChanged)
    Q_PROPERTY(bool canSendMediaMessages READ canSendMediaMessages NOTIFY canSendMediaMessagesChanged)
    Q_PROPERTY(bool canSendMessages READ canSendMessages  NOTIFY canSendMessagesChanged)
    Q_PROPERTY(bool canSendOtherMessages READ canSendOtherMessages NOTIFY canSendOtherMessagesChanged)
    Q_PROPERTY(bool canAddWebPagePreviews READ canAddWebPagePreviews NOTIFY canAddWebPagePreviewsChanged)
    Q_PROPERTY(int untilDate READ untilDate  NOTIFY untilDateChanged)
    // Banned
    // description
    // members
public:
    explicit ChannelInfoProvider(QObject *parent = nullptr);
    QString name() const;
    QString link() const;

    int members() const;

    int supergroupId() const;
    QString description() const;

    QString inviteLink() const;

    enum MemberStatus {
        Administrator,
        Restricted,
        Banned,
        Creator,
        Left,
        Member
    };
    Q_ENUM(MemberStatus)
    bool canBeEdited() const;
    bool canChangeInfo() const;
    bool canEditMmessages() const;
    bool canDeleteMessages() const;
    bool canInviteUsers() const;
    bool canPinMessages() const;
    bool canPostMessages() const;
    bool canPromoteMembers() const;
    bool isMember() const;
    bool canRestrictMembers() const;
    bool canSendMediaMessages() const;
    bool canSendMessages() const;
    bool canSendOtherMessages() const;
    bool canAddWebPagePreviews() const;
    int untilDate() const;
    MemberStatus status() const;

signals:
    void nameChanged();
    void linkChanged();
    void membersChanged();
    void supergroupIdChanged(int supergroupId);
    void descriptionChanged();
    void inviteLinkChanged();
    void canBeEditedChanged();
    void canChangeInfoChanged();
    void canPostMessagesChanged();
    void canEditMmessagesChanged();
    void canDeleteMessagesChanged();
    void canInviteUsersChanged();
    void canPinMessagesChanged();
    void canPromoteMembersChanged();
    void isMemberChanged();
    void canSendMediaMessagesChanged();
    void canSendMessagesChanged();
    void canSendOtherMessagesChanged();
    void canAddWebPagePreviewsChanged();
    void untilDateChanged();
    void canRestrictMembersChanged();
    void statusChanged(MemberStatus status);

private slots:
    void infoChanged(const QJsonObject &obj);
    void supergroupChanged(const QJsonObject &obj);

    void onChatIdChanged(const double chatId);
public slots:
    void setSupergroupId(int supergroupId);

private:
    void emitAll();
    void emitGroup();
    void emitInfo();
    QSharedPointer<supergroup> m_supergroup;
    QSharedPointer<supergroupFullInfo> m_supergroupFullInfo;

    int m_supergroupId;
};
} // namespace tdlibQt

#endif // CHANNELINFOPROVIDER_HPP
