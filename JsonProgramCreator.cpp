#include "JsonProgramCreator.h"

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

#include <QFile>
#include <QStandardPaths>

#include <QDebug>

JsonProgramCreator::JsonProgramCreator()
{   
}

void JsonProgramCreator::createEmptyJsonRequestProgram(QString pathToFile)
{
    qDebug() << "Creating file from path" << pathToFile;

    QJsonObject requestProgram;

    for (uint64_t i = 0; i < 2; i++)    //будет 2^14 в конечном варианте
    {
        QString name = "RequestPeriod" + QString::number(i);
        requestProgram[name] = createRequestPeriod();   // 1 запросный период, 16 ячеек
    }

    QFile saveFile(pathToFile);

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
    }

    QJsonDocument json;
    json.setObject(requestProgram);
    saveFile.write(json.toJson());
    saveFile.close();
}

QJsonObject JsonProgramCreator::createCell(uint32_t id)
{
    QJsonObject cell;

    cell["id"] = QJsonValue::fromVariant(id).toDouble();
    cell["timeToNext"] = QJsonValue::fromVariant(1);
    cell["hasNext"] = QJsonValue::fromVariant(1);
    cell["reserve"] = QJsonValue::fromVariant("");
    cell["type"] = QJsonValue::fromVariant(1);
    cell["message"] = QJsonValue::fromVariant("00000000");

    return cell;

}

QJsonArray JsonProgramCreator::createRequestPeriod()
{
    QJsonArray line;
    for (uint8_t i = 0; i < 16; i++)
    {
        line.append(createCell(i));
    }

    return line;
}
