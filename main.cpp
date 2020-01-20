#include <QCoreApplication>

#include <JsonProgramCreator.h>
#include <RequestProgramParser.h>

#include <FpgaSsrAppDriver.h>

#include <QStringList>

#include <QStandardPaths>
#include <QString>
#include <QTextStream>

#include <QDebug>

const QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/test.json";

void printInstruction()
{
    qDebug() << "Enter mode number and path to file in format: modeNumber pathToFile " << endl
             << "(for example: 1  ~/Desktop)" << endl
             << "Modes: 0 - create new empty json file" << endl
             << "1 - convert exist file to binary and send" << endl
             << "second argument is path to file, if it's empty, program will use standart path: ~/Desktop";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto args = QCoreApplication::arguments();

    if (argc == 2 or argc == 3)
    {
        QString path;
        if (argc == 3)
            path = args.at(2);
        else
            path = defaultPath;

        if (args.at(1) == "0")
        {
            JsonProgramCreator::createEmptyJsonRequestProgram(path);
        }
        else if (args.at(1) == "1")
        {
            RequestProgramParser parser(path);

            auto appDriver = makeDriver("");
            appDriver->requestScheldule();
        }
        else
            printInstruction();
    }

    return a.exec();
}
