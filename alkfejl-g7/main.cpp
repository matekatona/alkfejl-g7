#include "diagclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DiagClient w;
    w.show();

    return a.exec();
}
