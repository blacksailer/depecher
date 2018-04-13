#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP

#include <QObject>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QMap>
class FileWriter : public QObject
{
    Q_OBJECT
    QString dirPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
                      + "/depecherJson";
    QMap<QString, int> typeCounter;
public:
    explicit FileWriter(QObject *parent = 0);
    void writeJson(const QJsonDocument &doc);
signals:

public slots:
};

#endif // FILEWRITER_HPP
