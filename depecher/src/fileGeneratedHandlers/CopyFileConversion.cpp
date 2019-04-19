#include "CopyFileConversion.hpp"
#include <QFile>
#include <QFileInfo>
#include <QThread>
#include <QDebug>

CopyFileConversion::CopyFileConversion(QObject *parent, const qint64 &generationId,
                                       const QString &originalPath,
                                       const QString &destinationPath,
                                       const QString &conversion) : FileGeneratedInterface(parent,generationId,originalPath,destinationPath,conversion)
{

}

void CopyFileConversion::startGeneration()
{
    QThread* thread = new QThread;
    Worker* worker = new Worker(m_originalPath,m_destinationPath);
    worker->moveToThread(thread);
    m_expectedSize = QFileInfo(m_originalPath).size();
    connect(worker, &Worker::error, this, &CopyFileConversion::stop);
    connect(this, &CopyFileConversion::generationStopped, worker, &Worker::stop);
    connect(worker, &Worker::copied, [this](const qint64 generatedBytesSize) {
        m_generatedSize += generatedBytesSize;
        emit generationProgressUpdated(m_generationId,m_expectedSize,m_generatedSize);
    });
    connect(worker, &Worker::finished, this, &CopyFileConversion::finishGeneration);

    connect(thread, &QThread::started, worker, &Worker::process);
    connect(worker, &Worker::finished, thread, &QThread::quit);
    connect(worker, &Worker::finished, worker, &Worker::deleteLater);
    connect(worker, &Worker::finished, thread, &QThread::deleteLater);
    connect(worker, &Worker::aborted, thread, &QThread::quit);
    connect(worker, &Worker::aborted, thread, &QThread::deleteLater);
    connect(worker, &Worker::aborted, this, &CopyFileConversion::stopGeneration);
    thread->start();

}


void CopyFileConversion::stop(const QString &error)
{
    qDebug() << error;
    emit generationStopped(m_generationId,1,error);
}

void CopyFileConversion::stopGeneration()
{
    qDebug() << "aborted";
}

void CopyFileConversion::finishGeneration()
{
    emit generationFinished(m_generationId);
}

Worker::Worker(const QString &src, const QString &dst) : m_originalPath(src),m_destinationPath(dst)
{

}

void Worker::process()
{
    if(!QFileInfo::exists(m_originalPath))
    {
        emit error("no file in " + m_originalPath);
        return;
    }

    QFile src(m_originalPath);
    QFile dst(m_destinationPath);
    if(src.open(QIODevice::ReadOnly) && dst.open(QIODevice::WriteOnly)) {
        qint64 size = 4 * 1024;
        char data[size];// = new char[size];
        int k = 0;
        while(!src.atEnd() && !m_stopCopy)
        {
            src.read(data, size);
            qint64 bytes = dst.write(data, size);
            emit copied(bytes);
            k++;
            src.seek(k * size);
        }

        dst.flush();
        src.close();
        dst.close();
        if(m_stopCopy)
            emit aborted();
        else
            emit finished();
    } else {
        if(src.error() != QFileDevice::NoError) {
            switch (src.error()) {
            case QFileDevice::ReadError:
                emit error("An error occurred when reading from the file. " + m_originalPath);
                break;
            case QFileDevice::FatalError:
                emit error("A fatal error occurred " + m_originalPath);
                break;
            case QFileDevice::ResourceError:
                emit error("Out of resources (e.g., too many open files, out of memory, etc.) " + m_originalPath);
                break;
            case QFileDevice::OpenError:
                emit error("The file could not be opened " + m_originalPath);
                break;
            case QFileDevice::AbortError:
                emit error("The operation was aborted " + m_originalPath);
                break;
            case QFileDevice::TimeOutError:
                emit error("A timeout occurred " + m_originalPath);
                break;
            case QFileDevice::UnspecifiedError:
                emit error("An unspecified error occurred " + m_originalPath);
                break;
            case QFileDevice::PermissionsError:
                emit error("The file could not be accessed " + m_originalPath);
                break;
            case QFileDevice::CopyError:
                emit error("The file could not be copied " + m_originalPath);
                break;
            case QFileDevice::WriteError:
            case QFileDevice::RemoveError:
            case QFileDevice::PositionError:
            case QFileDevice::ResizeError:
            case QFileDevice::RenameError:
            default:
                break;
            }
        } else  if(dst.error() != QFileDevice::NoError) {
            switch (dst.error()) {
            case QFileDevice::WriteError:
                emit error("An error occurred when writing to the file. " + m_destinationPath);
                break;
            case QFileDevice::FatalError:
                emit error("A fatal error occurred " + m_destinationPath);
                break;
            case QFileDevice::ResourceError:
                emit error("Out of resources (e.g., too many open files, out of memory, etc.) " + m_destinationPath);
                break;
            case QFileDevice::OpenError:
                emit error("The file could not be opened " + m_destinationPath);
                break;
            case QFileDevice::AbortError:
                emit error("The operation was aborted " + m_destinationPath);
                break;
            case QFileDevice::TimeOutError:
                emit error("A timeout occurred " + m_destinationPath);
                break;
            case QFileDevice::UnspecifiedError:
                emit error("An unspecified error occurred " + m_destinationPath);
                break;
            case QFileDevice::PermissionsError:
                emit error("The file could not be accessed " + m_destinationPath);
                break;
            case QFileDevice::CopyError:
                emit error("The file could not be copied " + m_destinationPath);
                break;
            case QFileDevice::ReadError:
            case QFileDevice::RemoveError:
            case QFileDevice::RenameError:
            case QFileDevice::ResizeError:
            case QFileDevice::PositionError:
            default:
                break;
            }
        }
        return;
    }

}

void Worker::stop()
{
    m_stopCopy = true;
}
