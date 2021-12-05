#ifndef MAP_GRAPHICS_H
#define MAP_GRAPHICS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QColor>
#include <QThread>
#include <QDebug>
#include <QApplication>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

#include <../../../dot_H/dot.H>
#include <../../../map/map.H>
#include <../../../player_H/player.H>
#include <../../../skyline/skyline_H/skyline.H>

#define PLAYER_TURN 2
#define PLAYER2_TURN 1
#define AI_TURN 1
#define AI_PLAYER 2
#define HUMAN_PLAYER 1

class map_graphics : public QGraphicsView
{
    Q_OBJECT
public:
    explicit map_graphics(QWidget *parent = 0);

    void start_graph(ushort _p_or_ai,int _level);
    void for_test();

    bool check_move(QPointF &point);
    bool draw_line(QPointF &point, QBrush &color);
    bool draw_line(QPointF&, QPointF&,QBrush&);
    void draw_box(QBrush&);
    void refresh_dots();
    void act_score();
    bool upper_box(dot<4,4> *,dot<4,4> *);
    bool lower_box(dot<4,4> *,dot<4,4> *);
    bool right_box(dot<4,4> *,dot<4,4> *);
    bool left_box(dot<4,4> *,dot<4,4> *);
    unsigned short where_to_draw(MOVE);
    QPointF dot_to_qpointf(std::pair<size_t,size_t>&dot_);
    std::pair<unsigned short, unsigned short> detect_dot(QPointF &point);

    uint p1_score, p2_score;


    //To delay:

public slots:
   void mousePressEvent(QMouseEvent *e);
   void mouseReleaseEvent(QMouseEvent *event);
   //void mouseMoveEvent()
   //void show_turn(int);
   void ia_play();


   void msleep(unsigned long msecs);

signals:
    void refresh_score(uint,uint);
    void set_turn(int);


private:
    //HUD Atributes:
    QGraphicsScene *scene;

    QRectF *dot_00, *dot_01, *dot_02, *dot_03,
           *dot_10, *dot_11, *dot_12, *dot_13,
           *dot_20, *dot_21, *dot_22, *dot_23,
           *dot_30, *dot_31, *dot_32, *dot_33,
    //Lines (l_Fila_Columna):
        //HORIZONTAL:
           *l_00_01, *l_01_02, *l_02_03,
           *l_10_11, *l_11_12, *l_12_13,
           *l_20_21, *l_21_22, *l_22_23,
           *l_30_31, *l_31_32, *l_32_33,

        //VERTICAL:
           *l_00_10, *l_10_20, *l_20_30,
           *l_01_11, *l_11_21, *l_21_31,
           *l_02_12, *l_12_22, *l_22_32,
           *l_03_13, *l_13_23, *l_23_33;

    //Bools to know which line has been marked:
    bool
    //HORIZONTAL:
       p_00_01, p_01_02, p_02_03,
       p_10_11, p_11_12, p_12_13,
       p_20_21, p_21_22, p_22_23,
       p_30_31, p_31_32, p_32_33,
    //VERTICAL:
       p_00_10, p_10_20, p_20_30,
       p_01_11, p_11_21, p_21_31,
       p_02_12, p_12_22, p_22_32,
       p_03_13, p_13_23, p_23_33;
    //Bools to know which square has been marked:
    bool
       //Sorted by horizontal:
       s1, s2, s3,
       s4, s5, s6,
       s7, s8, s9;


    //Cuadro Punto

    QRectF *box_01;

    QColor *c_free;
    QColor *c_marked;
    QColor *c_marked2;
    QBrush *b_free;
    QBrush *box_paint1;
    QBrush *box_paint2;
    QBrush *b_marked;
    QBrush *b_marked2;
    QPointF *click_point;

    //This is to know who's playing: 1 for human player, 2 for AI.
    unsigned short p_or_ai;
    //Game Atributes:
    map<4,4> *m_game;
    MOVE cur_mv;
    int turn;
    int level;
    skyline *sky;

};

#endif // MAP_GRAPHICS_H
