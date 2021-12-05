
#include "map_graphics.h"

map_graphics::map_graphics(QWidget *parent) :
    QGraphicsView(parent)
{
}

void map_graphics::start_graph(ushort _p_or_ai, int _level)
{
    //Initializing variables:
    p_or_ai = _p_or_ai;
    level = _level;
    turn = PLAYER_TURN;
    m_game = new map<4,4>;
    if(p_or_ai == AI_PLAYER)
    {
        sky = new skyline(*m_game, cur_mv,level);
    }
    p1_score = 0;
    p2_score = 0;
    c_free = new QColor("000000");
    box_paint1 = new QBrush("#0C6DEB",Qt::SolidPattern);
    box_paint2 = new QBrush("#EB7F0C",Qt::SolidPattern);
    c_marked = new QColor("#EB7F0C");
    c_marked2 = new QColor("#0C6DEB");
    b_free = new QBrush(*c_free,Qt::SolidPattern);
    b_marked = new QBrush(*c_marked, Qt::SolidPattern);
    b_marked2 = new QBrush(*c_marked2,Qt::SolidPattern);
        //more variables (a lot):
    //HORIZONTAL:
       p_00_01 = p_01_02 = p_02_03 =
       p_10_11 = p_11_12 = p_12_13 =
       p_20_21 = p_21_22 = p_22_23 =
       p_30_31 = p_31_32 = p_32_33 =

    //VERTICAL:
       p_00_10 = p_10_20 = p_20_30 =
       p_01_11 = p_11_21 = p_21_31 =
       p_02_12 = p_12_22 = p_22_32 =
       p_03_13 = p_13_23 = p_23_33 =
            false;

     //Sorted by horizontal:
       s1 = s2 = s3 =
       s4 = s5 = s6 =
       s7 = s8 = s9 =
            false;

    //Dots:
    dot_00 = new QRectF(0,30,20,20);
    dot_10 = new QRectF(0,130,20,20);
    dot_20 = new QRectF(0,230,20,20);
    dot_30 = new QRectF(0,330,20,20);

    dot_01 = new QRectF(100,30,20,20);
    dot_11 = new QRectF(100,130,20,20);
    dot_21 = new QRectF(100,230,20,20);
    dot_31 = new QRectF(100,330,20,20);

    dot_02 = new QRectF(200,30,20,20);
    dot_12 = new QRectF(200,130,20,20);
    dot_22 = new QRectF(200,230,20,20);
    dot_32 = new QRectF(200,330,20,20);

    dot_03 = new QRectF(300,30,20,20);
    dot_13 = new QRectF(300,130,20,20);
    dot_23 = new QRectF(300,230,20,20);
    dot_33 = new QRectF(300,330,20,20);

    //Lines:
        //vertical:
    l_00_10 = new QRectF(7,50,7,80);
    l_10_20 = new QRectF(7,150,7,80);
    l_20_30 = new QRectF(7,250,7,80);

    l_01_11 = new QRectF(107,50,7,80);
    l_11_21 = new QRectF(107,150,7,80);
    l_21_31 = new QRectF(107,250,7,80);

    l_02_12 = new QRectF(207,50,7,80);
    l_12_22 = new QRectF(207,150,7,80);
    l_22_32 = new QRectF(207,250,7,80);

    l_03_13 = new QRectF(307,50,7,80);
    l_13_23 = new QRectF(307,150,7,80);
    l_23_33 = new QRectF(307,250,7,80);

        //horizontal:
    l_00_01 = new QRectF(20,37,80,7);
    l_01_02 = new QRectF(120,37,80,7);
    l_02_03 = new QRectF(220,37,80,7);

    l_10_11 = new QRectF(20,137,80,7);
    l_11_12 = new QRectF(120,137,80,7);
    l_12_13 = new QRectF(220,137,80,7);

    l_20_21 = new QRectF(20,237,80,7);
    l_21_22 = new QRectF(120,237,80,7);
    l_22_23 = new QRectF(220,237,80,7);

    l_30_31 = new QRectF(20,337,80,7);
    l_31_32 = new QRectF(120,337,80,7);
    l_32_33 = new QRectF(220,337,80,7);

    //Cuadro Punto

    box_01 = new QRectF(10,37,100,105);


    this->scene = new QGraphicsScene();
    this->setScene(scene);

    //Adding dots:
    scene->addEllipse(*dot_00,*c_free,*b_free);
    scene->addEllipse(*dot_10,*c_free,*b_free);
    scene->addEllipse(*dot_20,*c_free,*b_free);
    scene->addEllipse(*dot_30,*c_free,*b_free);

    scene->addEllipse(*dot_01,*c_free,*b_free);
    scene->addEllipse(*dot_11,*c_free,*b_free);
    scene->addEllipse(*dot_21,*c_free,*b_free);
    scene->addEllipse(*dot_31,*c_free,*b_free);

    scene->addEllipse(*dot_02,*c_free,*b_free);
    scene->addEllipse(*dot_12,*c_free,*b_free);
    scene->addEllipse(*dot_22,*c_free,*b_free);
    scene->addEllipse(*dot_32,*c_free,*b_free);

    scene->addEllipse(*dot_03,*c_free,*b_free);
    scene->addEllipse(*dot_13,*c_free,*b_free);
    scene->addEllipse(*dot_23,*c_free,*b_free);
    scene->addEllipse(*dot_33,*c_free,*b_free);


    //Adding box point

    //scene->addRect(*box_01,*c_free,*box_paint1);

    act_score();
    emit refresh_score(p1_score,p2_score);
    emit set_turn(turn);
}


