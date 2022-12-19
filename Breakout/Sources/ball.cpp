#include <QWidget>
#include <QRect>
#include <QImage>
#include <QPaintEvent>
#include <QPainter>

#include <mutex>
#include <memory>

#include "Headers/ball.h"

Ball* Ball :: m_instance = nullptr;
std::shared_ptr<std::mutex> Ball :: m_mutex = std::make_shared<std::mutex>();

Ball::Ball()
    :   m_x_dir(1)
    ,   m_y_dir(-1)
{
    m_image.load("C:/Users/owner/OneDrive/Desktop/KuRsayin_Arcanoid/Breakout/Images/ball.png");
    m_rect = m_image.rect();
    //m_rect.setRect(m_x_dir, m_y_dir, 35, 35);
    reset_state();
}

void Ball::auto_move() {

  m_rect.translate(m_x_dir, m_y_dir);
  if (m_rect.left() == 20) {
    m_x_dir = 1;
  }

  if (m_rect.right() == m_RIGHT_EDGE) {
    m_x_dir = -1;
  }

  if (m_rect.top() == 20) {
    m_y_dir = 1;
  }
}

void Ball::set_x_dir(int x) {

  m_x_dir = x;
}

void Ball::set_y_dir(int y) {

  m_y_dir = y;
}

int Ball::get_x_dir() {

  return m_x_dir;
}

int Ball::get_y_dir() {

  return m_y_dir;
}

void Ball::reset_state() {

  m_rect.moveTo(m_INITIAL_X, m_INITIAL_Y);
}

Ball* Ball::get_instance()
{
    std::lock_guard<std::mutex> lock(*m_mutex);
        if (m_instance == nullptr)
            m_instance = new Ball();
        return m_instance;
}

QRect Ball::get_rect()
{
  return m_rect;
}

QImage& Ball::get_image()
{
  return m_image;
}
