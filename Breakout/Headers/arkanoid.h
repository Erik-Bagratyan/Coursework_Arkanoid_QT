#ifndef ARKANOID_H
#define ARKANOID_H

#include <QWidget>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QTimerEvent>

#include "Headers/ball.h"
#include "Headers/paddle.h"
#include "Headers/brick.h"

class Arkanoid : public QWidget
{
private:
    static const int m_N_OF_BRICKS = 36;
    static const int m_DELAY = 3;
    static const int m_BOTTOM_EDGE = 975;
    static const int m_WINDOW_HEIGHT = 985;
    static const int m_WINDOW_WIDTH = 1920;

private:
    int m_x;
    int m_timer_id;
    Ball* m_ball;
    Paddle* m_paddle;
    Brick* m_bricks[m_N_OF_BRICKS];
    bool m_game_over;
    bool m_game_won;
    bool m_game_started;
    bool m_paused;

public:
  Arkanoid(QWidget *parent = 0);
  ~Arkanoid();

protected:
  void paintEvent(QPaintEvent* e);
  void timerEvent(QTimerEvent*);
  void keyPressEvent(QKeyEvent*);
  void keyReleaseEvent(QKeyEvent*);
  void draw_objects(QPainter* paint);
  void finish_game(QPainter*, QString);
  void move_objects();

  void start_game();
  void pause_game();
  void stop_game();
  void victory();
  void check_collision();

private:
  void init_window();
}; // Arkanoid

#endif // ARKANOID_H
