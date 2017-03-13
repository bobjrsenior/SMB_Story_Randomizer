#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setup();
    w.show();


    //QObject::connect(generateButton, SIGNAL(generateButtonClicked->clicked()), MainUINamespace, SLOT(generateButtonClicked()));
    return a.exec();
}
