#ifndef FILEGENERATEDHANDLER_HPP
#define FILEGENERATEDHANDLER_HPP

#include <QObject>
#include <QHash>
class FileGeneratedInterface;
namespace tdlibQt {
class TdlibJsonWrapper;
}
class FileGeneratedHandler : public QObject
{
    Q_OBJECT

    QHash <qint64, FileGeneratedInterface*> m_conversionMap;
    tdlibQt::TdlibJsonWrapper *m_tdlibJson;

public:
    explicit FileGeneratedHandler(QObject *parent = nullptr);

signals:

private slots:
    void initGeneration(const QJsonObject &updateFileGenerationStartObject);
    void stopGeneration(const QJsonObject &updateFileGenerationStopObject);
    void updateGeneration(qint64 generation_id,int expected_size,int local_prefix_size);
    void finishGeneration(const qint64 generation_id,const int code, const QString &message);
};

#endif // FILEGENERATEDHANDLER_HPP
