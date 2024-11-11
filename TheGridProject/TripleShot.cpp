#include "TripleShot.h"
#include "GameScene.h"
#include <QTimer>
#include "Cycle.h"
#include "AudioPlayer.h"
#include "EnemyTank.h"
#include "Score.h"

TripleShot::TripleShot(int fireballSize, const EDirection &direction, GameScene *gameScene) :
    scene(gameScene),
    tripleShotlDirection(direction),
    Projectile(fireballSize, ":/image/images/tripleShot.png")
{
    isHit = false;
    moveTimer = new QTimer();
    QObject::connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(30);

    shotSoundPath = QString("qrc:/sounds/sound/TripleShot.wav");
}

TripleShot::~TripleShot()
{

    if (leftShotPng)
    {
        delete leftShotPng;
        leftShotPng = nullptr;
    }

    if (midShotPng)
    {
        delete midShotPng;
        midShotPng = nullptr;
    }

    if (rightShotPng)
    {
        delete rightShotPng;
        rightShotPng = nullptr;
    }

    if (moveTimer)
    {
        moveTimer->stop();
        delete moveTimer;
        moveTimer = nullptr;
    }
}

void TripleShot::spawnProjectile(int posX, int posY)
{
    leftShotPng = new QGraphicsPixmapItem(projectile);
    scene->addItem(leftShotPng);
    leftShotPng->setPos(posX, posY);

    midShotPng = new QGraphicsPixmapItem(projectile);
    scene->addItem(midShotPng);
    midShotPng->setPos(posX, posY);

    rightShotPng = new QGraphicsPixmapItem(projectile);
    scene->addItem(rightShotPng);
    rightShotPng->setPos(posX, posY);

    playShotSound();
}

void TripleShot::playShotSound()
{
    AudioPlayer::activateSoundEffect(shotSoundPath);
}

void TripleShot::handleLeftShotMoveDirection()
{
    if (!leftShotPng || !leftShotPng->isActive()) return;

    QPointF currPosLeft = leftShotPng->pos();

    int newXLeft, newYLeft;

    if (tripleShotlDirection == EDirection::Left)
    {
        newXLeft = currPosLeft.x() - 15;
        newYLeft = currPosLeft.y() - 5;
    }
    if (tripleShotlDirection == EDirection::Right)
    {
        newXLeft = currPosLeft.x() + 15;
        newYLeft = currPosLeft.y() - 5;
    }
    if (tripleShotlDirection == EDirection::Up)
    {
        newXLeft = currPosLeft.x() - 5;
        newYLeft = currPosLeft.y() - 15;
    }
    if (tripleShotlDirection == EDirection::Down)
    {
        newXLeft = currPosLeft.x() + 5;
        newYLeft = currPosLeft.y() + 15;
    }

    leftShotPng->setPos(newXLeft, newYLeft);

}

void TripleShot::handleMidShotMoveDirection()
{
    if (!midShotPng || !midShotPng->isActive()) return;

    QPointF currPosMid = midShotPng->pos();

    int newXMid, newYMid;

    if (tripleShotlDirection == EDirection::Left)
    {
        newXMid = currPosMid.x() - 15;
        newYMid = currPosMid.y();
    }
    if (tripleShotlDirection == EDirection::Right)
    {
        newXMid = currPosMid.x() + 15;
        newYMid = currPosMid.y();
    }
    if (tripleShotlDirection == EDirection::Up)
    {
        newXMid = currPosMid.x();
        newYMid = currPosMid.y() - 15;
    }
    if (tripleShotlDirection == EDirection::Down)
    {
        newXMid = currPosMid.x();
        newYMid = currPosMid.y() + 15;
    }
    midShotPng->setPos(newXMid, newYMid);

}