void map_graphics::mousePressEvent(QMouseEvent *e)
{
    click_point = new QPointF(this->mapToScene(e->pos()));
    if(turn==PLAYER_TURN)
    {
        if(e->button() == Qt::LeftButton)
        {
            if(dot_00->contains(*click_point))
                scene->addEllipse(*dot_00,*c_marked,*b_marked);

            else if(dot_01->contains(*click_point))
                scene->addEllipse(*dot_01,*c_marked,*b_marked);

            else if(dot_02->contains(*click_point))
                scene->addEllipse(*dot_02,*c_marked,*b_marked);

            else if(dot_03->contains(*click_point))
                scene->addEllipse(*dot_03,*c_marked,*b_marked);

            else if(dot_10->contains(*click_point))
                scene->addEllipse(*dot_10,*c_marked,*b_marked);

            else if(dot_11->contains(*click_point))
                scene->addEllipse(*dot_11,*c_marked,*b_marked);

            else if(dot_12->contains(*click_point))
                scene->addEllipse(*dot_12,*c_marked,*b_marked);

            else if(dot_13->contains(*click_point))
                scene->addEllipse(*dot_13,*c_marked,*b_marked);

            else if(dot_20->contains(*click_point))
                scene->addEllipse(*dot_20,*c_marked,*b_marked);

            else if(dot_21->contains(*click_point))
                scene->addEllipse(*dot_21,*c_marked,*b_marked);

            else if(dot_22->contains(*click_point))
                scene->addEllipse(*dot_22,*c_marked,*b_marked);

            else if(dot_23->contains(*click_point))
                scene->addEllipse(*dot_23,*c_marked,*b_marked);

            else if(dot_30->contains(*click_point))
                scene->addEllipse(*dot_30,*c_marked,*b_marked);

            else if(dot_31->contains(*click_point))
                scene->addEllipse(*dot_31,*c_marked,*b_marked);

            else if(dot_32->contains(*click_point))
                scene->addEllipse(*dot_32,*c_marked,*b_marked);

            else if(dot_33->contains(*click_point))
                scene->addEllipse(*dot_33,*c_marked,*b_marked);
        }
    }
    if(turn==PLAYER2_TURN)
    {
        if(e->button() == Qt::LeftButton)
        {
            if(dot_00->contains(*click_point))
                scene->addEllipse(*dot_00,*c_marked2,*b_marked2);

            else if(dot_01->contains(*click_point))
                scene->addEllipse(*dot_01,*c_marked2,*b_marked2);

            else if(dot_02->contains(*click_point))
                scene->addEllipse(*dot_02,*c_marked2,*b_marked2);

            else if(dot_03->contains(*click_point))
                scene->addEllipse(*dot_03,*c_marked2,*b_marked2);

            else if(dot_10->contains(*click_point))
                scene->addEllipse(*dot_10,*c_marked2,*b_marked2);

            else if(dot_11->contains(*click_point))
                scene->addEllipse(*dot_11,*c_marked2,*b_marked2);

            else if(dot_12->contains(*click_point))
                scene->addEllipse(*dot_12,*c_marked2,*b_marked2);

            else if(dot_13->contains(*click_point))
                scene->addEllipse(*dot_13,*c_marked2,*b_marked2);

            else if(dot_20->contains(*click_point))
                scene->addEllipse(*dot_20,*c_marked2,*b_marked2);

            else if(dot_21->contains(*click_point))
                scene->addEllipse(*dot_21,*c_marked2,*b_marked2);

            else if(dot_22->contains(*click_point))
                scene->addEllipse(*dot_22,*c_marked2,*b_marked2);

            else if(dot_23->contains(*click_point))
                scene->addEllipse(*dot_23,*c_marked2,*b_marked2);

            else if(dot_30->contains(*click_point))
                scene->addEllipse(*dot_30,*c_marked2,*b_marked2);

            else if(dot_31->contains(*click_point))
                scene->addEllipse(*dot_31,*c_marked2,*b_marked2);

            else if(dot_32->contains(*click_point))
                scene->addEllipse(*dot_32,*c_marked2,*b_marked2);

            else if(dot_33->contains(*click_point))
                scene->addEllipse(*dot_33,*c_marked2,*b_marked2);
        }

    }

}

void map_graphics::mouseReleaseEvent(QMouseEvent *event)
{
    //Select 1vsAI game:
    if(p_or_ai == AI_PLAYER){
        if(turn==PLAYER_TURN)
        {
            QPointF release_point = this->mapToScene(event->pos());
            std::get<0>(cur_mv) = detect_dot(*click_point);
            std::get<1>(cur_mv) = detect_dot(release_point);

            if(check_move(release_point))
            {
                if(draw_line(release_point, *b_marked))
                {

                    p2_score = m_game->get_p2_score();
                    m_game->play(cur_mv,PLAYER_TURN);

                    if(p2_score != m_game->get_p2_score())
                    {
                        draw_box(*box_paint2);
                        sky->blind_move();
                    }
                    else
                    {
                        sky->check_play(*m_game,cur_mv,PLAYER_TURN);
                        turn = AI_TURN;

                    }
                }
            }
        }
        if(turn==AI_TURN)
        {
            //ia_play();
            QTimer::singleShot(500,this,SLOT(ia_play()));


        }
    }

    //Select 1vs1 game:
    if(p_or_ai == HUMAN_PLAYER)
    {
        QPointF release_point = this->mapToScene(event->pos());
        std::get<0>(cur_mv) = detect_dot(*click_point);
        std::get<1>(cur_mv) = detect_dot(release_point);

        if(check_move(release_point))
        {
          if(turn == PLAYER_TURN)
          {
              if(draw_line(release_point, *b_marked))
              {

                  p2_score = m_game->get_p2_score();
                  m_game->play(cur_mv,PLAYER_TURN);
                  if(p2_score == m_game->get_p2_score())
                      turn = PLAYER2_TURN;
                  else
                      draw_box(*box_paint2);
              }

          }
          else
          {
              if(draw_line(release_point, *b_marked2))
              {

                  p1_score = m_game->get_p1_score();
                  m_game->play(cur_mv,PLAYER2_TURN);
                  if(p1_score == m_game->get_p1_score())
                      turn = PLAYER_TURN;
                  else{
                      draw_box(*box_paint1);
                  }
              }
          }
        }
    }

    act_score();
    emit refresh_score(p2_score,p1_score);
    emit set_turn(turn);
    refresh_dots();
}

