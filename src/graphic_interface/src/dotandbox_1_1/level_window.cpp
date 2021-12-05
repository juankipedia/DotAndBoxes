#include "level_window.h"
#include "ui_level_window.h"
#include <QDebug>

level_window::level_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::level_window)
{
    ui->setupUi(this);
    this->ui->l_arrow1->setAttribute(Qt::WA_TranslucentBackground);
    this->ui->l_arrow2->setAttribute(Qt::WA_TranslucentBackground);
    this->ui->l_arrow3->setAttribute(Qt::WA_TranslucentBackground);
    this->ui->l_arrow4->setAttribute(Qt::WA_TranslucentBackground);

    this->ui->l_arrow1->setVisible(false);
    this->ui->l_arrow2->setVisible(false);
    this->ui->l_arrow3->setVisible(false);
    this->ui->l_arrow4->setVisible(false);

    if(_lvl == 1)
        this->ui->l_arrow1->setVisible(true);
    if(_lvl == 2)
        this->ui->l_arrow2->setVisible(true);
    if(_lvl == 3)
        this->ui->l_arrow3->setVisible(true);
    if(_lvl == 4)
        this->ui->l_arrow4->setVisible(true);

    connect(this,SIGNAL(level_changed(int)),this,SLOT(set_arrow_level(int)));


}

level_window::~level_window()
{
    delete ui;
}

void level_window::on_b_lv1_clicked()
{
    _lvl = 1;
    emit level_changed(_lvl);
}

void level_window::on_b_lv2_clicked()
{
    _lvl = 2;
    emit level_changed(_lvl);
}

void level_window::on_b_lv3_clicked()
{
    _lvl = 3;
    emit level_changed(_lvl);
}

void level_window::on_b_lv4_clicked()
{
    _lvl = 4;
    emit level_changed(_lvl);
}

void level_window::on_b_back_clicked()
{
    this->close();
}

void level_window::set_arrow_level(int a_l)
{
    this->ui->l_arrow1->setVisible(false);
    this->ui->l_arrow2->setVisible(false);
    this->ui->l_arrow3->setVisible(false);
    this->ui->l_arrow4->setVisible(false);

    if(a_l == 1)
        this->ui->l_arrow1->setVisible(true);
    if(a_l == 2)
        this->ui->l_arrow2->setVisible(true);
    if(a_l == 3)
        this->ui->l_arrow3->setVisible(true);
    if(a_l == 4)
        this->ui->l_arrow4->setVisible(true);
}
