#include "TelegramProfileProvider.hpp"
#include <QDebug>
#include <QImageReader>
namespace tdlibQt {
TelegramProfileProvider::TelegramProfileProvider() : QQuickImageProvider(
        QQuickImageProvider::Image)
{

}

QImage TelegramProfileProvider::requestImage(const QString &id, QSize *size,
        const QSize &requestedSize)
{
    QString rsrcid = id;
    QImage image(rsrcid);
    //https://github.com/tdlib/td/issues/264
    if (rsrcid.right(9) == ".jpg.webp") {
        QImageReader imgReader(rsrcid.left(rsrcid.length() - 1 - 4), "webp");
        QImage result = imgReader.read();
        if (imgReader.error() == QImageReader::InvalidDataError || imgReader.error() == QImageReader::DeviceError) {
            imgReader.setFormat("jpg");
            result = imgReader.read();
        }
        *size = result.size();
        return result;
    } else {
        QImage result = image;

//    if (requestedSize.isValid()) {
//        result = image.scaled(requestedSize, Qt::KeepAspectRatio);
//    } else {
//        result = image;
//    }
        *size = result.size();
        return result;
    }
}
}
