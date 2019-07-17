#ifndef QDBUSSHAREADAPTOR_HPP
#define QDBUSSHAREADAPTOR_HPP

#include <QObject>
#include <QDBusMessage>
#include <QVariant>
#include <QJsonObject>
#include "tdlibQt/items/TdApi.hpp"
namespace tdlibQt {
class TdlibJsonWrapper;
}
class DBusShareAdaptor : public QObject
{
    Q_OBJECT
    struct RequestData {
        QVariant chatList;
        QDBusMessage reply;
    };
    QList<RequestData> m_delayedList;
    QList<qint64> m_chatIds;
    QList<QVariant> m_chats;
    QMap<int, QSharedPointer<tdlibQt::file>> m_files;
    QMap<int, qint64> m_fileIdToGenerationIdMap;
    QMap<QString, int> m_filesPending;
    QMap<qint64, QPair<QString, QString>> m_generationIdPathMap;
    tdlibQt::TdlibJsonWrapper *m_tdlibJson;

    inline void sendPhoto(const QList<qlonglong> &chat_ids, const QString &filepath);
    inline void sendDocument(const QList<qlonglong> &chat_ids, const QString &filepath);
    inline void sendText(const QList<qlonglong> &chat_ids, const QString &data);

public:
    explicit DBusShareAdaptor(QObject *parent = nullptr);
    ~DBusShareAdaptor();
signals:
    void uploadFailed(const QString &chat_id, const QString &message_id);
    void uploadFinished(const QString &chat_id, const QString &message_id, const QString &remote_url);
    void uploadProgress(const QString &chat_id, const QString &message_id, int percent);
    void uploadStarted(const QString &chat_id, const QString &message_id, const QString &local_url);
    void sendData();
public slots:
    QVariant getChatList(const qint64 lastChatId, const qint64 order, const QDBusMessage &message);
    void sendMedia(const QList<qlonglong> &chat_ids, const QString &filepath, const QString &mimeType);
    void sendVCard(const QList<qlonglong> &chat_ids, const QString &data);
    void sendChatList();
private slots:
    void addChatItem(const QJsonObject &chatObject);
    void updateFileReceived(const QJsonObject &updateFileObject);
    void fileGenerationStarted(const QJsonObject &updateFileGenerationStartObject);
    void fileGenerationStoped(const QJsonObject &updateFileGenerationStopObject);
};


#endif // QDBUSSHAREADAPTOR_HPP
