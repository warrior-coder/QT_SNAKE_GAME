#include "game.h"

Game::Game()
{
    this->resize((WIDTH + 2) * CELL_WIDTH, (HEIGHT + 2) * CELL_HEIGHT);

    this->setWindowTitle("Snake Game");
    this->setStyleSheet("background-color: #16324C;");

    initGame();
}

void Game::timerEvent(QTimerEvent*)
{
    if (game)
    {
        moveBody();
        this->repaint();
    }
}

void Game::keyPressEvent(QKeyEvent* ke)
{
    switch (ke->key())
    {
        case Qt::Key_Left:  if (dir != right) dir = left; break;
        case Qt::Key_Right: if (dir != left) dir = right; break;
        case Qt::Key_Up:    if (dir != down) dir = up;    break;
        case Qt::Key_Down:  if (dir != up) dir = down;    break;
        case Qt::Key_Escape: this->close();
    }
}

void Game::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.fillRect(CELL_WIDTH, CELL_HEIGHT, WIDTH * CELL_WIDTH, HEIGHT * CELL_HEIGHT, Qt::black);

    if (game)
    {
        painter.fillRect((apple.x + 1) * CELL_WIDTH, (apple.y + 1) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, Qt::red);

        painter.fillRect((body[0].x + 1) * CELL_WIDTH + 1, (body[0].y + 1) * CELL_HEIGHT + 1, CELL_WIDTH - 2, CELL_HEIGHT - 2, Qt::darkGreen);
        for (int i = 1; i < body.size(); ++i)
        {
            painter.fillRect((body[i].x + 1) * CELL_WIDTH + 1, (body[i].y + 1) * CELL_HEIGHT + 1, CELL_WIDTH - 2, CELL_HEIGHT - 2, QColor(0x00, 0xFF, 0x00));
        }
    }

    painter.setPen(Qt::white);
    painter.setFont(QFont("Consolas", CELL_HEIGHT / 5 * 3));
    painter.drawText(CELL_WIDTH * (WIDTH - 1) / 2, CELL_HEIGHT / 5 * 4, "Score: " + QString::number(body.size() - 3));

}

void Game::initGame()
{
    game = true;

    body.resize(3, { WIDTH * 2, HEIGHT * 2 });
    for (int i = 0; i < body.size(); ++i)
    {
        body[i] = { WIDTH / 2 - i, HEIGHT / 2 };
    }

    srand(time(0));
    locateApple();

    dir = right;

    timerId = startTimer(TIMER_DELAY);
}

void Game::locateApple()
{
    for (bool isInside = true; isInside; isInside = false)
    {
        apple = { rand() % WIDTH, rand() % HEIGHT };

        for (const auto& el : body)
        {
            if (apple == el) isInside = true;
        }
    }
}

void Game::moveBody()
{
    for (int i = body.size() - 1; i > 0 ; --i)
    {
        body[i] = body[i - 1];
    }

    switch (dir)
    {
        case left:  body[0].x--; break;
        case right: body[0].x++; break;
        case up:    body[0].y--; break;
        case down:  body[0].y++; break;
    }

    for (int i = 3; i < body.size(); i++)
    {
        if (body[0] == body[i]) gameOver();
    }

    if (body[0].x >= WIDTH)  body[0].x = 0;
    if (body[0].x < 0)       body[0].x = WIDTH - 1;
    if (body[0].y >= HEIGHT) body[0].y = 0;
    if (body[0].y < 0)       body[0].y = HEIGHT - 1;

    if (body[0] == apple)
    {
        locateApple();
        body.push_back({ WIDTH * 2, HEIGHT * 2 });
    }
}

void Game::gameOver()
{
    killTimer(timerId);

    QMessageBox mb;
    mb.setText(QString("Game Over.  Your Score: %1").arg(body.size() - 3));
    mb.exec();

    initGame();
}
