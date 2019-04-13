#include "FileGeneratedHandler.hpp"
#include "FileGeneratedInterface.hpp"

#include "tdlibQt/TdlibJsonWrapper.hpp"
#include "tdlibQt/ParseObject.hpp"
#include "CopyFileConversion.hpp"
FileGeneratedHandler::FileGeneratedHandler(QObject *parent) : QObject(parent)
  ,m_tdlibJson(tdlibQt::TdlibJsonWrapper::instance())
{
    connect(m_tdlibJson, &tdlibQt::TdlibJsonWrapper::updateFileGenerationStartReceived,
            this, &FileGeneratedHandler::initGeneration);
    connect(m_tdlibJson, &tdlibQt::TdlibJsonWrapper::updateFileGenerationStopReceived,
            this, &FileGeneratedHandler::stopGeneration);
}

void FileGeneratedHandler::initGeneration(const QJsonObject &updateFileGenerationStartObject)
{
    if (updateFileGenerationStartObject["@type"].toString() == "updateFileGenerationStart") {
        qint64 g_id = tdlibQt::ParseObject::getInt64(updateFileGenerationStartObject["generation_id"]);
        QString orig = updateFileGenerationStartObject["original_path"].toString();
        QString dest = updateFileGenerationStartObject["destination_path"].toString();
        QString conv = updateFileGenerationStartObject["conversion"].toString();
        if( conv == "copy")
            m_conversionMap[g_id] = new CopyFileConversion(this,g_id,orig,dest,conv);


        connect(m_conversionMap[g_id], &FileGeneratedInterface::generationProgressUpdated,
                this, &FileGeneratedHandler::updateGeneration);
        connect(m_conversionMap[g_id], &FileGeneratedInterface::generationFinished,
                [this](const qint64 gen_id){
            finishGeneration(gen_id,0,"");
        });
        connect(m_conversionMap[g_id], &FileGeneratedInterface::generationStopped,
                [this](const qint64 gen_id,const int code, const QString &message) {
            if(m_conversionMap.contains(gen_id))
            {
                finishGeneration(gen_id,code,message);
                m_conversionMap[gen_id]->stopGeneration();
                m_conversionMap[gen_id]->deleteLater();
                m_conversionMap.remove(gen_id);
            }
        });

        m_conversionMap[g_id]->startGeneration();
    }
}

void FileGeneratedHandler::stopGeneration(const QJsonObject &updateFileGenerationStopObject)
{
    if (updateFileGenerationStopObject["@type"].toString() == "updateFileGenerationStop") {
        qint64 g_id = tdlibQt::ParseObject::getInt64(updateFileGenerationStopObject["generation_id"]);
        if(m_conversionMap.contains(g_id))
        {
            m_conversionMap[g_id]->stopGeneration();
            m_conversionMap[g_id]->deleteLater();
            m_conversionMap.remove(g_id);
        }
    }
}

void FileGeneratedHandler::updateGeneration(qint64 generation_id, int expected_size, int local_prefix_size)
{
    QString setFileGenerationProgressStr = "{\"@type\":\"setFileGenerationProgress\","
                    "\"generation_id\":\"%1\","
                    "\"expected_size\":%2,"
                    "\"local_prefix_size\":%3"
                    "}";
    setFileGenerationProgressStr = setFileGenerationProgressStr.arg(QString::number(generation_id),QString::number(expected_size),QString::number(local_prefix_size) );

    m_tdlibJson->sendMessage(setFileGenerationProgressStr);
}

void FileGeneratedHandler::finishGeneration(const qint64 generation_id,const int code, const QString &message)
{
    QString finishFileGenerationStr;
    if(code != 0){
     finishFileGenerationStr = "{\"@type\":\"finishFileGeneration\","
                    "\"generation_id\":\"%1\","
                    "\"error\":{"
                       "\"@type\":\"error\","
                       "\"code\":%2,"
                       "\"message\":\"%3\""
                       "}"
                    "}";
    finishFileGenerationStr = finishFileGenerationStr.arg(QString::number(generation_id), QString::number(code), message);
} else
    {
        finishFileGenerationStr = "{\"@type\":\"finishFileGeneration\",""\"generation_id\":\"%1\"}";
         finishFileGenerationStr = finishFileGenerationStr.arg(QString::number(generation_id));
    }

    m_tdlibJson->sendMessage(finishFileGenerationStr);
}
