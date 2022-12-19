#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QImage>
#include <QRect>
#include <QPaintEvent>

#include <mutex>
#include <memory>

class Ball
{
private:
    static Ball* m_instance;
    // For multi threading
    static std::shared_ptr<std::mutex> m_mutex;

private:
    int m_x_dir;
    int m_y_dir;
    QImage m_image;
    QRect m_rect;
    static const int m_INITIAL_X = 835;
    static const int m_INITIAL_Y = 910;
    static const int m_RIGHT_EDGE = 1590;

public:
    Ball(const Ball&)		= delete;
    Ball& operator=(Ball&)	= delete;

    // Used Singlton dessign pattern for Ball
    static Ball* get_instance();

public:
    void reset_state();
    void auto_move();
    void set_x_dir(int);
    void set_y_dir(int);
    int get_x_dir();
    int get_y_dir();
    QRect get_rect();
    QImage& get_image();


private:
    Ball();
}; // Ball

#endif // BALL_H
