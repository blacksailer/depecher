#include "AuthenticationHandler.hpp"
#include "../TdlibJsonWrapper.hpp"


tdlibQt::AuthenticationHandler::AuthenticationHandler(QObject *parent) :
    QObject(parent),
    m_client(TdlibJsonWrapper::instance())
{
    connect(m_client, &TdlibJsonWrapper::newAuthorizationState,
            this, &AuthenticationHandler::setAuthorizationState);
    connect(m_client, &TdlibJsonWrapper::authorizationStateChanged,
            this, &AuthenticationHandler::setCurrentAuthorizationState);
    m_authorizationState = QSharedPointer<AuthorizationState>(nullptr);

}

tdlibQt::Enums::AuthorizationState tdlibQt::AuthenticationHandler::authorizationState() const
{
    return m_currentAuthorizationState;
}

QString tdlibQt::AuthenticationHandler::getType() const
{
    return getCurrentCodeType();
}

void tdlibQt::AuthenticationHandler::setCurrentAuthorizationState(tdlibQt::Enums::AuthorizationState
                                                                  currentAuthorizationState)
{
    if (m_currentAuthorizationState == currentAuthorizationState)
        return;

    m_currentAuthorizationState = currentAuthorizationState;
    emit authorizationStateChanged(currentAuthorizationState);
}

void tdlibQt::AuthenticationHandler::setEncryptionKey(const QString &passwd)
{
    m_client->setEncryptionKey(passwd);

}

bool tdlibQt::AuthenticationHandler::isUserRegistered() const
{
    if (m_authorizationState.data()) {

        if (m_authorizationState->get_id() == authorizationStateWaitCode::ID) {
            auto waitCode = static_cast<authorizationStateWaitCode *>(m_authorizationState.data());
            return waitCode->is_registered_;
        }
    }
    return false;
}

QString tdlibQt::AuthenticationHandler::getCurrentCodeType() const
{
    if (m_authorizationState.data()) {
        if (m_authorizationState->get_id() == authorizationStateWaitCode::ID) {
            auto waitCode = static_cast<authorizationStateWaitCode *>(m_authorizationState.data());
            auto codeInfo = static_cast<authenticationCodeInfo *>(waitCode->code_info_.data());
            auto codeType = static_cast<AuthenticationCodeType *>(codeInfo->type_.data());
            if (codeType->get_id() == authenticationCodeTypeSms::ID)
                return "SMS";
            if (codeType->get_id() == authenticationCodeTypeCall::ID)
                return "Call";
            if (codeType->get_id() == authenticationCodeTypeFlashCall::ID)
                return "Flash call";
            if (codeType->get_id() == authenticationCodeTypeTelegramMessage::ID)
                return "Telegram";
        }
    }
    return "";
}

void tdlibQt::AuthenticationHandler::setAuthorizationState(const
                                                           QSharedPointer<tdlibQt::AuthorizationState> &authorizationState)
{
    m_authorizationState = authorizationState;
    emit getTypeChanged(getCurrentCodeType());
    emit isUserRegisteredChanged(isUserRegistered());
}
