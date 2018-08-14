#ifndef DNSTXTLOOKUP_HPP
#define DNSTXTLOOKUP_HPP

#include <QObject>
#include <QDnsLookup>

class QQmlEngine;
class QJSEngine;
class DNSTXTLookup : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString inviteLink READ inviteLink WRITE setInviteLink NOTIFY inviteLinkChanged)

    QDnsLookup *dns;
    QString m_inviteLink;

public:
    explicit DNSTXTLookup(QObject *parent = nullptr);
    ~DNSTXTLookup();

    QString inviteLink() const
    {
        return m_inviteLink;
    }
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
    {
        Q_UNUSED(engine);
        Q_UNUSED(scriptEngine);

        return new DNSTXTLookup;
    }
public slots:
    void setInviteLink(const QString &inviteLink)
    {
        if (m_inviteLink == inviteLink)
            return;

        m_inviteLink = inviteLink;
        emit inviteLinkChanged(m_inviteLink);
    }
    void lookupServer();
signals:

    void inviteLinkChanged(const QString &inviteLink);

private slots:
    void handleLookup();
};

#endif // DNSTXTLOOKUP_HPP
