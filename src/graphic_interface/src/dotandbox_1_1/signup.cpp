#include "signup.h"
#include "ui_signup.h"
#include <QFile>
#include <QTextStream>

const QString USERS_FILE_NAME = "DONOTREAD.txt";

SignUp::SignUp(QHash<QString, QString> &users_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUp),
    users(users_)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_b_sett_clicked()
{
    QString user = this->ui->label_user->text();
    QString pass = this->ui->label_pass->text();
    if(user == "" || pass == ""){
        this->ui->errorLabel->setText("User or password should not be empty.");
        return;
    }

    if(users.contains(user)){
        this->ui->errorLabel->setText("User already exists.");
        return;
    }

    QFile file(USERS_FILE_NAME);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
       qDebug() << "Could not open Users File" << "\n";
    }
    users[user] = pass;
    QTextStream out(&file);
    for(int i = 0; i < users.keys().size(); i++){
        auto key = users.keys()[i];
        out << key << " " << users[key];
        if((i + 1) != users.keys().size()) out << "\n";
        file.flush();
    }
    file.close();
    this->close();
}