void map_graphics::ia_play()
{
        if(turn==AI_TURN and !m_game->is_full())
        {

            p1_score = m_game->get_p1_score();
            cur_mv = sky->AI_play();

            m_game->play(cur_mv,AI_TURN);

            QPointF par1 = dot_to_qpointf(std::get<0>(cur_mv));
            QPointF par2 = dot_to_qpointf(std::get<1>(cur_mv));

            /*if(dot_00->contains(par2))
                scene->addEllipse(*dot_00,*c_marked,*b_marked);
            else if(dot_01->contains(par2))
                scene->addEllipse(*dot_01,*c_marked,*b_marked);
            else if(dot_02->contains(par2))
                scene->addEllipse(*dot_02,*c_marked,*b_marked);
            else if(dot_03->contains(par2))
                scene->addEllipse(*dot_03,*c_marked,*b_marked);
            else if(dot_10->contains(par2))
                scene->addEllipse(*dot_10,*c_marked,*b_marked);
            else if(dot_11->contains(par2))
                scene->addEllipse(*dot_11,*c_marked,*b_marked);
            else if(dot_12->contains(par2))
                scene->addEllipse(*dot_12,*c_marked,*b_marked);
            else if(dot_13->contains(par2))
                scene->addEllipse(*dot_13,*c_marked,*b_marked);
            else if(dot_20->contains(par2))
                scene->addEllipse(*dot_20,*c_marked,*b_marked);
            else if(dot_21->contains(par2))
                scene->addEllipse(*dot_21,*c_marked,*b_marked);
            else if(dot_22->contains(par2))
                scene->addEllipse(*dot_22,*c_marked,*b_marked);
            else if(dot_23->contains(par2))
                scene->addEllipse(*dot_23,*c_marked,*b_marked);
            else if(dot_30->contains(par2))
                scene->addEllipse(*dot_30,*c_marked,*b_marked);
            else if(dot_31->contains(par2))
                scene->addEllipse(*dot_31,*c_marked,*b_marked);
            else if(dot_32->contains(par2))
                scene->addEllipse(*dot_32,*c_marked,*b_marked);
            else if(dot_33->contains(par2))
                scene->addEllipse(*dot_33,*c_marked,*b_marked);*/

            if((draw_line(par1, par2, *b_marked2)))
            {

                if(p1_score != m_game->get_p1_score())
                {

                    draw_box(*box_paint1);
                    sky->check_play(*m_game,cur_mv,AI_TURN);
                    QTimer::singleShot(750,this,SLOT(ia_play()));

                }
                else
                {
                    //sky->check_play(*m_game, cur_mv,IA_TURN);
                    sky->blind_move();
                    turn = PLAYER_TURN;
                }

                act_score();
                emit refresh_score(p2_score,p1_score);
                emit set_turn(turn);
                refresh_dots();
            }
       }

}


std::pair<unsigned short,unsigned short> map_graphics::detect_dot(QPointF &point)
{
    std::pair<unsigned short,unsigned short> dot;

    if(dot_00->contains(point))
    {
        return dot = std::make_pair(0,0);
    }
    else if(dot_01->contains(point))
    {
        return dot = std::make_pair(0,1);

    }
    else if(dot_02->contains(point))
    {
        return dot = std::make_pair(0,2);

    }
    else if(dot_03->contains(point))
    {
        return dot = std::make_pair(0,3);

    }
    else if(dot_10->contains(point))
    {
        return dot = std::make_pair(1,0);

    }
    else if(dot_11->contains(point))
    {
        return dot = std::make_pair(1,1);

    }
    else if(dot_12->contains(point))
    {
        return dot = std::make_pair(1,2);

    }
    else if(dot_13->contains(point))
    {
        return dot = std::make_pair(1,3);

    }
    else if(dot_20->contains(point))
    {
        return dot = std::make_pair(2,0);

    }
    else if(dot_21->contains(point))
    {
        return dot = std::make_pair(2,1);

    }
    else if(dot_22->contains(point))
    {
        return dot = std::make_pair(2,2);

    }
    else if(dot_23->contains(point))
    {
        return dot = std::make_pair(2,3);

    }
    else if(dot_30->contains(point))
    {
        return dot = std::make_pair(3,0);

    }
    else if(dot_31->contains(point))
    {
        return dot = std::make_pair(3,1);

    }
    else if(dot_32->contains(point))
    {
        return dot = std::make_pair(3,2);

    }
    else if(dot_33->contains(point))
    {
        return dot = std::make_pair(3,3);

    }
}

void map_graphics::msleep(unsigned long msecs){QThread::msleep(msecs);}

