#ifndef LEVEL_WINDOW_H
#define LEVEL_WINDOW_H

#include <QDialog>

namespace Ui {
class level_window;
}

class level_window : public QDialog
{
    Q_OBJECT

public:
    explicit level_window(QWidget *parent = 0);
    ~level_window();

    int _lvl = 2;

signals:
    void level_changed(int);

private slots:
    void set_arrow_level(int);

    void on_b_lv1_clicked();

    void on_b_lv2_clicked();

    void on_b_lv3_clicked();

    void on_b_lv4_clicked();

    void on_b_back_clicked();

private:
    Ui::level_window *ui;
};

#endif // LEVEL_WINDOW_H
