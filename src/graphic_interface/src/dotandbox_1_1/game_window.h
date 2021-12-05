#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QDialog>
#include <QDebug>


#include <map_graphics.h>


namespace Ui {
class game_window;
}

class game_window : public QDialog
{
    Q_OBJECT

public:
    explicit game_window(QWidget *parent = 0);

    void start_game(ushort,int);
    //void make_move(QGraphicsSceneMouseEvent*);
    ~game_window();

    //void refresh_score();
    player p1, p2;
    ushort _p_or_ai;
    int level;


private slots:
    void act_score(uint,uint);
    void show_turn(int);



    void on_b_exit_clicked();

    void on_b_reset_clicked();

private:
    Ui::game_window *ui;
};

#endif // GAME_WINDOW_H
