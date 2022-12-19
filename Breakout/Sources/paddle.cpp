#include <QImage>
#include <QRect>

#include <mutex>
#include <memory>


#include "Headers/paddle.h"

Paddle* Paddle :: m_instance = nullptr;
std::shared_ptr<std::mutex> Paddle :: m_mutex = std::make_shared<std::mutex>();

Paddle::Paddle() {

  m_dx = 0;
  m_image.load("C:/Users/owner/OneDrive/Desktop/KuRsayin_Arcanoid/Breakout/Images/paddle.png");

  m_rect = m_image.rect();
  m_rect.setSize(QSize(100, 30));
  reset_state();
}


Paddle* Paddle::get_instance()
{
    std::lock_guard<std::mutex> lock(*m_mutex);
    if (m_instance == nullptr)
        m_instance = new Paddle();
    return m_instance;
}

void Paddle::set_dx(int x) {
  m_dx = x;
}

void Paddle::move() {

    int x = m_rect.x() + m_dx;
    int y = m_rect.top();
    if(x < 25)
        x = 25;
    else if (x > 1480)
        x = 1480;
    m_rect.moveTo(x, y);
}

void Paddle::reset_state() {

  m_rect.moveTo(m_INITIAL_X, m_INITIAL_Y);
}

QRect Paddle::get_rect() {

  return m_rect;
}

QImage & Paddle::get_image() {

  return m_image;
}
