#ifndef COPYFILECONVERSION_HPP
#define COPYFILECONVERSION_HPP

#include "FileGeneratedInterface.hpp"

class CopyFileConversion : public FileGeneratedInterface
{
    Q_OBJECT
    qint64 m_expectedSize = 0;
    qint64 m_generatedSize = 0;

public:
    CopyFileConversion(QObject *parent, const qint64 &generationId,
    const QString &originalPath,
    const QString &destinationPath,
    const QString &conversion);

    // FileGeneratedInterface interface
public slots:
    void startGeneration() Q_DECL_OVERRIDE;
    void stop(const QString &error);
    void stopGeneration() Q_DECL_OVERRIDE;
    void finishGeneration() Q_DECL_OVERRIDE;
};


class Worker : public QObject {
    Q_OBJECT

    const QString m_originalPath;
    const QString m_destinationPath;
    bool m_stopCopy = false;
public:
    Worker(const QString &src,const QString &dst);
public slots:
    void process();
    void stop();
signals:
    void finished();
    void aborted();
    void copied(qint64 bytes);
    void error(const QString &err);

private:
    // add your variables here
};
#endif // COPYFILECONVERSION_HPP
