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

    enum class FileType {
        Photo,
        Video,
        Document,
        Animation,
        Sticker
    };
    enum class MessageState {
        Sending_Failed,
        Sending_Pending,
        Sending_Not_Read,
        Sending_Read
    };
    Q_ENUM(MessageState)
    Q_ENUM(FileType)
    Q_ENUM(AuthorizationState)
    Q_ENUM(ConnectionState)
    Q_ENUM(ChatType)

    Q_OBJECT

};
}
Q_DECLARE_METATYPE(tdlibQt::Enums::AuthorizationState)
Q_DECLARE_METATYPE(tdlibQt::Enums::ConnectionState)
Q_DECLARE_METATYPE(tdlibQt::Enums::ChatType)
Q_DECLARE_METATYPE(tdlibQt::Enums::MessageState)

Q_DECLARE_METATYPE(Qt::ApplicationState)

#endif // TDLIBNAMESPACE_HPP
