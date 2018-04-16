#ifndef PROXYDAO_HPP
#define PROXYDAO_HPP

#include <QObject>
#include <QJsonObject>
namespace tdlibQt {
class TdlibJsonWrapper;
class ProxyDAO : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString  username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString  password READ password WRITE setPassword NOTIFY passwordChanged)

    TdlibJsonWrapper *m_client;
    QString m_server;

    int m_port;

    QString m_username;

    QString m_password;

    QString m_address;

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

public slots:
    void setProxy(const QString &address, const int port,
                  const QString &username, const QString &password);
    void onProxyReceived(const QJsonObject &proxyObject);
    void setServer(QString server)
    {
        if (m_server == server)
            return;

        m_server = server;
        emit serverChanged(server);
    }
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
};
} //namespace tdlibQt

#endif // PROXYDAO_HPP
