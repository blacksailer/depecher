#ifndef TDLIBNAMESPACE_HPP
#define TDLIBNAMESPACE_HPP
#include <QObject>
namespace tdlibQt {

class Enums: public QObject
{
public:
    enum class AuthorizationState {
        AuthorizationStateWaitTdlibParameters,
        AuthorizationStateWaitEncryptionKey,
        AuthorizationStateWaitPhoneNumber,
        AuthorizationStateWaitCode,
        AuthorizationStateWaitPassword,
        AuthorizationStateLoggingOut,
        AuthorizationStateClosing,
        AuthorizationStateClosed,
        AuthorizationStateReady
    };
    enum class ConnectionState {
        ConnectionStateWaitingForNetwork,
        ConnectionStateConnecting,
        ConnectionStateConnectingToProxy,
        ConnectionStateUpdating,
        ConnectionStateReady
    };
    enum class ChatType {
        BasicGroup,
        Private,
        Secret,
        Supergroup,
        Channel
    };
    Q_ENUM(AuthorizationState)
    Q_ENUM(ConnectionState)
    Q_ENUM(ChatType)

    Q_OBJECT

};
}
Q_DECLARE_METATYPE(tdlibQt::Enums::AuthorizationState)
Q_DECLARE_METATYPE(tdlibQt::Enums::ConnectionState)
Q_DECLARE_METATYPE(tdlibQt::Enums::ChatType)

Q_DECLARE_METATYPE(Qt::ApplicationState)

#endif // TDLIBNAMESPACE_HPP