bool map_graphics::check_move(QPointF &point)
{
    //For dot00:
    if( (dot_00->contains(*click_point) and (dot_01->contains(point) or
                                           dot_10->contains(point)))
            and (!p_00_01 or !p_00_10))
        return true;
    //For dot01:
    if( (dot_01->contains(*click_point) and (dot_00->contains(point) or
                                             dot_11->contains(point) or
                                             dot_02->contains(point)) )
            and (!p_00_01 or !p_01_11 or !p_01_02) )
        return true;
    //For dot02:
    if( (dot_02->contains(*click_point) and (dot_01->contains(point) or
                                            dot_03->contains(point) or
                                            dot_12->contains(point)) )
            and (!p_02_03 or !p_01_02 or !p_02_12 ))
        return true;
    //For dot03:
    if((dot_03->contains(*click_point) and (dot_02->contains(point) or
                                           dot_13->contains(point)) )
            and (!p_03_13 or !p_02_03))

        return true;
    //For dot10
    if((dot_10->contains(*click_point) and (dot_00->contains(point) or
                                           dot_11->contains(point) or
                                           dot_20->contains(point)) )
            and (!p_10_11 or !p_10_20 or !p_00_10))

        return true;
    //For dot11:
    if((dot_11->contains(*click_point) and (dot_01->contains(point) or
                                           dot_12->contains(point) or
                                           dot_21->contains(point) or
                                           dot_10->contains(point)) )
            and (!p_11_12 or !p_11_21 or !p_10_11 or !p_01_11))

        return true;
    //For dot12:
    if((dot_12->contains(*click_point) and (dot_02->contains(point) or
                                           dot_11->contains(point) or
                                           dot_13->contains(point) or
                                           dot_22->contains(point)) )
            and (!p_02_12 or !p_12_13 or !p_11_12 or !p_12_22))

        return true;
    //For dot13:
    if((dot_13->contains(*click_point) and (dot_03->contains(point) or
                                           dot_12->contains(point) or
                                           dot_23->contains(point)) )
            and (!p_13_23 or !p_03_13 or !p_12_13))

        return true;
    //For dot20:
    if((dot_20->contains(*click_point) and (dot_10->contains(point) or
                                           dot_30->contains(point) or
                                           dot_21->contains(point)) )
            and (!p_20_21 or !p_20_30 or !p_10_20))

        return true;
    //For dot21:
    if((dot_21->contains(*click_point) and (dot_11->contains(point) or
                                           dot_20->contains(point) or
                                           dot_31->contains(point) or
                                           dot_22->contains(point)) )
            and (!p_21_22 or !p_21_31 or !p_11_21 or !p_20_21))

        return true;
    //For dot22:
    if((dot_22->contains(*click_point) and (dot_12->contains(point) or
                                           dot_23->contains(point) or
                                           dot_32->contains(point) or
                                           dot_21->contains(point)) )
            and (!p_12_22 or !p_22_23 or !p_22_32 or !p_21_22))

        return true;
    //For dot23:
    if((dot_23->contains(*click_point) and (dot_13->contains(point) or
                                           dot_22->contains(point) or
                                           dot_33->contains(point)) )
            and (!p_13_23 or !p_22_23 or !p_23_33))

        return true;
    //For dot30:
    if((dot_30->contains(*click_point) and (dot_20->contains(point) or
                                           dot_31->contains(point)) )
            and (!p_20_30 or !p_30_31))

        return true;
    //For dot31:
    if((dot_31->contains(*click_point) and (dot_21->contains(point) or
                                           dot_30->contains(point) or
                                           dot_32->contains(point)) )
            and (!p_21_31 or !p_30_31 or !p_31_32))

        return true;
    //For dot32:
    if((dot_32->contains(*click_point) and (dot_22->contains(point) or
                                           dot_31->contains(point) or
                                           dot_33->contains(point)) )
            and (!p_32_33 or !p_22_32 or !p_31_32))

        return true;

    //For dot33:
    if((dot_33->contains(*click_point) and (dot_32->contains(point) or
                                           dot_23->contains(point)) )
            and (!p_32_33 or !p_23_33))

        return true;

    return false;
}

