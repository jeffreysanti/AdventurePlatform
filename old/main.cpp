#include <QtGui/QApplication>
#include "mainwindow.h"

bool GameMain(MainWindow *w);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return GameMain(&w);
}
