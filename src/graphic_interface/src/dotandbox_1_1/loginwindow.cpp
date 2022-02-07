#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QtDebug>
#include "signup.h"

LoginWindow::LoginWindow(MainWindow *mwindow, QHash<QString, QString> &users_, QWidget *parent) :
    QMainWindow(parent),
    mw(mwindow),
    users(users_),
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
    QString user = ui->label_user->text();
    QString password = ui->label_pass->text();
    if(this->users.contains(password) || this->users[user] != password){
        this->ui->errorLabel->setText("Error on login user or password wrong");
    }
    else{
        this->close();
        mw->setUserNick(this->ui->label_user->text());
        mw->show();
    }


}


void LoginWindow::on_b_sett_2_clicked()
{
    auto signup_window = new SignUp(users);
    signup_window->setAttribute(Qt::WA_DeleteOnClose);
    signup_window->show();
}

