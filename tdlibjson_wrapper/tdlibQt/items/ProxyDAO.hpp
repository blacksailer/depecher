#ifndef PROXYDAO_HPP
#define PROXYDAO_HPP

#include <QObject>
#include <QJsonObject>
#include <QAbstractListModel>
#include "TdApi.hpp"

namespace tdlibQt {
class TdlibJsonWrapper;

class ProxyDAO : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString  username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString  password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString proxyLink READ proxyLink WRITE setProxyLink NOTIFY proxyLinkChanged)
    Q_PROPERTY(QVariantMap error READ error NOTIFY errorChanged)

    TdlibJsonWrapper *m_client;
    QString m_server;
    QList<QSharedPointer<proxy>> m_proxies;
    QHash<int,double> m_pings;
    int m_port;

    QString m_username;

    QString m_password;

    QString m_address;

    int findProxy(const int id);

    QString m_proxyLink;

    QVariantMap m_error;

    int findEnabledProxy();
public:
    explicit ProxyDAO(QObject *parent = 0);

    QString server() const
    {
        return m_server;
    }

    int port() const
    {
        return m_port;
    }

    QString username() const
    {
        return m_username;
    }

    QString password() const
    {
        return m_password;
    }

    QString address() const
    {
        return m_address;
    }

signals:

    void serverChanged(QString server);

    void portChanged(int port);

    void usernameChanged(QString username);

    void passwordChanged(QString password);

    void addressChanged(QString address);

    void proxyLinkChanged(QString proxyLink);

    void errorChanged(QVariantMap error);

public slots:
    void addProxy(const QString &address, const int port, const bool &enabled, const QVariantMap &type);
    void enableProxy(const int id);
    void disableProxy();
    void editProxy(const int proxy_index, const QString &address, const int port,
                   const bool &enabled, const QVariantMap &type);
    void pingProxy(const int id);
    void getProxyLink(const int id);
    void removeProxy(const int id);

    void onProxiesReceived(const QJsonObject &proxiesObject);
    void onProxyReceived(const QJsonObject &proxyObject);
    void onSecondsReceived(const QJsonObject &secondsObject);
    void onTextReceived(const QJsonObject &textObject);
    void onOkReceived(const QJsonObject &okObject);

    void setServer(QString server);
    void setPort(int port)
    {
        if (m_port == port)
            return;

        m_port = port;
        emit portChanged(port);
    }
    void setUsername(QString username)
    {
        if (m_username == username)
            return;

        m_username = username;
        emit usernameChanged(username);
    }
    void setPassword(QString password)
    {
        if (m_password == password)
            return;

        m_password = password;
        emit passwordChanged(password);
    }
    void setAddress(QString address)
    {
        if (m_address == address)
            return;

        m_address = address;
        emit addressChanged(address);
    }

    // QAbstractItemModel interface
    void setProxyLink(QString proxyLink)
    {
        if (m_proxyLink == proxyLink)
            return;

        m_proxyLink = proxyLink;
        emit proxyLinkChanged(m_proxyLink);
    }

    void setError(const QJsonObject &errorObject);
public:

    enum Roles {
        ID,
        SERVER,
        PORT,
        USERNAME,
        PASSWORD,
        LAST_USED_DATE,
        IS_ENABLED,
        PROXY_TYPE,
        SECRET,
        HTTP_ONLY,
        PING
    };
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    QString proxyLink() const
    {
        return m_proxyLink;
    }
    QVariantMap error() const
    {
        return m_error;
    }
};
} //namespace tdlibQt

#endif // PROXYDAO_HPP
