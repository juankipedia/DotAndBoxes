#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(MainWindow *mwindow, QWidget *parent = nullptr);
    ~LoginWindow();
    MainWindow *mw;

private slots:
    void on_b_sett_clicked();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
