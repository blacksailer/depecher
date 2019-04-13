#ifndef FILEGENERATEDINTERFACE_HPP
#define FILEGENERATEDINTERFACE_HPP
#include <QObject>
#include <QJsonObject>
namespace tdlibQt {

class FileGeneratedInterface: public QObject {
    Q_OBJECT

    qint64 m_generationId;
    QString m_originalPath;
    QString m_destinationPath;
    QString m_conversion;
signals:
    void generationProgressUpdated(qint64 generation_id,int expected_size,int local_prefix_size);
    void generationStopped();
    void generationFinished();
private slots:
    virtual void startGeneration(const QJsonObject &updateFileGenerationStartObject);
    virtual void updateGenerationProgress();
    virtual void stopGeneration();
    virtual void finishGeneration();

};
} //namespace tdlibQt
#endif // FILEGENERATEDINTERFACE_HPP
