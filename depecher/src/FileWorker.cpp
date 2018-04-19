#include "FileWorker.hpp"
#include <QStandardPaths>
#include <QFile>
#include <QUrl>
#include <QDebug>
FileWorker::FileWorker(QObject *parent) : QObject(parent)
{

}

bool FileWorker::savePictureToGallery(const QString &sourcePath)
{
    QUrl a(sourcePath);
    return QFile::copy(a.toLocalFile(),
                       QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + "/" +
                       a.fileName());
}
