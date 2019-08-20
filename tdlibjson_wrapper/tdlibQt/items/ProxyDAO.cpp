#include "ProxyDAO.hpp"
#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/ParseObject.hpp"
namespace tdlibQt {
int ProxyDAO::findProxy(const int id)
{
    int result = -1;
    for (int i = 0; i < m_proxies.size(); i++) {
        if (m_proxies[i]->id_ == id) {
            result = i;
            break;
        }
    }

    return result;
}
int ProxyDAO::findEnabledProxy()
{
    int result = -1;
    for (int i = 0; i < m_proxies.size(); i++) {
        if (m_proxies[i]->is_enabled_) {
            result = i;
            break;
        }
    }

    return result;
}

ProxyDAO::ProxyDAO(QObject *parent) : QAbstractListModel(parent),
    m_client(TdlibJsonWrapper::instance())
{
    connect(m_client, &TdlibJsonWrapper::proxiesReceived,
            this, &ProxyDAO::onProxiesReceived);
    connect(m_client, &TdlibJsonWrapper::proxyReceived,
            this, &ProxyDAO::onProxyReceived);
    connect(m_client, &TdlibJsonWrapper::secondsReceived,
            this, &ProxyDAO::onSecondsReceived);
    connect(m_client, &TdlibJsonWrapper::textReceived,
            this, &ProxyDAO::onTextReceived);
    connect(m_client, &TdlibJsonWrapper::errorReceived,
            this, &ProxyDAO::setError);

    m_client->getProxies();
}

void ProxyDAO::enableProxy(const int id)
{
    m_client->enableProxy(data(index(id), ID).toInt());
}

void ProxyDAO::disableProxy()
{
    m_client->disableProxy();
    for (int i = 0 ; i < m_proxies.size(); i++)
        m_proxies[i]->is_enabled_ = false;
    QVector<int> role;
    role << IS_ENABLED;
    emit dataChanged(index(0), index(m_proxies.size() - 1), role);
}

void ProxyDAO::editProxy(const int proxy_index, const QString &address, const int port,
                         const bool &enabled, const QVariantMap &type)
{
    int proxy_id = data(index(proxy_index), ID).toInt();
    m_client->editProxy(proxy_id, address, port, enabled, type);
//    std::int32_t proxy_id_;
//    std::string server_;
//    std::int32_t port_;
//    bool enable_;
//    object_ptr<ProxyType> type_;

}

void ProxyDAO::pingProxy(const int id)
{
    m_client->pingProxy(data(index(id), ID).toInt());
}

void ProxyDAO::getProxyLink(const int id)
{
    m_client->getProxyLink(data(index(id), ID).toInt());
}

void ProxyDAO::removeProxy(const int id)
{
    beginRemoveRows(QModelIndex(), id, id);
    m_client->removeProxy(data(index(id), ID).toInt());
    endRemoveRows();
}

void ProxyDAO::addProxy(const QString &address, const int port, const bool &enabled, const QVariantMap &type)
{
    m_client->addProxy(address, port, enabled, type);
}

void ProxyDAO::onProxiesReceived(const QJsonObject &proxiesObject)
{
    auto proxiesArray = proxiesObject["proxies"].toArray();
    beginInsertRows(QModelIndex(), m_proxies.size(), m_proxies.size() + proxiesArray.size() - 1);

    for (int i = 0; i < proxiesArray.size(); i++)
        m_proxies.append(ParseObject::parseProxy(proxiesArray[i].toObject()));

    endInsertRows();
}

void ProxyDAO::onProxyReceived(const QJsonObject &proxyObject)
{
    int proxyIndex = findProxy(proxyObject["id"].toInt());
    if (proxyIndex == -1) {
        beginInsertRows(QModelIndex(), m_proxies.size(), m_proxies.size());
        m_proxies.append(ParseObject::parseProxy(proxyObject));
        endInsertRows();
    } else {
        m_proxies.replace(proxyIndex, ParseObject::parseProxy(proxyObject));
        emit dataChanged(index(proxyIndex), index(proxyIndex));
    }
}

void ProxyDAO::onSecondsReceived(const QJsonObject &secondsObject)
{
    if (secondsObject["@extra"].toString().contains("pingProxy_")) {
        int proxy_id = secondsObject["@extra"].toString().split('_')[1].toInt();
        m_pings[proxy_id] = secondsObject["seconds"].toDouble();
        QVector<int> roles;
        roles << PING;
        emit dataChanged(index(findProxy(proxy_id)), index(findProxy(proxy_id)), roles);
    }
}

void ProxyDAO::onTextReceived(const QJsonObject &textObject)
{
    if (textObject["@extra"].toString().contains("getProxyLink"))
        setProxyLink(textObject["text"].toString());
}

void ProxyDAO::onOkReceived(const QJsonObject &okObject)
{
    if (okObject["@extra"].toString().contains("enableProxy")) {
        int proxy_id = okObject["@extra"].toString().split('_')[1].toInt();
        int enabledIndex = findEnabledProxy();
        QVector<int> role;
        role << IS_ENABLED;

        if (enabledIndex != -1)  {
            QVector<int> role;
            role << IS_ENABLED;
            m_proxies[enabledIndex]->is_enabled_ = false;
            emit dataChanged(index(enabledIndex), index(enabledIndex), role);
        }
        m_proxies[proxy_id]->is_enabled_ = true;
        emit dataChanged(index(proxy_id), index(proxy_id), role);

    }
}

void ProxyDAO::setServer(QString server)
{
    if (m_server == server)
        return;

    m_server = server;
    emit serverChanged(server);
}
void ProxyDAO::setError(const QJsonObject &errorObject)
{
    m_error = errorObject.toVariantMap();
    emit errorChanged(m_error);
}
int ProxyDAO::rowCount(const QModelIndex &parent) const
{
    return m_proxies.size();
}

QVariant ProxyDAO::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() < 0)
        return QVariant();

    int rowIndex = index.row();

    switch (role) {
    case ID:
        return m_proxies[rowIndex]->id_;
    case SERVER:
        return QString::fromStdString(m_proxies[rowIndex]->server_);
    case USERNAME:
        switch (m_proxies[rowIndex]->type_->get_id()) {
        case proxyTypeHttp::ID:
            return QString::fromStdString(static_cast<proxyTypeHttp *>(m_proxies[rowIndex]->type_.data())->username_);
        case proxyTypeSocks5::ID:
            return QString::fromStdString(static_cast<proxyTypeSocks5 *>(m_proxies[rowIndex]->type_.data())->username_);
            return QVariant();
        }
    case PASSWORD:
        switch (m_proxies[rowIndex]->type_->get_id()) {
        case proxyTypeHttp::ID:
            return QString::fromStdString(static_cast<proxyTypeHttp *>(m_proxies[rowIndex]->type_.data())->password_);
        case proxyTypeSocks5::ID:
            return QString::fromStdString(static_cast<proxyTypeSocks5 *>(m_proxies[rowIndex]->type_.data())->password_);
            return QVariant();
        }
    case SECRET:
        switch (m_proxies[rowIndex]->type_->get_id()) {
        case proxyTypeMtproto::ID:
            return QString::fromStdString(static_cast<proxyTypeMtproto *>(m_proxies[rowIndex]->type_.data())->secret_);
            return QVariant();
        }
    case HTTP_ONLY:
        switch (m_proxies[rowIndex]->type_->get_id()) {
        case proxyTypeHttp::ID:
            return static_cast<proxyTypeHttp *>(m_proxies[rowIndex]->type_.data())->http_only_;
            return QVariant();
        }
    case PORT:
        return m_proxies[rowIndex]->port_;
    case LAST_USED_DATE:
        return m_proxies[rowIndex]->last_used_date_;
    case IS_ENABLED:
        return m_proxies[rowIndex]->is_enabled_;
    case PING:
        if (m_pings.contains(m_proxies[rowIndex]->id_))
            return m_pings[m_proxies[rowIndex]->id_];
        else
            return -1;
    case PROXY_TYPE:
        switch (m_proxies[rowIndex]->type_->get_id()) {
        case proxyTypeHttp::ID:
            return "HTTP";
        case proxyTypeMtproto::ID:
            return "MtProto";
        case proxyTypeSocks5::ID:
            return "SOCKS5";
        }
    }
}

QHash<int, QByteArray> ProxyDAO::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ID] = "id";
    roles[SERVER] = "server";
    roles[PORT] = "port";
    roles[USERNAME] = "username";
    roles[PASSWORD] = "password";
    roles[SECRET] = "secret";
    roles[HTTP_ONLY] = "http_only";
    roles[LAST_USED_DATE] = "last_used_date";
    roles[IS_ENABLED] = "is_enabled";
    roles[PROXY_TYPE] = "proxy_type";
    roles[PING] = "ping";
    return roles;
}
} //namespace tdlibQt