bool map_graphics::draw_line(QPointF &point, QBrush &color)
{    //Horizontal:
    if( ((dot_00->contains(*click_point) and dot_01->contains(point)) or
       (dot_00->contains(point) and dot_01->contains(*click_point))) and
            !p_00_01)
    {
        scene->addRect(*l_00_01,*c_free,color);
        p_00_01 = true;
        return true;
    }
    if( ((dot_01->contains(*click_point) and dot_02->contains(point)) or
       (dot_01->contains(point) and dot_02->contains(*click_point))) and
            !p_01_02)
    {
        scene->addRect(*l_01_02,*c_free,color);
        p_01_02 = true;
        return true;
    }

    if( ((dot_02->contains(*click_point) and dot_03->contains(point)) or
       (dot_02->contains(point) and dot_03->contains(*click_point))) and
            !p_02_03)
       {
        scene->addRect(*l_02_03,*c_free,color);
        p_02_03 = true;
        return true;
      };


    if( ((dot_10->contains(*click_point) and dot_11->contains(point)) or
       (dot_10->contains(point) and dot_11->contains(*click_point))) and
            !p_10_11)
       {
        scene->addRect(*l_10_11,*c_free,color);
        p_10_11 = true;
        return true;
      };

    if( ((dot_11->contains(*click_point) and dot_12->contains(point)) or
       (dot_11->contains(point) and dot_12->contains(*click_point))) and
            !p_11_12)
       {
        scene->addRect(*l_11_12,*c_free,color);
        p_11_12 = true;
        return true;
      };

    if( ((dot_12->contains(*click_point) and dot_13->contains(point)) or
       (dot_12->contains(point) and dot_13->contains(*click_point))) and
            !p_12_13)
       {
        scene->addRect(*l_12_13,*c_free,color);
        p_12_13 = true;
        return true;
      };

    if( ((dot_20->contains(*click_point) and dot_21->contains(point)) or
       (dot_20->contains(point) and dot_21->contains(*click_point))) and
            !p_20_21)
       {
        scene->addRect(*l_20_21,*c_free,color);
        p_20_21 = true;
        return true;
      };

    if( ((dot_21->contains(*click_point) and dot_22->contains(point)) or
       (dot_21->contains(point) and dot_22->contains(*click_point))) and
            !p_21_22)
       {
        scene->addRect(*l_21_22,*c_free,color);
        p_21_22 = true;
        return true;
      };

    if( ((dot_22->contains(*click_point) and dot_23->contains(point)) or
       (dot_22->contains(point) and dot_23->contains(*click_point))) and
            !p_22_23)
       {
        scene->addRect(*l_22_23,*c_free,color);
        p_22_23 = true;
        return true;
      };

    if( ((dot_30->contains(*click_point) and dot_31->contains(point)) or
       (dot_30->contains(point) and dot_31->contains(*click_point))) and
            !p_30_31)
       {
        scene->addRect(*l_30_31,*c_free,color);
        p_30_31 = true;
        return true;
      };

    if( ((dot_31->contains(*click_point) and dot_32->contains(point)) or
       (dot_31->contains(point) and dot_32->contains(*click_point))) and
            !p_31_32)
       {
        scene->addRect(*l_31_32,*c_free,color);
        p_31_32 = true;
        return true;
      };

    if( ((dot_32->contains(*click_point) and dot_33->contains(point)) or
       (dot_32->contains(point) and dot_33->contains(*click_point))) and
            !p_32_33)
       {
        scene->addRect(*l_32_33,*c_free,color);
        p_32_33 = true;
        return true;
      };


    //Vertical:
    if( ((dot_00->contains(*click_point) and dot_10->contains(point)) or
       (dot_00->contains(point) and dot_10->contains(*click_point))) and
            !p_00_10)
       {
        scene->addRect(*l_00_10,*c_free,color);
        p_00_10 = true;
        return true;
      };

    if( ((dot_10->contains(*click_point) and dot_20->contains(point)) or
       (dot_10->contains(point) and dot_20->contains(*click_point))) and
            !p_10_20)
       {
        scene->addRect(*l_10_20,*c_free,color);
        p_10_20 = true;
        return true;
      };

    if( ((dot_20->contains(*click_point) and dot_30->contains(point)) or
       (dot_20->contains(point) and dot_30->contains(*click_point))) and
            !p_20_30)
       {
        scene->addRect(*l_20_30,*c_free,color);
        p_20_30 = true;
        return true;
      };

    if( ((dot_01->contains(*click_point) and dot_11->contains(point)) or
       (dot_01->contains(point) and dot_11->contains(*click_point))) and
            !p_01_11)
       {
        scene->addRect(*l_01_11,*c_free,color);
        p_01_11 = true;
        return true;
      };

    if( ((dot_11->contains(*click_point) and dot_21->contains(point)) or
       (dot_11->contains(point) and dot_21->contains(*click_point))) and
            !p_11_21)
       {
        scene->addRect(*l_11_21,*c_free,color);
        p_11_21 = true;
        return true;
      };

    if( ((dot_21->contains(*click_point) and dot_31->contains(point)) or
       (dot_21->contains(point) and dot_31->contains(*click_point))) and
            !p_21_31)
       {
        scene->addRect(*l_21_31,*c_free,color);
        p_21_31 = true;
        return true;
      };

    if( ((dot_02->contains(*click_point) and dot_12->contains(point)) or
       (dot_02->contains(point) and dot_12->contains(*click_point))) and
            !p_02_12)
       {
        scene->addRect(*l_02_12,*c_free,color);
        p_02_12 = true;
        return true;
      };

    if( ((dot_12->contains(*click_point) and dot_22->contains(point)) or
       (dot_12->contains(point) and dot_22->contains(*click_point))) and
            !p_12_22)
       {
        scene->addRect(*l_12_22,*c_free,color);
        p_12_22 = true;
        return true;
      };

    if( ((dot_22->contains(*click_point) and dot_32->contains(point)) or
       (dot_22->contains(point) and dot_32->contains(*click_point))) and
            !p_22_32)
       {
        scene->addRect(*l_22_32,*c_free,color);
        p_22_32 = true;
        return true;
      };

    if( ((dot_03->contains(*click_point) and dot_13->contains(point)) or
       (dot_03->contains(point) and dot_13->contains(*click_point))) and
            !p_03_13)
       {
        scene->addRect(*l_03_13,*c_free,color);
        p_03_13 = true;
        return true;
      };

    if( ((dot_13->contains(*click_point) and dot_23->contains(point)) or
       (dot_13->contains(point) and dot_23->contains(*click_point))) and
            !p_13_23)
       {
        scene->addRect(*l_13_23,*c_free,color);
        p_13_23 = true;
        return true;
      };

    if( ((dot_23->contains(*click_point) and dot_33->contains(point)) or
       (dot_23->contains(point) and dot_33->contains(*click_point))) and
            !p_23_33)
       {
        scene->addRect(*l_23_33,*c_free,color);
        p_23_33 = true;
        return true;
      };

      return false;
}

