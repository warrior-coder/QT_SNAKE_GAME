#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>
#include <QPainter>
#include <QMessageBox>
#include <QString>

class Game : public QWidget
{
public:
    Game();

protected:
    void timerEvent(QTimerEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void paintEvent(QPaintEvent*) override;

private:
    static const int WIDTH = 20, HEIGHT = 20;
    static const int CELL_WIDTH = 25, CELL_HEIGHT = 25;
    static const int TIMER_DELAY = 128;

    struct Point
    {
        int x, y;
        inline bool operator==(const Point& p) { return (x == p.x && y == p.y); }
    };

    enum Direction { left, right, up, down };


    bool game;
    QVector<Point> body;
    Point apple;
    Direction dir;
    int timerId;


    void initGame();
    void locateApple();
    void moveBody();
    void gameOver();
};

#endif // GAME_H
