#ifndef CONTACTSMODEL_HPP
#define CONTACTSMODEL_HPP

#include <QAbstractListModel>
#include <QJsonObject>
#include "tdlibQt/items/TdApi.hpp"
namespace tdlibQt {

class TdlibJsonWrapper;

class ContactsModel : public QAbstractListModel
{
    Q_OBJECT

    QList<QSharedPointer<user>> m_contacts;
    QList<int> m_contactsIds;
    TdlibJsonWrapper *m_clientJson;
    QTimer m_statusTimer;

public:
    ContactsModel(QObject *parent = 0);
    enum class Status {
        userStatusEmpty,
        userStatusOnline,//int  expires_;
        userStatusOffline,//int was_online_;
        userStatusRecently,
        userStatusLastWeek,
        userStatusLastMonth
    };
    enum DataTypes {
        USER_ID,
        FIRST_NAME,
        LAST_NAME,
        USER_NAME,
        PHONE_NUMBER,
        STATUS,
        PHOTO,
        IS_VERIFIED
    };
    // QAbstractItemModel interface
    void appendContact(const QSharedPointer<user> &usr);
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
signals:
    void chatIdReceived(QString chatId);
private slots:
    void onChatReceived(const QJsonObject &obj);
public slots:
    void parseContact(const QJsonObject &userObject);
    void addContactIds(const QJsonObject &usersObject);
    void updateContactPhoto(const QJsonObject &fileObject);
    void updateStatus(const QJsonObject &statusObject);
    QString getChatId(const int userId);
};


} // namespace tdlibQt

Q_DECLARE_METATYPE(tdlibQt::ContactsModel::Status)
#endif // CONTACTSMODEL_HPP
