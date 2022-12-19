#include <QImage>
#include <QRect>

#include "Headers/brick.h"

Brick::Brick(int x, int y) {

  m_image.load("C:/Users/owner/OneDrive/Desktop/KuRsayin_Arcanoid/Breakout/Images/bricke.png");
  m_destroyed = false;
  m_rect = m_image.rect();
  //m_rect.setSize(QSize(140, 40));
  m_rect.translate(x, y);
}

QRect Brick::get_rect() {

  return m_rect;
}

void Brick::set_rect(QRect rct) {

  m_rect = rct;
}

QImage & Brick::get_image() {

  return m_image;
}

bool Brick::is_destroyed() {

  return m_destroyed;
}

void Brick::set_destroyed(bool destr) {

  m_destroyed = destr;
}
