#include "Snake.h"
#include <QPixmap>
#include <GameScene.h>



/*

Snake::Snake(int length,
             int dotSize,
             const QString &headImagePath,
             const QString &bodyImagePath)
            : snakeLength(length),
            dotSize(dotSize)
{
    headPng = QPixmap(headImagePath);
    headPng = headPng.scaled(dotSize, dotSize, Qt::AspectRatioMode::KeepAspectRatio, Qt::SmoothTransformation);
    bodyPng = QPixmap(bodyImagePath);
    bodyPng = bodyPng.scaled(dotSize, dotSize, Qt::AspectRatioMode::KeepAspectRatio, Qt::SmoothTransformation);
}


void Snake::initHead(QGraphicsScene *scene, int startX, int startY)
{
    head = new QGraphicsPixmapItem(headPng);
    head->setPos(startX, startY);
    vSnake.push_back(head);
    scene->addItem(head);
    initBody(scene);
}

void Snake::initBody(QGraphicsScene *scene)
{
    for (int z = 1; z <= snakeLength; ++z)
    {
        body = new QGraphicsPixmapItem(bodyPng);
        int headX = head->x();
        int headY = head->y();
        vSnake.push_back(body);
        scene->addItem(body);
        body->setPos(headX, headY + z * dotSize);
    }
}

void Snake::addBody(QGraphicsScene *scene)
{
    body = new QGraphicsPixmapItem(bodyPng);
    vSnake.push_back(body);
    ++snakeLength;
    scene->addItem(body);
}

void Snake::deleteBody()
{

}
*/



