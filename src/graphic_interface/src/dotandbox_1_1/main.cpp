#include "loginwindow.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mw;
    LoginWindow lw(&mw);
    lw.show();

    return a.exec();
}
