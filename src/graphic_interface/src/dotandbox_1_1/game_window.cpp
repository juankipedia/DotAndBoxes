#include "game_window.h"
#include "ui_game_window.h"
#include <map_graphics.h>

game_window::game_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game_window)
{
    ui->setupUi(this);

    this->ui->l_img->setAttribute(Qt::WA_TranslucentBackground);
    this->ui->l_img_2->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowTitle("Dot and Box");
    this->setWindowIcon(QIcon(":/images/images/WhatsApp Image 2016-11-30 at 11.45.59.jpeg"));

    connect(ui->g_map,SIGNAL(refresh_score(uint,uint)),this,
            SLOT(act_score(uint,uint)));

    connect(ui->g_map,SIGNAL(set_turn(int)),this,SLOT(show_turn(int)));


}

game_window::~game_window()
{
    delete ui;
}

void game_window::start_game(ushort p_or_ai, int _level){
    //This flag is necessary to reset the game:
    level = _level;
    _p_or_ai = p_or_ai;
    //Player 1:
    this->ui->l_p1_id->setText(QString::fromStdString(this->p1.get_id()));
    //Player 2:
    this->ui->l_p2_id->setText(QString::fromStdString(this->p2.get_id()));
    //Showing image for turn:
    this->ui->l_img->setVisible(true);
    this->ui->l_img_2->setVisible(false);

    //Starting the game:
    this->ui->g_map->start_graph(p_or_ai, level);
}

void game_window::act_score(uint a,uint b)
{
    //Player 1:
    this->ui->l_p1_score->setText(QString::number(a));
    //Player 2:
    this->ui->l_p2_score->setText(QString::number(b));
}

void game_window::show_turn(int t){
    if(t == 2)
    {
        this->ui->l_img->setVisible(true);
        this->ui->l_img_2->setVisible(false);
    }
    else if(t == 1)
    {
        this->ui->l_img->setVisible(false);
        this->ui->l_img_2->setVisible(true);
    }
}

void game_window::on_b_exit_clicked()
{
    this->close();
}

void game_window::on_b_reset_clicked()
{
    this->start_game(this->_p_or_ai, level);
}
