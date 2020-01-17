#include "RequestProgramParser.h"

#include <QFile>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QByteArray>
#include <QDebug>

RequestProgramParser::RequestProgramParser(QString pathToJson)
{
    readFile(pathToJson);
}

void RequestProgramParser::readFile(QString pathToJson)
{
    qDebug() << "Reading file from path" << pathToJson;

    QFile file(pathToJson);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

        QByteArray saveData = file.readAll();

        QJsonDocument json(QJsonDocument::fromJson(saveData));

        parse(json.object());
}

void RequestProgramParser::parse(QJsonObject obj)
{
    qDebug() << "Parsing file";

    QJsonObject cell;

    for (uint64_t i = 0; i < 1; i++)
    {
        QString periodName = "RequestPeriod" + QString::number(i);

        if (obj.contains(periodName) and obj[periodName].isArray())
        {
            QJsonArray requestPeriod = obj[periodName].toArray();
            arrayToBinary(requestPeriod);
        }
    }
}

QByteArray RequestProgramParser::arrayToBinary(QJsonArray array)
{
    QJsonDocument doc;
    doc.setArray(array);

    QByteArray bytes = doc.toBinaryData();

    return bytes;

}
