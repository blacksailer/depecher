#include "UsernameResolver.hpp"
#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/ParseObject.hpp"
namespace tdlibQt {
static const QString c_extra = QLatin1String("UsernameResolver");

UsernameResolver::UsernameResolver(QObject *parent) : QObject(parent)
{
    m_tdlibJson = TdlibJsonWrapper::instance();
    connect(m_tdlibJson, &TdlibJsonWrapper::chatReceived,
            this, &UsernameResolver::chatReceived);
    connect(m_tdlibJson, &TdlibJsonWrapper::errorReceived,
            this, &UsernameResolver::errorReceived);
}

void UsernameResolver::setResolvedId(double resolvedId)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_resolvedId, resolvedId))
        return;

    m_resolvedId = resolvedId;
    emit resolvedIdChanged(m_resolvedId);
}

void UsernameResolver::setResolvedChatId(double resolvedChatId)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_resolvedChatId, resolvedChatId))
        return;

    m_resolvedChatId = resolvedChatId;
    emit resolvedChatIdChanged(m_resolvedChatId);
}

void UsernameResolver::setUsername(QString username)
{
    if (m_username == username)
        return;

    m_username = username;
    m_tdlibJson->searchPublicChat(m_username, c_extra);
    emit usernameChanged(m_username);
}
void UsernameResolver::chatReceived(const QJsonObject &chatObject)
{
    if (chatObject["@extra"].toString() == c_extra) {
        auto chat = ParseObject::parseChat(chatObject);
        setResolvedChatId(chat->id_);
        switch (chat->type_->get_id()) {
        case chatTypePrivate::ID:
            setChatType(tdlibQt::Enums::ChatType::Private);
            setResolvedId(static_cast<chatTypePrivate *>(chat->type_.data())->user_id_);
            break;
        case chatTypeBasicGroup::ID:
            setChatType(tdlibQt::Enums::ChatType::BasicGroup);
            setResolvedId(static_cast<chatTypeBasicGroup *>(chat->type_.data())->basic_group_id_);
            break;
        case chatTypeSupergroup::ID:
            setResolvedId(static_cast<chatTypeSupergroup *>(chat->type_.data())->supergroup_id_);
            if (static_cast<chatTypeSupergroup *>(chat->type_.data())->is_channel_)
                setChatType(tdlibQt::Enums::ChatType::Channel);
            else
                setChatType(tdlibQt::Enums::ChatType::Supergroup);
            break;
        case chatTypeSecret::ID:
            setResolvedId(static_cast<chatTypeSecret *>(chat->type_.data())->secret_chat_id_);
            setChatType(tdlibQt::Enums::ChatType::Secret);
        default:
            break;
        }

    }
}
void UsernameResolver::errorReceived(const QJsonObject &errorObject)
{
    if (errorObject["@extra"].toString() == c_extra) {
        if (errorObject["code"].toInt() == 400)
            setError(tr("Username %1 not found").arg(username()));
        else
            setError(errorObject["message"].toString());
    }
}
} // namespace tdlibQt
