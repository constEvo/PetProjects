#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>


class Enemy : public QObject
{
    Q_OBJECT
public:
    Enemy();


    virtual void move() = 0;
private:
    int health;
    int moveSpeed;
};

#endif // ENEMY_H
