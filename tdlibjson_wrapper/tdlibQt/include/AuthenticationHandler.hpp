#ifndef AUTHENTICATIONHANDLER_HPP
#define AUTHENTICATIONHANDLER_HPP

#include <QObject>
#include <QVariant>
#include "../items/TdApi.hpp"
#include "../include/TdlibNamespace.hpp"
namespace tdlibQt {

class TdlibJsonWrapper;
class AuthenticationHandler : public QObject
{
    Q_OBJECT
    QSharedPointer<AuthorizationState> m_authorizationState;
    Q_PROPERTY(tdlibQt::Enums::AuthorizationState currentAuthorizationState READ authorizationState
               WRITE
               setCurrentAuthorizationState
               NOTIFY authorizationStateChanged)
    Q_PROPERTY(QString getType READ getType NOTIFY getTypeChanged)
    Q_PROPERTY(QString getHint READ getHint NOTIFY getHintChanged)
    Q_PROPERTY(QString emailPattern READ emailPattern NOTIFY emailPatternChanged)
    Q_PROPERTY(bool hasRecoveryEmail READ hasRecoveryEmail NOTIFY hasRecoveryEmailChanged)
    Q_PROPERTY(bool isUserRegistered READ getIsUserRegistered NOTIFY isUserRegisteredChanged)
    Q_PROPERTY(QVariantMap error READ error NOTIFY errorChanged)
    Q_PROPERTY(QVariantMap ok READ ok NOTIFY okChanged)

    tdlibQt::Enums::AuthorizationState m_currentAuthorizationState;
    TdlibJsonWrapper *m_client;

    bool isUserRegistered() const;
    QString getCurrentCodeType() const;


    QVariantMap m_error;

    QVariantMap m_ok;

public:
    explicit AuthenticationHandler(QObject *parent = nullptr);
    tdlibQt::Enums::AuthorizationState authorizationState() const;

    QString getType() const;

    bool getIsUserRegistered() const;

    QString getHint() const;

    QString emailPattern() const;

    bool hasRecoveryEmail() const;

    QVariantMap error() const
    {
        return m_error;
    }

    QVariantMap ok() const
    {
        return m_ok;
    }

public slots:

    void setCurrentAuthorizationState(tdlibQt::Enums::AuthorizationState currentAuthorizationState);
    void recoverPassword();
    void sendRecoveryCode(const QString &code);
    void setEncryptionKey(const QString &passwd = "abcd");
    void checkPassword(const QString &password);
signals:
    void authorizationStateChanged(tdlibQt::Enums::AuthorizationState currentAuthorizationState);

    void getTypeChanged(QString getType);

    void isUserRegisteredChanged(bool isUserRegistered);

    void getHintChanged(QString getHint);

    void emailPatternChanged(QString emailPattern);

    void hasRecoveryEmailChanged(bool hasRecoveryEmail);

    void errorChanged(QVariantMap error);

    void okChanged(QVariantMap ok);

private slots:
    void setAuthorizationState(const QSharedPointer<AuthorizationState> &authorizationState);
    void setError(const QJsonObject &errorObject);
    void setOk(const QJsonObject &okObject);
};
} //namespace tdlibQt
#endif // AUTHENTICATIONHANDLER_HPP
