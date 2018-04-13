#include "TelegramProfileProvider.hpp"
#include <QDebug>
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
    QImage result;

    if (requestedSize.isValid()) {
        result = image.scaled(requestedSize, Qt::KeepAspectRatio);
    } else {
        result = image;
    }
    *size = result.size();
    return result;

}
}
