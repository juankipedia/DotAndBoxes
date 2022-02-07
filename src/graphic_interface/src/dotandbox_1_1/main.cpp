#include "loginwindow.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QHash>

const QString USERS_FILE_NAME = "DONOTREAD.txt";

QHash<QString, QString> users;

void load_all_users(){
    QFile file(USERS_FILE_NAME);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        file.open(QFile::WriteOnly | QFile::Text);
        file.close();
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd()){
        auto line = in.readLine().split(" ");
        users[line[0]] = line[1];
    }
    file.close();
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow main_window;
    LoginWindow login_window(&main_window, users);
    load_all_users();
    login_window.show();

    return a.exec();
}
