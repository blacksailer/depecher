#ifndef AUTHENTICATIONHANDLER_HPP
#define AUTHENTICATIONHANDLER_HPP

#include <QObject>
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
    Q_PROPERTY(bool isUserRegistered READ getIsUserRegistered NOTIFY isUserRegisteredChanged)
    tdlibQt::Enums::AuthorizationState m_currentAuthorizationState;
    TdlibJsonWrapper *m_client;

    bool isUserRegistered() const;
    QString getCurrentCodeType() const;

public:
    explicit AuthenticationHandler(QObject *parent = nullptr);
    tdlibQt::Enums::AuthorizationState authorizationState() const;

    QString getType() const;

    bool getIsUserRegistered() const
    {
        return isUserRegistered();
    }

public slots:

    void setCurrentAuthorizationState(tdlibQt::Enums::AuthorizationState currentAuthorizationState);
    void setEncryptionKey(const QString &passwd = "abcd");

signals:
    void authorizationStateChanged(tdlibQt::Enums::AuthorizationState currentAuthorizationState);

    void getTypeChanged(QString getType);

    void isUserRegisteredChanged(bool isUserRegistered);

private slots:
    void setAuthorizationState(const QSharedPointer<AuthorizationState> &authorizationState);
};
} //namespace tdlibQt
#endif // AUTHENTICATIONHANDLER_HPP
