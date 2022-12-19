#ifndef BRICK_H
#define BRICK_H

#include <QImage>
#include <QRect>

class Brick {

  public:
    Brick(int, int);

  public:
    bool is_destroyed();
    void set_destroyed(bool);
    QRect get_rect();
    void set_rect(QRect);
    QImage & get_image();

  private:
    QImage m_image;
    QRect m_rect;
    bool m_destroyed;
};

#endif // BRICK_H
