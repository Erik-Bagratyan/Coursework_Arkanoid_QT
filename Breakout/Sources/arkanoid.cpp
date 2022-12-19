#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QApplication>

#include "Headers/arkanoid.h"

Arkanoid::Arkanoid(QWidget* parent)
    :   QWidget(parent)
    ,   m_x(0)
    ,   m_timer_id(0)
    ,   m_ball(Ball::get_instance())
    ,   m_paddle(Paddle::get_instance())
    ,   m_game_over(false)
    ,   m_game_won(false)
    ,   m_game_started(false)
    ,   m_paused(false)
{
    init_window();

    int k = 0;

    for (int i=0; i<6; i++) {
      for (int j=0; j<6; j++) {
        m_bricks[k] = new Brick(j*151+350, i*45+100);
        k++;
      }
    }
}

Arkanoid::~Arkanoid() {

 delete m_ball;
 delete m_paddle;

 for (int i=0; i< m_N_OF_BRICKS; i++) {
   delete m_bricks[i];
 }
}

void Arkanoid::init_window()
{
    // Screen Maximize
    this->showMaximized();
    //this->resize(this->m_WINDOW_WIDTH, this->m_WINDOW_HEIGHT);
    this->setWindowTitle("Arkanoid");
    this->setObjectName("Widget");
    this->setStyleSheet("#Widget { background-image: url(C:/Users/owner/OneDrive/Desktop/KuRsayin_Arcanoid/Breakout/Images/background.png); }");
    // Windows flags
    //setWindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

// Event Section
//  Begin

void Arkanoid::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    if (m_game_over)
    {
        painter.setPen(Qt::red);
        finish_game(&painter, "Game Over");
    }
    else if(m_game_won)
    {
        painter.setPen(Qt::green);
        finish_game(&painter, "Victory");
    }
    else
    {
        draw_objects(&painter);
    }

}

void Arkanoid::timerEvent(QTimerEvent *e) {

  Q_UNUSED(e);

  move_objects();
  check_collision();
  repaint();
}

void Arkanoid::move_objects() {

  m_ball->auto_move();
  m_paddle->move();
}

void Arkanoid::keyReleaseEvent(QKeyEvent *e) {

    int dx = 0;

    switch (e->key()) {
        case Qt::Key_Left:
            dx = 0;
            m_paddle->set_dx(dx);
            break;

        case Qt::Key_Right:
            dx = 0;
            m_paddle->set_dx(dx);
            break;
    }
}

void Arkanoid::keyPressEvent(QKeyEvent *e) {

    int dx = 0;

    switch (e->key()) {
    case Qt::Key_Left:

        dx = -1;
        m_paddle->set_dx(dx);

        break;

    case Qt::Key_Right:

        dx = 1;
        m_paddle->set_dx(dx);
        break;

    case Qt::Key_P:

        pause_game();
        break;

    case Qt::Key_Space:

        start_game();
        break;

    case Qt::Key_Escape:

        qApp->exit();
        break;

    default:
        QWidget::keyPressEvent(e);
    }
}

// Event Section
//  End

void Arkanoid::finish_game(QPainter *painter, QString message) {

  QFont font("Courier", 15, QFont::DemiBold);
  QFontMetrics fm(font);
  int textWidth = fm.width(message);

  painter->setFont(font);
  int h = height();
  int w = width();

  painter->translate(QPoint(w/2, h/2));
  painter->drawText(-textWidth/2, 0, message);
}

void Arkanoid::draw_objects(QPainter* painter)
{
    painter->drawImage(m_ball->get_rect(), m_ball->get_image());
    painter->drawImage(m_paddle->get_rect(), m_paddle->get_image());

    for (int i=0; i< m_N_OF_BRICKS; i++)
    {
      if (!m_bricks[i]->is_destroyed())
      {
        painter->drawImage(m_bricks[i]->get_rect(), m_bricks[i]->get_image());
      }
    }
}

void Arkanoid::start_game() {

  if (!m_game_started) {
    m_ball->reset_state();
    m_paddle->reset_state();

    for (int i=0; i< m_N_OF_BRICKS; i++) {
      m_bricks[i]->set_destroyed(false);
    }

    m_game_over = false;
    m_game_won = false;
    m_game_started = true;
    m_timer_id = startTimer(m_DELAY);
  }
}

void Arkanoid::pause_game() {

  if (m_paused) {

    m_timer_id = startTimer(m_DELAY);
    m_paused = false;
  } else {

    m_paused = true;
    killTimer(m_timer_id);
  }
}

void Arkanoid::stop_game() {

  killTimer(m_timer_id);
  m_game_over = true;
  m_game_started = false;
}

void Arkanoid::victory() {

  killTimer(m_timer_id);
  m_game_won = true;
  m_game_started = false;
}

void Arkanoid::check_collision() {

  if (m_ball->get_rect().bottom() > m_BOTTOM_EDGE) {
    stop_game();
  }

  for (int i=0, j=0; i< m_N_OF_BRICKS; i++) {

    if (m_bricks[i]->is_destroyed()) {
      j++;
    }

    if (j == m_N_OF_BRICKS) {
      victory();
    }
  }

  if ((m_ball->get_rect()).intersects(m_paddle->get_rect())) {

    int paddleLPos = m_paddle->get_rect().left();
    int ballLPos = m_ball->get_rect().left();

    int first = paddleLPos + 8;
    int second = paddleLPos + 16;
    int third = paddleLPos + 24;
    int fourth = paddleLPos + 32;

    if (ballLPos < first) {
      m_ball->set_x_dir(-1);
      m_ball->set_y_dir(-1);
    }

    if (ballLPos >= first && ballLPos < second) {
      m_ball->set_x_dir(-1);
      m_ball->set_y_dir(-1*m_ball->get_y_dir());
    }

    if (ballLPos >= second && ballLPos < third) {
       m_ball->set_x_dir(0);
       m_ball->set_y_dir(-1);
    }

    if (ballLPos >= third && ballLPos < fourth) {
       m_ball->set_x_dir(1);
       m_ball->set_y_dir(-1*m_ball->get_y_dir());
    }

    if (ballLPos > fourth) {
      m_ball->set_x_dir(1);
      m_ball->set_y_dir(-1);
    }
  }

  for (int i=0; i< m_N_OF_BRICKS; i++) {

    if ((m_ball->get_rect()).intersects(m_bricks[i]->get_rect())) {

      int ballLeft = m_ball->get_rect().left();
      int ballHeight = m_ball->get_rect().height();
      int ballWidth = m_ball->get_rect().width();
      int ballTop = m_ball->get_rect().top();

      QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
      QPoint pointLeft(ballLeft - 1, ballTop);
      QPoint pointTop(ballLeft, ballTop -1);
      QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

      if (!m_bricks[i]->is_destroyed()) {
        if(m_bricks[i]->get_rect().contains(pointRight)) {
           m_ball->set_x_dir(-1);
        }

        else if(m_bricks[i]->get_rect().contains(pointLeft)) {
           m_ball->set_x_dir(1);
        }

        if(m_bricks[i]->get_rect().contains(pointTop)) {
           m_ball->set_y_dir(1);
        }

        else if(m_bricks[i]->get_rect().contains(pointBottom)) {
           m_ball->set_y_dir(-1);
        }

        m_bricks[i]->set_destroyed(true);
      }
    }
  }
}
