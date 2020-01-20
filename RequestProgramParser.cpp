#include "RequestProgramParser.h"

#include <QFile>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QByteArray>
#include <QBitArray>
#include <QString>
#include <QDebug>

#include "FpgaTypes.h"

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
        QString result;
// TODO переделать под правильный размер
        if (cell.contains("id"))
        {
            auto id = cell["id"].toString().rightJustified(4, '0');
            result.insert(0, id.rightJustified(4, '0')); //4 байта
        }
        if (cell.contains("timeToNext"))
        {
            auto ttn = cell["timeToNext"].toString();
            result.append(ttn.rightJustified(4, '0')); //4 байта
        }

        //Резерв
        result.append(QString('0'));//1 байт

        if (cell.contains("type"))
        {
            auto type = cell["type"].toString();    //1 байт
            result.append(type);
        }
        if (cell.contains("message"))
        {
            auto message = cell["message"].toString(); //14 байт
            result.append(message.rightJustified(14, '0'));
        }

        result = result.leftJustified(32, '0'); //выравнивание до 32 байт (256 бит)

        convertToDriverPresentation(result);
    }
}


QByteArray RequestProgramParser::arrayToBinary(QJsonArray array)
{
    QJsonDocument doc;
    doc.setArray(array);

    QByteArray bytes = doc.toBinaryData();

    return bytes;

}

void RequestProgramParser::convertToDriverPresentation(QString &data)
{
    Cell cell;
    uint8_t index = 0;

    while (!data.isEmpty())
    {
        cell[index] = static_cast<uint8_t>(data.mid(0, 1).toUInt());
        data.remove(0, 1);
        index++;
    }
}
