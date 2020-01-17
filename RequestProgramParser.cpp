#include "RequestProgramParser.h"

#include <QFile>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QByteArray>
#include <QBitArray>
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

    for (uint64_t i = 0; i < 2; i++)
    {
        QString periodName = "RequestPeriod" + QString::number(i);

        if (obj.contains(periodName) and obj[periodName].isArray())
        {
            QJsonArray requestPeriod = obj[periodName].toArray();
            //            arrayToBinary(requestPeriod);
            formatCell(requestPeriod);
        }
    }
}

void RequestProgramParser::formatCell(QJsonArray &array)
{
    for (auto item : array)
    {
        auto cell = item.toObject();
        QByteArray bytes;

        if (cell.contains("id"))
        {
            auto id = cell["id"].toDouble();
            bytes.insert(0, QString::number(id)); //4 байта
        }
        if (cell.contains("timeToNext"))
        {
            auto ttn = cell["timeToNext"].toDouble();
            bytes.insert(4, QString::number(ttn)); //4 байта
        }

        //Резерв
        bytes.insert(9, QString::number(0)); //1 байт

        if (cell.contains("type"))
        {
            auto type = cell["type"].toDouble();
            bytes.insert(10, QString::number(type)); //1 байт
        }
        if (cell.contains("message"))
        {
            auto message = cell["message"].toString(); //14 байт
            bytes.insert(11, message);
        }

        bytes.resize(32);
    }
}




QByteArray RequestProgramParser::arrayToBinary(QJsonArray array)
{
    QJsonDocument doc;
    doc.setArray(array);

    QByteArray bytes = doc.toBinaryData();

    return bytes;

}
