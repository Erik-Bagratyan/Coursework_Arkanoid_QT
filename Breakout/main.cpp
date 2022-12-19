//#include "mainwindow.h"

#include <QApplication>

#include "Headers/arkanoid.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Arkanoid arkanoid;
    arkanoid.show();

    return a.exec();
}
