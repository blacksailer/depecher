#ifndef ABOUTMEDAO_HPP
#define ABOUTMEDAO_HPP

#include <QObject>
namespace tdlibQt {
class TdlibJsonWrapper;
class AboutMeDAO : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QString fullName READ fullName WRITE setFullName NOTIFY fullNameChanged)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(QString photoPath READ photoPath WRITE setPhotoPath NOTIFY photoPathChanged)
    TdlibJsonWrapper *m_client;
    int m_profilePhotoId = 0;
    QString m_firstName;

    QString m_lastName;

    QString m_fullName;

    QString m_phoneNumber;

    QString m_photoPath;

    QString m_id;

    QString m_last_message_inbox_id;

    QString m_last_message_id;

public:
    explicit AboutMeDAO(QObject *parent = 0);

    QString firstName() const;

    QString lastName() const;

    QString fullName() const;

    QString phoneNumber() const;

    QString photoPath() const;

    QString id() const
    {
        return m_id;
    }

signals:

    void firstNameChanged(QString firstName);

    void lastNameChanged(QString lastName);

    void fullNameChanged(QString fullName);

    void phoneNumberChanged(QString phoneNumber);

    void photoPathChanged(QString photoPath);

    void idChanged(QString id);

public slots:
    void setInfo(const QJsonObject &meObject);
    void setFirstName(QString firstName);
    void setLastName(QString lastName);
    void setFullName(QString fullName);
    void setPhoneNumber(QString phoneNumber);
    void setPhotoPath(QString photoPath);
    void setId(QString id);

};
} //namespace tdlibQt

#endif // ABOUTMEDAO_HPP
