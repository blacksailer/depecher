#include "DepecherMediaTransfer.hpp"

DepecherMediaTransfer::DepecherMediaTransfer(QObject *parent) : MediaTransferInterface(parent)
{
    QDBusConnection conn = QDBusConnection::sessionBus();
    _iface = new QDBusInterface(SERVER_SERVICE, SERVER_PATH, SERVER_INTERFACE,
                                conn, this);
    conn.connect(SERVER_SERVICE, SERVER_PATH, SERVER_INTERFACE,
                 "uploadFailed", this, SLOT(uploadMediaFailed(QString, QString)));
    conn.connect(SERVER_SERVICE, SERVER_PATH, SERVER_INTERFACE,
                 "uploadFinished", this, SLOT(uploadMediaFinished(QString, QString, QString)));
    conn.connect(SERVER_SERVICE, SERVER_PATH, SERVER_INTERFACE,
                 "uploadStarted", this, SLOT(uploadMediaStarted(QString, QString, QString)));
    conn.connect(SERVER_SERVICE, SERVER_PATH, SERVER_INTERFACE,
                 "uploadProgress", this, SLOT(uploadMediaProgress(QString, QString, int)));
}

bool DepecherMediaTransfer::cancelEnabled() const
{
    return false;
}

QString DepecherMediaTransfer::displayName() const
{
    return "Depecher";
}

bool DepecherMediaTransfer::restartEnabled() const
{
    return false;
}

QUrl DepecherMediaTransfer::serviceIcon() const
{
    return QUrl::fromLocalFile("/usr/share/depecher/qml/assets/icons/depecher.png");
}

void DepecherMediaTransfer::uploadMediaProgress(const QString &jid, const QString &msgId, int percent)
{
    Q_UNUSED(jid);
    if (m_generationIds.contains(msgId)) {
        if (percent <= 100) {
            qreal s_progress = (qreal)percent / (qreal)100;
            setProgress(s_progress);
        }
    }
}

void DepecherMediaTransfer::uploadMediaFinished(const QString &jid, const QString &msgId, const QString &remoteUrl)
{
    Q_UNUSED(jid);
    Q_UNUSED(remoteUrl);
    if (m_generationIds.contains(msgId)) {
        m_generationIds.removeAll(msgId);
        if (m_generationIds.size() == 0)
            setStatus(MediaTransferInterface::TransferFinished);
    }
}

void DepecherMediaTransfer::uploadMediaStarted(const QString &jid, const QString &msgId, const QString &localUrl)
{
    Q_UNUSED(jid);
    if (localUrl == _mediaName) {
        m_generationIds.append(msgId);
        setStatus(MediaTransferInterface::TransferStarted);
    }
}

void DepecherMediaTransfer::uploadMediaFailed(const QString &jid, const QString &msgId)
{
    Q_UNUSED(jid);
    if (m_generationIds.contains(msgId)) {
        m_generationIds.removeAll(msgId);
        setStatus(MediaTransferInterface::TransferInterrupted);
    }
}

void DepecherMediaTransfer::cancel()
{
    //Cancel transfer in dbus TODO
    setStatus(MediaTransferInterface::TransferCanceled);
}

void DepecherMediaTransfer::start()
{
    QString mime = mediaItem()->value(MediaItem::MimeType).toString();
    _mediaName = mediaItem()->value(MediaItem::Url).toString().replace("file://", "");
    QVariantMap description = mediaItem()->value(MediaItem::UserData).toMap();
    QStringList jids = description["recipients"].toString().split(",");
    QList<qint64> chat_ids;
    for (int i = 0; i < jids.size(); ++i)
        chat_ids.append(jids[i].toLongLong());
    QVariant arg;
    arg.setValue(chat_ids);
    if (_iface) {
        if (!mime.contains("text"))
            _iface->call(QDBus::NoBlock, "sendMedia", arg, _mediaName, mime);
        else {
            _mediaName = description["name"].toString();
            _iface->call(QDBus::NoBlock, "sendMedia", arg, QString(QJsonDocument::fromVariant(mediaItem()->value(MediaItem::UserData)).toJson()), mime);
        }
    }
}
