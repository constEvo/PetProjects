#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QVector>
#include "GameScene.h"

class Snake : public QObject
{
    Q_OBJECT
public:
    Snake(int length, int dotSize, const QString &headImagePath, const QString &bodyImagePath) :
            snakeLength(length),
            dotSize(dotSize)
    {
        headPng = QPixmap(headImagePath);
        headPng = headPng.scaled(dotSize , dotSize , Qt::AspectRatioMode::KeepAspectRatio, Qt::SmoothTransformation);
        bodyPng = QPixmap(bodyImagePath);
        bodyPng = bodyPng.scaled(dotSize , dotSize  , Qt::AspectRatioMode::KeepAspectRatio, Qt::SmoothTransformation);
    }
    QGraphicsPixmapItem* head;
protected:
    virtual void initHead(GameScene* scene, int startX, int startY) = 0;
    virtual void initBody(GameScene* scene) = 0;
    virtual void addBody(GameScene* scene) = 0;
    virtual void deleteBody(GameScene* scene) = 0;



    int snakeLength;
    int dotSize;


    QGraphicsPixmapItem* body;

    QPixmap headPng;
    QPixmap bodyPng;



};

#endif // SNAKE_H

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
*/
