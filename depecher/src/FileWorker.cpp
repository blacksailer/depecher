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

QString FileWorker::openContact(const QString &firstName, const QString &lastName, const QString &phoneNumber, const int userId)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    QFile file(path + "/contact.vcf");
    QString vcfData = "BEGIN:VCARD \n"
                      "VERSION:2.1 \n"
                      "FN;ENCODING=QUOTED-PRINTABLE;CHARSET=UTF-8:%1 %2 \n"
                      "N;ENCODING=QUOTED-PRINTABLE;CHARSET=UTF-8:%2;%1 \n"
                      "TEL;HOME;VOICE;ISDN:%3 \n"
                      "END:VCARD";
    vcfData = vcfData.arg(firstName, lastName, phoneNumber);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(vcfData.toUtf8());
        file.close();
        return path + "/contact.vcf";
    } else
        return "";

}