bool map_graphics::draw_line(QPointF &first_point, QPointF &second_point, QBrush &color)
{
    //Horizontal:
    if( ((dot_00->contains(first_point) and dot_01->contains(second_point)) or
       (dot_00->contains(second_point) and dot_01->contains(first_point))) and
            !p_00_01)
    {
        scene->addRect(*l_00_01,*c_free,color);
        p_00_01 = true;
        return true;
    }
    if( ((dot_01->contains(first_point) and dot_02->contains(second_point)) or
       (dot_01->contains(second_point) and dot_02->contains(first_point))) and
            !p_01_02)
    {
        scene->addRect(*l_01_02,*c_free,color);
        p_01_02 = true;
        return true;
    }

    if( ((dot_02->contains(first_point) and dot_03->contains(second_point)) or
       (dot_02->contains(second_point) and dot_03->contains(first_point))) and
            !p_02_03)
       {
        scene->addRect(*l_02_03,*c_free,color);
        p_02_03 = true;
        return true;
      };


    if( ((dot_10->contains(first_point) and dot_11->contains(second_point)) or
       (dot_10->contains(second_point) and dot_11->contains(first_point))) and
            !p_10_11)
       {
        scene->addRect(*l_10_11,*c_free,color);
        p_10_11 = true;
        return true;
      };

    if( ((dot_11->contains(first_point) and dot_12->contains(second_point)) or
       (dot_11->contains(second_point) and dot_12->contains(first_point))) and
            !p_11_12)
       {
        scene->addRect(*l_11_12,*c_free,color);
        p_11_12 = true;
        return true;
      };

    if( ((dot_12->contains(first_point) and dot_13->contains(second_point)) or
       (dot_12->contains(second_point) and dot_13->contains(first_point))) and
            !p_12_13)
       {
        scene->addRect(*l_12_13,*c_free,color);
        p_12_13 = true;
        return true;
      };

    if( ((dot_20->contains(first_point) and dot_21->contains(second_point)) or
       (dot_20->contains(second_point) and dot_21->contains(first_point))) and
            !p_20_21)
       {
        scene->addRect(*l_20_21,*c_free,color);
        p_20_21 = true;
        return true;
      };

    if( ((dot_21->contains(first_point) and dot_22->contains(second_point)) or
       (dot_21->contains(second_point) and dot_22->contains(first_point))) and
            !p_21_22)
       {
        scene->addRect(*l_21_22,*c_free,color);
        p_21_22 = true;
        return true;
      };

    if( ((dot_22->contains(first_point) and dot_23->contains(second_point)) or
       (dot_22->contains(second_point) and dot_23->contains(first_point))) and
            !p_22_23)
       {
        scene->addRect(*l_22_23,*c_free,color);
        p_22_23 = true;
        return true;
      };

    if( ((dot_30->contains(first_point) and dot_31->contains(second_point)) or
       (dot_30->contains(second_point) and dot_31->contains(first_point))) and
            !p_30_31)
       {
        scene->addRect(*l_30_31,*c_free,color);
        p_30_31 = true;
        return true;
      };

    if( ((dot_31->contains(first_point) and dot_32->contains(second_point)) or
       (dot_31->contains(second_point) and dot_32->contains(first_point))) and
            !p_31_32)
       {
        scene->addRect(*l_31_32,*c_free,color);
        p_31_32 = true;
        return true;
      };

    if( ((dot_32->contains(first_point) and dot_33->contains(second_point)) or
       (dot_32->contains(second_point) and dot_33->contains(first_point))) and
            !p_32_33)
       {
        scene->addRect(*l_32_33,*c_free,color);
        p_32_33 = true;
        return true;
      };


    //Vertical:
    if( ((dot_00->contains(first_point) and dot_10->contains(second_point)) or
       (dot_00->contains(second_point) and dot_10->contains(first_point))) and
            !p_00_10)
       {
        scene->addRect(*l_00_10,*c_free,color);
        p_00_10 = true;
        return true;
      };

    if( ((dot_10->contains(first_point) and dot_20->contains(second_point)) or
       (dot_10->contains(second_point) and dot_20->contains(first_point))) and
            !p_10_20)
       {
        scene->addRect(*l_10_20,*c_free,color);
        p_10_20 = true;
        return true;
      };

    if( ((dot_20->contains(first_point) and dot_30->contains(second_point)) or
       (dot_20->contains(second_point) and dot_30->contains(first_point))) and
            !p_20_30)
       {
        scene->addRect(*l_20_30,*c_free,color);
        p_20_30 = true;
        return true;
      };

    if( ((dot_01->contains(first_point) and dot_11->contains(second_point)) or
       (dot_01->contains(second_point) and dot_11->contains(first_point))) and
            !p_01_11)
       {
        scene->addRect(*l_01_11,*c_free,color);
        p_01_11 = true;
        return true;
      };

    if( ((dot_11->contains(first_point) and dot_21->contains(second_point)) or
       (dot_11->contains(second_point) and dot_21->contains(first_point))) and
            !p_11_21)
       {
        scene->addRect(*l_11_21,*c_free,color);
        p_11_21 = true;
        return true;
      };

    if( ((dot_21->contains(first_point) and dot_31->contains(second_point)) or
       (dot_21->contains(second_point) and dot_31->contains(first_point))) and
            !p_21_31)
       {
        scene->addRect(*l_21_31,*c_free,color);
        p_21_31 = true;
        return true;
      };

    if( ((dot_02->contains(first_point) and dot_12->contains(second_point)) or
       (dot_02->contains(second_point) and dot_12->contains(first_point))) and
            !p_02_12)
       {
        scene->addRect(*l_02_12,*c_free,color);
        p_02_12 = true;
        return true;
      };

    if( ((dot_12->contains(first_point) and dot_22->contains(second_point)) or
       (dot_12->contains(second_point) and dot_22->contains(first_point))) and
            !p_12_22)
       {
        scene->addRect(*l_12_22,*c_free,color);
        p_12_22 = true;
        return true;
      };

    if( ((dot_22->contains(first_point) and dot_32->contains(second_point)) or
       (dot_22->contains(second_point) and dot_32->contains(first_point))) and
            !p_22_32)
       {
        scene->addRect(*l_22_32,*c_free,color);
        p_22_32 = true;
        return true;
      };

    if( ((dot_03->contains(first_point) and dot_13->contains(second_point)) or
       (dot_03->contains(second_point) and dot_13->contains(first_point))) and
            !p_03_13)
       {
        scene->addRect(*l_03_13,*c_free,color);
        p_03_13 = true;
        return true;
      };

    if( ((dot_13->contains(first_point) and dot_23->contains(second_point)) or
       (dot_13->contains(second_point) and dot_23->contains(first_point))) and
            !p_13_23)
       {
        scene->addRect(*l_13_23,*c_free,color);
        p_13_23 = true;
        return true;
      };

    if( ((dot_23->contains(first_point) and dot_33->contains(second_point)) or
       (dot_23->contains(second_point) and dot_33->contains(first_point))) and
            !p_23_33)
       {
        scene->addRect(*l_23_33,*c_free,color);
        p_23_33 = true;
        return true;
      };

    return false;
}

