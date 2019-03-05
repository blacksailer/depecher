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

    connect(m_client, &TdlibJsonWrapper::errorReceived,
            this, &AuthenticationHandler::setError);
    connect(m_client, &TdlibJsonWrapper::okReceived,
            this, &AuthenticationHandler::setOk);

    m_authorizationState = QSharedPointer<AuthorizationState>(nullptr);
    if(m_client->authorizationState() == tdlibQt::Enums::AuthorizationState::AuthorizationStateWaitEncryptionKey)
        m_client->setEncryptionKey();

}

tdlibQt::Enums::AuthorizationState tdlibQt::AuthenticationHandler::authorizationState() const
{
    return m_currentAuthorizationState;
}

QString tdlibQt::AuthenticationHandler::getType() const
{
    return getCurrentCodeType();
}

bool tdlibQt::AuthenticationHandler::getIsUserRegistered() const
{
    return isUserRegistered();
}

QString tdlibQt::AuthenticationHandler::getHint() const
{
    if (m_authorizationState.data()) {

        if (m_authorizationState->get_id() == authorizationStateWaitPassword::ID) {
            auto waitCode = static_cast<authorizationStateWaitPassword *>(m_authorizationState.data());
            return QString::fromStdString(waitCode->password_hint_);
        }
    }
    return "";
}

QString tdlibQt::AuthenticationHandler::emailPattern() const
{
    if (m_authorizationState.data()) {

        if (m_authorizationState->get_id() == authorizationStateWaitPassword::ID) {
            auto waitCode = static_cast<authorizationStateWaitPassword *>(m_authorizationState.data());
            return QString::fromStdString(waitCode->recovery_email_address_pattern_);
        }
    }
    return "";
}

bool tdlibQt::AuthenticationHandler::hasRecoveryEmail() const
{
    if (m_authorizationState.data()) {

        if (m_authorizationState->get_id() == authorizationStateWaitPassword::ID) {
            auto waitCode = static_cast<authorizationStateWaitPassword *>(m_authorizationState.data());
            return waitCode->has_recovery_email_address_;
        }
    }
    return false;
}

void tdlibQt::AuthenticationHandler::setCurrentAuthorizationState(tdlibQt::Enums::AuthorizationState
                                                                  currentAuthorizationState)
{
    if (m_currentAuthorizationState == currentAuthorizationState)
        return;

    m_currentAuthorizationState = currentAuthorizationState;
    emit authorizationStateChanged(currentAuthorizationState);
}

void tdlibQt::AuthenticationHandler::recoverPassword()
{
    m_client->requestAuthenticationPasswordRecovery();
}

void tdlibQt::AuthenticationHandler::sendRecoveryCode(const QString &code)
{
    m_client->recoverAuthenticationPassword(code);
}


void tdlibQt::AuthenticationHandler::setEncryptionKey(const QString &passwd)
{
    m_client->setEncryptionKey(passwd);

}

void tdlibQt::AuthenticationHandler::checkPassword(const QString &password)
{
    m_client->checkPassword(password);
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
                return tr("SMS");
            if (codeType->get_id() == authenticationCodeTypeCall::ID)
                return tr("Call");
            if (codeType->get_id() == authenticationCodeTypeFlashCall::ID)
                return tr("Flash call");
            if (codeType->get_id() == authenticationCodeTypeTelegramMessage::ID)
                return tr("Telegram");
        }
    }
    return "";
}

void tdlibQt::AuthenticationHandler::setAuthorizationState(const
                                                           QSharedPointer<tdlibQt::AuthorizationState> &authorizationState)
{
    m_authorizationState = authorizationState;
    if (m_authorizationState->get_id() == authorizationStateWaitPassword::ID) {
        auto waitCode = static_cast<authorizationStateWaitPassword *>(m_authorizationState.data());
        qDebug() << QString::fromStdString(waitCode->recovery_email_address_pattern_) <<
                 waitCode->has_recovery_email_address_ <<  QString::fromStdString(waitCode->password_hint_);

        emit getHintChanged(getHint());
        emit emailPatternChanged(emailPattern());
        emit hasRecoveryEmailChanged(hasRecoveryEmail());
    }
    emit getTypeChanged(getCurrentCodeType());
    emit isUserRegisteredChanged(isUserRegistered());
}

void tdlibQt::AuthenticationHandler::setError(const QJsonObject &errorObject)
{
    m_error = errorObject.toVariantMap();
    emit errorChanged(m_error);
}

void tdlibQt::AuthenticationHandler::setOk(const QJsonObject &okObject)
{
    m_ok = okObject.toVariantMap();
    emit okChanged(m_ok);
}
