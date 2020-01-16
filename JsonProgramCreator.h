#ifndef JSONPROGRAMCREATOR_H
#define JSONPROGRAMCREATOR_H

#include <stdint.h>

class QJsonObject;
class QJsonArray;

class JsonProgramCreator
{
public:
    JsonProgramCreator();

private:
    QJsonObject createCell(uint32_t id);
    QJsonArray createRequestPeriod();
};

#endif // JSONPROGRAMCREATOR_H