void map_graphics::refresh_dots()
{
    scene->addEllipse(*dot_00,*c_free,*b_free);
    scene->addEllipse(*dot_10,*c_free,*b_free);
    scene->addEllipse(*dot_20,*c_free,*b_free);
    scene->addEllipse(*dot_30,*c_free,*b_free);

    scene->addEllipse(*dot_01,*c_free,*b_free);
    scene->addEllipse(*dot_11,*c_free,*b_free);
    scene->addEllipse(*dot_21,*c_free,*b_free);
    scene->addEllipse(*dot_31,*c_free,*b_free);

    scene->addEllipse(*dot_02,*c_free,*b_free);
    scene->addEllipse(*dot_12,*c_free,*b_free);
    scene->addEllipse(*dot_22,*c_free,*b_free);
    scene->addEllipse(*dot_32,*c_free,*b_free);

    scene->addEllipse(*dot_03,*c_free,*b_free);
    scene->addEllipse(*dot_13,*c_free,*b_free);
    scene->addEllipse(*dot_23,*c_free,*b_free);
    scene->addEllipse(*dot_33,*c_free,*b_free);
}

void map_graphics::act_score()
{
    p1_score = m_game->get_p1_score();
    p2_score = m_game->get_p2_score();
}

QPointF map_graphics::dot_to_qpointf(std::pair<size_t, size_t> &dot_)
{
    QPointF click_;  //Click point to return

    //First row:
    if(std::get<0>(dot_) == 0)
    {
        //First column:
        if(std::get<1>(dot_) == 0)
            return click_ = dot_00->center();
        //Second column:
        if(std::get<1>(dot_) == 1)
            return click_ = dot_01->center();
        //Third column:
        if(std::get<1>(dot_) == 2)
            return click_ = dot_02->center();
        //Quarter column:
        if(std::get<1>(dot_) == 3)
            return click_ = dot_03->center();
    }

    //Second row:
    if(std::get<0>(dot_) == 1)
    {
        //First column:
        if(std::get<1>(dot_) == 0)
            return click_ = dot_10->center();

        //Second column:
        if(std::get<1>(dot_) == 1)
            return click_ = dot_11->center();

        //Third column:
        if(std::get<1>(dot_) == 2)
            return click_ = dot_12->center();

        //Quarter column:
        if(std::get<1>(dot_) == 3)
            return click_ = dot_13->center();
    }

    //Third row:
    if(std::get<0>(dot_) == 2)
    {
        //First column:
        if(std::get<1>(dot_) == 0)
            return click_ = dot_20->center();

        //Second column:
        if(std::get<1>(dot_) == 1)
            return click_ = dot_21->center();

        //Third column:
        if(std::get<1>(dot_) == 2)
            return click_ = dot_22->center();

        //Quarter column:
        if(std::get<1>(dot_) == 3)
            return click_ = dot_23->center();
    }

    //Quarter row:
    if(std::get<0>(dot_) == 3)
    {
        //First column:
        if(std::get<1>(dot_) == 0)
            return click_ = dot_30->center();

        //Second column:
        if(std::get<1>(dot_) == 1)
            return click_ = dot_31->center();

        //Third column:
        if(std::get<1>(dot_) == 2)
            return click_ = dot_32->center();

        //Quarter column:
        if(std::get<1>(dot_) == 3)
            return click_ = dot_33->center();
    }

    return click_ = QPointF(-1,-1);
}

bool map_graphics::upper_box(dot<4,4> *dot_1,dot<4,4> *dot_2)
{
  MOVE try_mv;
  std::get<0>(try_mv) = std::pair<size_t,size_t>(std::get<0>(dot_1->get_pos()) - 1,std::get<1>(dot_1->get_pos()));
  std::get<1>(try_mv) = std::pair<size_t,size_t>(std::get<0>(dot_2->get_pos()) - 1,std::get<1>(dot_2->get_pos()));

  if(not m_game->was_point(try_mv))
    return false;

  std::get<0>(try_mv) =dot_1->get_pos();
  std::get<1>(try_mv) = std::pair<size_t,size_t>(std::get<0>(dot_1->get_pos()) - 1,std::get<1>(dot_1->get_pos()));

  if(not m_game->was_point(try_mv))
    return false;

  std::get<0>(try_mv) =dot_2->get_pos();
  std::get<1>(try_mv) = std::pair<size_t,size_t>(std::get<0>(dot_2->get_pos()) - 1,std::get<1>(dot_2->get_pos()));

  if(not m_game->was_point(try_mv))
   return false;

  return true;
}

bool map_graphics::lower_box(dot<4,4> *dot_1,dot<4,4> *dot_2)
{
  MOVE try_mv;
  std::get<0>(try_mv) = std::pair<size_t,size_t>(std::get<0>(dot_1->get_pos()) + 1,std::get<1>(dot_1->get_pos()));
  std::get<1>(try_mv) = std::pair<size_t,size_t>(std::get<0>(dot_2->get_pos()) + 1,std::get<1>(dot_2->get_pos()));

  if(not m_game->was_point(try_mv))
    return false;

  std::get<0>(try_mv) =dot_1->get_pos();
  std::get<1>(try_mv) = std::pair<size_t,size_t>(std::get<0>(dot_1->get_pos()) + 1,std::get<1>(dot_1->get_pos()));

  if(not m_game->was_point(try_mv))
    return false;

  std::get<0>(try_mv) =dot_2->get_pos();
  std::get<1>(try_mv) = std::pair<size_t,size_t>(std::get<0>(dot_2->get_pos()) + 1,std::get<1>(dot_2->get_pos()));

  if(not m_game->was_point(try_mv))
   return false;

  return true;
}

