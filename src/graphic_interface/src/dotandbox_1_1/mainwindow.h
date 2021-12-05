#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <game_window.h>
#include <level_window.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int _level = 2;
    level_window *Level_Window = new level_window();



private slots:
    void act_level(int);

    void on_b_play_clicked();

    void on_b_ai_play_clicked();

    void on_b_exit_clicked();

    void on_b_sett_clicked();

private:
    Ui::MainWindow *ui;
    game_window *Game_window;


};

#endif // MAINWINDOW_H
