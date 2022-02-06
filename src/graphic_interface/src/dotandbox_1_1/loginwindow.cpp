#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QtDebug>

LoginWindow::LoginWindow(MainWindow *mwindow, QWidget *parent) :
    QMainWindow(parent),
    mw(mwindow),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_b_sett_clicked()
{
    qDebug() << this->ui->label_user->text() << " " << this->ui->label_pass->text() << "\n\n";
    this->close();
    mw->setUserNick(this->ui->label_user->text());
    mw->show();
}

