#ifndef JSONPROGRAMCREATOR_H
#define JSONPROGRAMCREATOR_H

#include <stdint.h>

class QJsonObject;
class QJsonArray;
class QString;

class JsonProgramCreator
{
public:
    JsonProgramCreator();
    static void createEmptyJsonRequestProgram(QString pathToFile);

private:
    static QJsonObject createCell(uint32_t id);
    static QJsonArray createRequestPeriod();
};

#endif // JSONPROGRAMCREATOR_H
