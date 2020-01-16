#include <QCoreApplication>

#include <JsonProgramCreator.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    JsonProgramCreator creator;
    return a.exec();
}
