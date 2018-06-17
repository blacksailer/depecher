#include "FileWorker.hpp"
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QUrl>
#include <QDebug>
FileWorker::FileWorker(QObject *parent) : QObject(parent),
    m_PicturesPath(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + "/Depecher")
{
    QDir pictureDir;
    pictureDir.mkpath(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + "/Depecher");
}

bool FileWorker::savePictureToGallery(const QString &sourcePath)
{
    QUrl a(sourcePath);
    return QFile::copy(a.toLocalFile(),
                       m_PicturesPath + "/" +
                       a.fileName());
}
