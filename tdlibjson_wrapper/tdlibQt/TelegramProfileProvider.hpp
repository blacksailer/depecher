#ifndef TELEGRAMPROFILEPROVIDER_HPP
#define TELEGRAMPROFILEPROVIDER_HPP

#include <QQuickImageProvider>
namespace tdlibQt {
class TelegramProfileProvider : public QQuickImageProvider
{
public:
    explicit TelegramProfileProvider();
    // QQuickImageProvider interface
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
};
}

#endif // TELEGRAMPROFILEPROVIDER_HPP
