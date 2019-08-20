#ifndef BASICGROUPINFOPROVIDER_HPP
#define BASICGROUPINFOPROVIDER_HPP

#include <QObject>
#include "InfoProvider.hpp"
#include <QJsonObject>
#include "tdlibQt/items/TdApi.hpp"

namespace tdlibQt {
class ChatMembersModel;
class BasicGroupInfoProvider : public InfoProvider
{
    Q_OBJECT
    Q_PROPERTY(int groupId READ groupId WRITE setGroupId NOTIFY groupIdChanged)
    Q_PROPERTY(QString inviteLink READ inviteLink NOTIFY inviteLinkChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(int members READ members NOTIFY membersChanged)
    Q_PROPERTY(ChatMembersModel *membersModel READ membersModel NOTIFY membersModelChanged)
    QSharedPointer<basicGroup> m_group;
    QSharedPointer<basicGroupFullInfo> m_info;

    void emitInfo();
    void emitGroup();
    void emitAll();

    int m_groupId  = 0;


    ChatMembersModel *m_membersModel = nullptr;

public:
    explicit BasicGroupInfoProvider(QObject *parent = nullptr);

    int groupId() const
    {
        return m_groupId;
    }

    QString inviteLink() const;

    QString name() const;

    int members() const;

    ChatMembersModel *membersModel() const;

public slots:
    void setGroupId(int groupId);

signals:

    void groupIdChanged(int groupId);

    void inviteLinkChanged();

    void nameChanged();

    void membersChanged();
    void membersModelChanged();
private slots:
    void basicGroupFullInfoReceived(const QJsonObject &obj);
    void updateBasicGroupReceived(const QJsonObject &obj);
    void basicGroupReceived(const QJsonObject &obj);

    void onChatIdChanged(const qint64 &chatId);

};
}//namespace tdlibQt

#endif // BASICGROUPINFOPROVIDER_HPP