bool map_graphics::left_box(dot<4,4> *dot_1,dot<4,4> *dot_2)
{
  MOVE try_mv;
  std::get<0>(try_mv) = std::pair<size_t,size_t>(std::get<0>(dot_1->get_pos()),std::get<1>(dot_1->get_pos()) - 1);
  std::get<1>(try_mv) = std::pair<size_t,size_t>(std::get<0>(dot_2->get_pos()),std::get<1>(dot_2->get_pos()) - 1);

  if(not m_game->was_point(try_mv))
    return false;

  std::get<0>(try_mv) =dot_1->get_pos();
  std::get<1>(try_mv) = std::pair<size_t,size_t>(std::get<0>(dot_1->get_pos()),std::get<1>(dot_1->get_pos()) - 1);

  if(not m_game->was_point(try_mv))
    return false;

  std::get<0>(try_mv) =dot_2->get_pos();
  std::get<1>(try_mv) = std::pair<size_t,size_t>(std::get<0>(dot_2->get_pos()),std::get<1>(dot_2->get_pos()) - 1);

  if(not m_game->was_point(try_mv))
   return false;

  return true;
}

bool map_graphics::right_box(dot<4,4> *dot_1,dot<4,4> *dot_2)
{
  MOVE try_mv;
  std::get<0>(try_mv) = std::pair<size_t,size_t>(std::get<0>(dot_1->get_pos()),std::get<1>(dot_1->get_pos()) + 1);
  std::get<1>(try_mv) = std::pair<size_t,size_t>(std::get<0>(dot_2->get_pos()),std::get<1>(dot_2->get_pos()) + 1);

  if(not m_game->was_point(try_mv))
    return false;

  std::get<0>(try_mv) =dot_1->get_pos();
  std::get<1>(try_mv) = std::pair<size_t,size_t>(std::get<0>(dot_1->get_pos()),std::get<1>(dot_1->get_pos()) + 1);

  if(not m_game->was_point(try_mv))
    return false;

  std::get<0>(try_mv) =dot_2->get_pos();
  std::get<1>(try_mv) = std::pair<size_t,size_t>(std::get<0>(dot_2->get_pos()),std::get<1>(dot_2->get_pos()) + 1);

  if(not m_game->was_point(try_mv))
   return false;

  return true;
}

unsigned short map_graphics::where_to_draw(MOVE last_move)
{
  if(not m_game->was_point(last_move))
    return 0;

  dot<4,4> *dot_1 = new dot<4,4> (std::pair<size_t,size_t>(std::get<0>(std::get<0>(last_move)),std::get<1>(std::get<0>(last_move))));
  dot<4,4> *dot_2 = new dot<4,4> (std::pair<size_t,size_t>(std::get<0>(std::get<1>(last_move)),std::get<1>(std::get<1>(last_move))));


  unsigned short case_ = m_game->try_to_point(dot_1,dot_2);

  if(case_ == 1 or case_ == 2)
  {
    if(dot_1->is_d_border() or dot_2->is_d_border())
        return 1; //draw upper box

    if(dot_1->is_u_border() or dot_2->is_u_border())
        return 2; //draw lower box

    if(upper_box(dot_1,dot_2) and lower_box(dot_1,dot_2))
      return 3; //draw upper_box and lower_box

    if(upper_box(dot_1,dot_2))
      return 1; //draw upper box

    if(lower_box(dot_1,dot_2))
      return 2; //draw lower box
  }

  if(case_ == 3 or case_ == 4)
  {
      if(dot_1->is_l_border() or dot_2->is_l_border())
          return 4; //draw right box

      if(dot_1->is_r_border() or dot_2->is_r_border())
          return 5; //draw left box

      if(right_box(dot_1,dot_2) and left_box(dot_1,dot_2))
        return 6; //draw right box and left box

      if(right_box(dot_1,dot_2))
        return 4; //draw right box

      if(left_box(dot_1,dot_2))
        return 5; //draw left box
  }

}

void map_graphics::draw_box(QBrush& paint)
{
    //Squares sorted by horizontal

        //First row:
    if( p_00_01 and p_01_11 and p_01_11 and p_00_10 and not(s1) )
    {
       scene->addRect(13,44,93,93,*c_free,paint);
       s1 = true;
       //return;
    }

    if( p_01_02 and p_02_12 and p_11_12 and p_02_12 and not(s2) )
    {
       scene->addRect(113,44,93,93,*c_free,paint);
       s2 = true;
    }

    if( p_02_03 and p_03_13 and p_12_13 and p_02_12 and not(s3) )
    {
       scene->addRect(213,44,93,93,*c_free,paint);
       s3 = true;
    }

        //Second row:
    if( p_10_11 and p_11_21 and p_20_21 and p_10_20 and not(s4) )
    {
       scene->addRect(13,144,93,93,*c_free,paint);
       s4 = true;
    }

    if( p_11_12 and p_12_22 and p_21_22 and p_11_21 and not(s5) )
    {
       scene->addRect(113,144,93,93,*c_free,paint);
       s5 = true;
    }

    if( p_12_13 and p_13_23 and p_22_23 and p_12_22 and not(s6))
    {
       scene->addRect(213,144,93,93,*c_free,paint);
       s6 = true;
    }

        //Third row:
    if( p_20_21 and p_21_31 and p_30_31 and p_20_30 and not(s7) )
    {
       scene->addRect(13,244,93,93,*c_free,paint);
       s7 = true;
    }

    if( p_21_22 and p_22_32 and p_31_32 and p_21_31 and not(s8) )
    {
       scene->addRect(113,244,93,93,*c_free,paint);
       s8 = true;
    }

    if( p_22_23 and p_23_33 and p_32_33 and p_22_32 and not(s9) )
    {
       scene->addRect(213,244,93,93,*c_free,paint);
       s9 = true;
    }

}


