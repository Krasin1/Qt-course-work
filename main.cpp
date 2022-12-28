#include "mainwindow.h"

#include <QApplication>

#include "Vector.hpp"
#include "radio_components.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
