#ifndef REQUESTPROGRAMPARSER_H
#define REQUESTPROGRAMPARSER_H


#include <QString>
#include <array>

class QJsonObject;
class QJsonArray;

class RequestProgramParser
{
public:
    RequestProgramParser(QString pathToJson);

private:
    void readFile(QString pathToJson);
    void parse(QJsonObject obj);
    void formatCell(QJsonArray &array);
    QByteArray arrayToBinary(QJsonArray array);
};

#endif // REQUESTPROGRAMPARSER_H
