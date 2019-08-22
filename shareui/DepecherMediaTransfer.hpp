#ifndef DEPECHERMEDIATRANSFER_HPP
#define DEPECHERMEDIATRANSFER_HPP

#include <QObject>

#include <TransferEngine-qt5/mediatransferinterface.h>
#include <TransferEngine-qt5/mediaitem.h>

#include <QtDBus/QtDBus>

#define SERVER_INTERFACE "org.blacksailer.depecher.share"
#define SERVER_SERVICE "org.blacksailer.depecher"
#define SERVER_PATH "/org/blacksailer/depecher/share"
class DepecherMediaTransfer : public MediaTransferInterface
{
    Q_OBJECT
public:
    explicit DepecherMediaTransfer(QObject *parent = nullptr);
    bool	cancelEnabled() const;
    QString	displayName() const;
    bool	restartEnabled() const;
    QUrl serviceIcon() const;

private:
    QDBusInterface *_iface;
    QString _mediaName;
    QStringList m_generationIds;

private slots:
    void uploadMediaProgress(const QString &jid, const QString &msgId, int percent);
    void uploadMediaFinished(const QString &jid, const QString &msgId, const QString &remoteUrl);
    void uploadMediaStarted(const QString &jid, const QString &msgId, const QString &localUrl);
    void uploadMediaFailed(const QString &jid, const QString &msgId);

public slots:
    void	cancel();
    void	start();

};

#endif // DEPECHERMEDIATRANSFER_HPP
