#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Dot and Box");
    this->setWindowIcon(QIcon(":/images/images/WhatsApp Image 2016-11-30 at 11.45.59.jpeg"));

    connect(this->Level_Window,SIGNAL(level_changed(int)),this, SLOT(act_level(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_b_play_clicked()
{
    Game_window = new game_window();
    Game_window->setAttribute(Qt::WA_DeleteOnClose);
    Game_window->setModal(true);
    Game_window->p1.set_id((this->ui->l_id1->text()).toStdString());
    Game_window->p2.set_id(this->ui->l_id2->text().toStdString());

    Game_window->start_game(1,_level);

    Game_window->show();
}

void MainWindow::on_b_ai_play_clicked()
{
    Game_window = new game_window();
    Game_window->setAttribute(Qt::WA_DeleteOnClose);
    Game_window->setModal(true);
    Game_window->p1.set_id((this->ui->l_id1->text()).toStdString());
    Game_window->p2.set_id(this->ui->l_id2->text().toStdString());

    Game_window->start_game(2,_level);

    Game_window->show();
}

void MainWindow::on_b_exit_clicked()
{
    qApp->quit();
}

void MainWindow::on_b_sett_clicked()
{
    //Level_Window->setAttribute(Qt::WA_DeleteOnClose);
    Level_Window->setModal(true);

    Level_Window->show();
}

void MainWindow::act_level(int lvl)
{
    _level = lvl;
}
