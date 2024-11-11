#include "Fireball.h"
#include <QTimer>
#include "Cycle.h"
#include "GameScene.h"
#include "Score.h"
#include "AudioPlayer.h"
#include "EnemyTank.h"

Fireball::Fireball(int fireballSize, const EDirection& direction, GameScene* gameScene)
    : scene(gameScene), fireballDirection(direction), Projectile(fireballSize, ":/image/images/Fireball.png")
{
    isHit = false;
    moveTimer = new QTimer();
    QObject::connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(30);

    shotSoundPath = QString("qrc:/sounds/sound/Fireball.wav");
}

Fireball::~Fireball()
{
    if (fireballPng)
    {
        scene->removeItem(fireballPng);
        delete fireballPng;
        fireballPng = nullptr;
    }
}

void Fireball::spawnProjectile(int posX, int posY )
{
    fireballPng = new QGraphicsPixmapItem(projectile);
    scene->addItem(fireballPng);
    fireballPng->setPos(posX, posY);
    playShotSound();

}

void Fireball::playShotSound()
{
    AudioPlayer::activateSoundEffect(shotSoundPath);
}

void Fireball::move()
{

    calculatingDirection();

    for (auto i = 0 ; i < scene->activeCycles.size(); i++)
    {
        Cycle* py = scene->activeCycles[i];

        if (py)
        {
            if (checkCollisionWithEnemy(py))
            {
                handleCollidingWithEnemy(py, scene->activeCycles, scene->cycleCount, i, 5);
                return;
            }
        }

    }

    for (auto i = 0; i < scene->activeTanks.size(); i++)
    {
        EnemyTank* tank = scene->activeTanks[i];

        if (tank)
        {
            if (checkCollisionWithEnemy(tank))
            {
                handleCollidingWithEnemy(tank, scene->activeTanks, scene->tankCount, i, 10);
                return;
            }
        }
    }

    if (fireballPng->isActive())
    {
        //Check screen four side screen boundaries
        if (isOutOfScene(fireballPng))
        {
            //if passed, delete fireball
            delete this;
        }
    }
}

void Fireball::calculatingDirection()
{
    QPointF currPos = fireballPng->pos();
    int newX, newY;

    if (fireballDirection == EDirection::Left)
    {
        newX = currPos.x() - 15;
        newY = currPos.y();
    }
    if (fireballDirection == EDirection::Right)
    {
        newX = currPos.x() + 15;
        newY = currPos.y();
    }
    if (fireballDirection == EDirection::Up)
    {
        newX = currPos.x();
        newY = currPos.y() - 15;
    }
    if (fireballDirection == EDirection::Down)
    {
        newX = currPos.x();
        newY = currPos.y() + 15;
    }

    fireballPng->setPos(newX, newY);
}

template<typename T>
bool Fireball::checkCollisionWithEnemy(T* enemy)
{
    const int collisionRange = 25;
    //check collision with player snake
    QRectF fireballRect = this->fireballPng->boundingRect().translated(this->fireballPng->pos());
    fireballRect = fireballRect.adjusted(20, 10, -20, -10);

    //fireballRect = fireballRect.adjusted(collisionRange, collisionRange, -collisionRange, -collisionRange);

    QRectF enemyRect = enemy->getMesh()->boundingRect().translated(enemy->getMesh()->pos());
    enemyRect = enemyRect.adjusted(10, 10, -4, -10);

    if (fireballRect.intersects(enemyRect))
    {
        isHit = true;
        return isHit;
    }
    return false;
}

template<typename T>
void Fireball::handleCollidingWithEnemy(T *enemy, std::vector<T*> &activeEnemies, int &enemyCount, int index, int reward)
{


    if (enemy->getHealth() <= 1)
    {
        scene->getScore()->increaseScore(reward);
        //Setup sound when Cycle destroyed
        enemy->playDeathSound();
        //delete from cycle from the scene
        activeEnemies.erase(activeEnemies.begin() + index);
        delete enemy;
        //decrease number of maximum activeCycles
        --enemyCount;
        //delete fireball from the scene and heap
        delete this;
        //Uncheck flag
        isHit = false;
        return;
    }
    else
    {
        enemy->decreaseHealth();
        enemy->playHitSound();
        //delete fireball from the scene and heap
        delete this;
        //Uncheck flag
        isHit = false;
    }
 }

bool Fireball::isOutOfScene(QGraphicsPixmapItem *fireballMesh)
{
    return fireballMesh->pos().x() > 800 || fireballMesh->pos().x() < -10 || fireballMesh->pos().y() > 600 || fireballMesh->pos().y() < 50;
}


