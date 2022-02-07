#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QHash>

namespace Ui {
class SignUp;
}

class SignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp(QHash<QString, QString> &users_, QWidget *parent = nullptr);
    ~SignUp();

private slots:
    void on_b_sett_clicked();

private:
    Ui::SignUp *ui;
    QHash<QString, QString> &users;
};

#endif // SIGNUP_H
