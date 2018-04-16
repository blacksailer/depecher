#include "ProxyDAO.hpp"
#include "tdlibQt/TdlibJsonWrapper.hpp"

namespace tdlibQt {
ProxyDAO::ProxyDAO(QObject *parent) : QObject(parent),
    m_client(TdlibJsonWrapper::instance())
{
    connect(m_client, &TdlibJsonWrapper::proxyReceived,
            this, &ProxyDAO::onProxyReceived);
    m_client->getProxy();
}

void ProxyDAO::setProxy(const QString &address, const int port, const QString &username,
                        const QString &password)
{
    if (address == "")
        m_client->setProxy("proxyEmpty");
    else
        m_client->setProxy("proxySocks5", address, port, username, password);
}

void ProxyDAO::onProxyReceived(const QJsonObject &proxyObject)
{
    setAddress(proxyObject["server"].toString());
    setPort(proxyObject["port"].toInt());
    setUsername(proxyObject["username"].toString());
    setPassword(proxyObject["password"].toString());
}
} //namespace tdlibQt
