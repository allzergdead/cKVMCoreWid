#include "ctoolswid.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cToolsWid w;
    w.show();
    return a.exec();
}
