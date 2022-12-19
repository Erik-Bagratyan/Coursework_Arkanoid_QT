#ifndef PADDLE_H
#define PADDLE_H

#include <QImage>
#include <QRect>

#include <mutex>
#include <memory>

class Paddle
{
private:
    static Paddle* m_instance;
    // For multi threading
    static std::shared_ptr<std::mutex> m_mutex;

private:
  QImage m_image;
  QRect m_rect;
  int m_dx;
  static const int m_INITIAL_X = 800;
  static const int m_INITIAL_Y = 950;

public:
    Paddle(const Paddle&)		= delete;
    Paddle& operator=(Paddle&)	= delete;

private:
    Paddle();

public:
    static Paddle* get_instance();

    void reset_state();
    void move();
    void set_dx(int);
    QRect get_rect();
    QImage & get_image();
}; // Paddle

#endif // PADDLE_H
