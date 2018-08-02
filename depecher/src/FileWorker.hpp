#ifndef FILEWORKER_HPP
#define FILEWORKER_HPP

#include <QObject>

class FileWorker : public QObject
{
    Q_OBJECT
    QString m_PicturesPath;
public:
    explicit FileWorker(QObject *parent = 0);

signals:

public slots:
    bool savePictureToGallery(const QString &sourcePath);
    QString openContact(const QString &firstName, const QString &lastName, const QString &phoneNumber, const int userId);
};

#endif // FILEWORKER_HPP