void TripleShot::handleRightShotMoveDirection()
{
    if (!rightShotPng || !rightShotPng->isActive()) return;

    QPointF currPosRight = rightShotPng->pos();

    int newXRight, newYRight;

    if (tripleShotlDirection == EDirection::Left)
    {
        newXRight = currPosRight.x() - 15;
        newYRight = currPosRight.y() + 5;
    }
    if (tripleShotlDirection == EDirection::Right)
    {
        newXRight = currPosRight.x() + 15;
        newYRight = currPosRight.y() + 5;
    }
    if (tripleShotlDirection == EDirection::Up)
    {
        newXRight = currPosRight.x() + 5;
        newYRight = currPosRight.y() - 15;
    }
    if (tripleShotlDirection == EDirection::Down)
    {
        newXRight = currPosRight.x() - 5;
        newYRight = currPosRight.y() + 15;
    }

    rightShotPng->setPos(newXRight, newYRight);
}

template<typename T>
bool TripleShot::checkCollisionWithEnemy(T *enemy, std::vector<QGraphicsPixmapItem*>& tripleShot)
{

    //if (leftShotPng)
        tripleShot.push_back(leftShotPng);

    //if (midShotPng)
        tripleShot.push_back(midShotPng);

    //if (rightShotPng)
        tripleShot.push_back(rightShotPng);

    QRectF enemyRect = enemy->getMesh()->boundingRect().translated(enemy->getMesh()->pos());
    enemyRect = enemyRect.adjusted(10, 10, -4, -10);

    for (auto i = 0; i < tripleShot.size(); ++i)
    {
        QGraphicsPixmapItem* shot = tripleShot[i];
        QRectF shotRect = shot->boundingRect().translated(shot->pos());
        shotRect = shotRect.adjusted(0, 0, 0, -10);

        if (shotRect.intersects(enemyRect))
        {
            isHit = true;
        }
    }
    tripleShot.clear();
    return isHit;

}

template<typename T>
void TripleShot::handleCollidingWithEnemy(T *enemy, std::vector<T*> &activeEnemy, int &enemyCount, int index, int reward)
{
    scene->getScore()->increaseScore(reward);
    //Setup sound when Cycle destroyed
    enemy->playDeathSound();
    //decrease current activeCycles
    activeEnemy.erase(activeEnemy.begin() + index);
    //decrease number of maximum activeCycles
    --enemyCount;
    //delete cycle from the scene
    delete enemy;
    //Uncheck flag
    isHit = false;
    return;
}


void TripleShot::move()
{
    //Set directional move for left shot move
    handleLeftShotMoveDirection();
    //Set directional move for mid shot move
    handleMidShotMoveDirection();
    //Set directional move for right shot move
    handleRightShotMoveDirection();

    std::vector<QGraphicsPixmapItem*> tripleShot;

    for (auto i = 0; i < scene->activeCycles.size(); ++i)
    {
        Cycle* cycle = scene->activeCycles[i];

        if (cycle)
        {
            if (checkCollisionWithEnemy(cycle, tripleShot))
            {
                handleCollidingWithEnemy(cycle, scene->activeCycles,  scene->cycleCount, i, 5);
                return;
            }
        }

    }

    for (auto i = 0; i < scene->activeTanks.size(); ++i)
    {
        EnemyTank* tank = scene->activeTanks[i];

        if (tank)
        {
            if (checkCollisionWithEnemy(tank, tripleShot))
            {
                handleCollidingWithEnemy(tank, scene->activeTanks, scene->tankCount, i, 10);
                return;
            }
        }
    }

    //Check screen four side screen boundaries for left projectile
    passBoundaries(leftShotPng);

    //Check screen four side screen boundaries for mid projectile
    passBoundaries(midShotPng);

    //Check screen four side screen boundaries for right projectile
    passBoundaries(rightShotPng);

    //When all shots deleteted from the scene, delete tripleShots from the heap
    if (!leftShotPng->isActive() && !midShotPng->isActive() && !rightShotPng->isActive())
    {
        delete this;
    }
}


void TripleShot::passBoundaries(QGraphicsPixmapItem *shotMesh)
{
    if (shotMesh->isActive() && isOutOfScene(shotMesh))
    {
        //if passed, delete shot
        scene->removeItem(shotMesh);
        return;
    }
}

bool TripleShot::isOutOfScene(QGraphicsPixmapItem *shotMesh)
{
    return shotMesh->pos().x() > 800 || shotMesh->pos().x() < -10 || shotMesh->pos().y() > 600 || shotMesh->pos().y() < 50;
}
