#ifndef FILEWORKER_HPP
#define FILEWORKER_HPP

#include <QObject>

class FileWorker : public QObject
{
    Q_OBJECT
public:
    explicit FileWorker(QObject *parent = 0);

signals:

public slots:
    static bool savePictureToGallery(const QString &sourcePath);
};

#endif // FILEWORKER_HPP
