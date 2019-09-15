#ifndef CHATMEMBERSMODEL_HPP
#define CHATMEMBERSMODEL_HPP

#include <QtCore>
#include "tdlibQt/items/TdApi.hpp"
namespace tdlibQt {
class TdlibJsonWrapper;
class ChatMembersModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool supergroupMode READ supergroupMode WRITE setSupergroupMode NOTIFY supergroupModeChanged)
    bool m_supergroupMode = false;

public:
    explicit ChatMembersModel(QObject *parent = nullptr);
    ChatMembersModel(QObject *parent = nullptr, bool mode = false);
    TdlibJsonWrapper *m_tdlibJson;
    QMap<int, int> avatarPhotoMap;
    std::vector<QSharedPointer<chatMember>> m_members;
    enum DataRoles {
        USER_ID,
        AVATAR,
        NAME,
        STATUS,
        ONLINE_STATUS
    };
    enum MemberStatus {
        Administrator,
        Restricted,
        Banned,
        Creator,
        Left,
        Member
    };
    void setMembers(const std::vector<QSharedPointer<chatMember> > &members);
    Q_ENUM(MemberStatus)
signals:

    void supergroupModeChanged(bool supergroupMode);
    void downloadAvatar(const int fileId, const int rowIndex, const int priority) const;
private slots:
    void processFile(const QJsonObject &fileObject);
    void getFile(const int fileId, const int rowIndex, const int priority);
    void userStatusReceived(const QJsonObject &userStatusObject);
public slots:

    // QAbstractItemModel interface
    void setSupergroupMode(bool supergroupMode);

public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool supergroupMode() const;
};
} // namespace tdlibQt

#endif // CHATMEMBERSMODEL_HPP
