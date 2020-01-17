#include <QCoreApplication>

#include <JsonProgramCreator.h>
#include <RequestProgramParser.h>
#include <QStringList>

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    qDebug() << argc << argv[0] << argv[1];
//    JsonProgramCreator creator;
    if (argc == 2)
    {
        auto args = QCoreApplication::arguments();
        RequestProgramParser(args.at(1));
    }
    else
        qDebug() << "Error, enter path to file";

    return a.exec();
}
