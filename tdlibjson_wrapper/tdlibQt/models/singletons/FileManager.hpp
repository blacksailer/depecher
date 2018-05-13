#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <QObject>
namespace tdlibQt {

class FileManager : public QObject
{
    Q_OBJECT
    explicit FileManager(QObject *parent = 0);

public:
    static FileManager *instance();
    FileManager(FileManager const &) = delete;
    void operator=(FileManager const &)  = delete;
signals:

public slots:
};
} //tdlibQt
#endif // FILEMANAGER_HPP
