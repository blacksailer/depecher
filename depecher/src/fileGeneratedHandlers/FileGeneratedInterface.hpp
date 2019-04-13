#ifndef FILEGENERATEDINTERFACE_HPP
#define FILEGENERATEDINTERFACE_HPP
#include <QObject>
#include <QJsonObject>
class FileGeneratedInterface : public QObject {
    Q_OBJECT
protected:
    const qint64 m_generationId;
    const QString m_originalPath;
    const QString m_destinationPath;
    const QString m_conversion;
public:
    FileGeneratedInterface(QObject *parent, const qint64 &generationId,
                           const QString &originalPath,
                           const QString &destinationPath,
                           const QString &conversion): QObject(parent),
      m_generationId(generationId),
      m_originalPath(originalPath),
      m_destinationPath(destinationPath),
      m_conversion(conversion) {

    }


signals:
    void generationProgressUpdated(const qint64 generation_id,const qint64 expected_size, const qint64 local_prefix_size);
    void generationStopped(const qint64 generation_id, const int code, const QString &message);
    void generationFinished(const qint64 generation_id);
public slots:
    virtual void startGeneration()  = 0;
    virtual void stopGeneration()  = 0;
    virtual void finishGeneration()  = 0;

};
#endif // FILEGENERATEDINTERFACE_HPP
