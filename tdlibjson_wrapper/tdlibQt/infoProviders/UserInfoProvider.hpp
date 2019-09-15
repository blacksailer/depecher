#ifndef USERINFOPROVIDER_HPP
#define USERINFOPROVIDER_HPP

#include <QObject>
#include <QJsonObject>
#include "InfoProvider.hpp"
#include "tdlibQt/items/TdApi.hpp"
namespace tdlibQt {
class TdlibJsonWrapper;
class UserInfoProvider : public InfoProvider
{
    Q_OBJECT
    Q_PROPERTY(int userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString firstName READ firstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName NOTIFY lastNameChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString username READ username NOTIFY usernameChanged)
    Q_PROPERTY(QString bio READ bio NOTIFY bioChanged)
    Q_PROPERTY(QString phoneNumber READ phoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(linkState incomingLink READ incomingLink NOTIFY incomingLinkChanged)
    Q_PROPERTY(linkState outgoingLink READ outgoingLink  NOTIFY outcomingLinkChanged)
    Q_PROPERTY(int groupCount READ groupCount WRITE setGroupCount NOTIFY groupCountChanged)

public:
    enum class linkState {
        NONE,
        KNOWS_PHONE_NUMBER,
        IS_CONTACT
    };
    Q_ENUM(linkState)
private:

    QSharedPointer<user> m_userInfo;
    QSharedPointer<userFullInfo> m_userFullInfo;
    int m_userId = 0;

    linkState m_incomingLink;

    linkState m_outcomingLink;

    void emitAll();

    int m_groupCount  = 0;

    QString m_bio;

public:
    explicit UserInfoProvider(QObject *parent = nullptr);
    int userId() const;

    QString firstName() const;

    QString lastName() const;

    QString avatar() const override;

    QString username() const;

    QString bio() const
    {
        return m_bio;
    }

    QString status() const;

    linkState incomingLink() const;

    linkState outgoingLink() const;


    QString phoneNumber() const;

    int groupCount() const
    {
        return m_groupCount;
    }

signals:
    void userIdChanged(int userId);

    void firstNameChanged();

    void lastNameChanged();


    void statusChanged();

    void incomingLinkChanged();

    void outcomingLinkChanged();

    void phoneNumberChanged();

    void usernameChanged();

    void bioChanged();

    void groupCountChanged(int groupCount);
    void chatIdReceived(const QString &chatId);
private slots:
    void updateUserReceived(const QJsonObject &userObject);
    void userFullInfoReceived(const QJsonObject &userFullInfoObject);
    void errorReceived(const QJsonObject &errorObject);
    void setGroupCount(int groupCount);
    void setBio(const QString &bio);
    void processFile(const QJsonObject &fileObject);
    void onChatReceived(const QJsonObject &userObject);
public slots:
    void setUserId(int userId);
    QString getChatId();
};
} // namespace tdlibQt
Q_DECLARE_METATYPE(tdlibQt::UserInfoProvider::linkState)
#endif // USERINFOPROVIDER_HPP
