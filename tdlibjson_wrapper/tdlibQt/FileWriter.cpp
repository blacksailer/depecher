#include "FileWriter.hpp"
#include <QFile>
#include <QJsonObject>
#include <QDir>
FileWriter::FileWriter(QObject *parent) : QObject(parent)
{

}

void FileWriter::writeJson(const QJsonDocument &doc)
{
    QString typeJson = doc.object()["@type"].toString();
    QDir parentDataDir;
    parentDataDir.mkpath(dirPath);
    parentDataDir.setPath(dirPath);
    parentDataDir.mkdir(typeJson);
    if (!typeCounter.contains(typeJson))
        typeCounter[typeJson] = 0;
    int fileCount = typeCounter[typeJson];
    QFile jsonFile(parentDataDir.absolutePath() + "/"
                   + typeJson + "/"
                   + QString::number(fileCount)
                   + ".json");

    if (jsonFile.open(QFile::WriteOnly)) {
        jsonFile.write(doc.toJson());
        typeCounter[typeJson] = fileCount + 1;
        jsonFile.close();
    }
}
