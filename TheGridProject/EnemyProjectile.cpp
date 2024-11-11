#include "EnemyProjectile.h"
#include <QTimer>
#include "GameScene.h"
#include "GameCharacter.h"
#include "Health.h"

EnemyProjectile::EnemyProjectile(int size, const EDirection &direction, GameScene *gameScene, GameCharacter* playerCharacter) :
    Projectile(size, ":/image/images/EnemyTank/TankProjectile.png"),
    enemyProjectileDirection(direction),
    scene(gameScene),
    player(playerCharacter)
{
    isHit = false;
    moveTimer = new QTimer();
    QObject::connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(50);

}

EnemyProjectile::~EnemyProjectile()
{
    if (moveTimer)
    {
        moveTimer->stop();
        delete moveTimer;
        moveTimer = nullptr;
    }
    if (enemyProjectileMesh)
    {
        scene->removeItem(enemyProjectileMesh);
        delete enemyProjectileMesh;
        enemyProjectileMesh = nullptr;
    }

}

void EnemyProjectile::spawnProjectile(int posX, int posY)
{
    enemyProjectileMesh = new QGraphicsPixmapItem(projectile);
    scene->addItem(enemyProjectileMesh);
    enemyProjectileMesh->setPos(posX, posY);
}

void EnemyProjectile::playShotSound()
{

}

QGraphicsPixmapItem *EnemyProjectile::getMesh()
{
    return enemyProjectileMesh;
}

void EnemyProjectile::move()
{
    handleEnemyShotMoveDirection();

    //when shield is disable
    if (checkPlayerCollision() && !player->getShieldStatus())
    {
        handleCollidingWithPlayer();
    }
    // when shield is active
    else if (checkPlayerCollision() && player->getShieldStatus())
    {
        //delete enemy projectile
        delete this;
    }

    //Check screen four side screen boundaries
    if (getMesh())
    {
        if (isOutOfBoundaries())
        {
            //if passed, delete enemyProjectile
            delete this;
        }
    }

}

void EnemyProjectile::handleEnemyShotMoveDirection()
{
    QPointF projectileCenter = getMesh()->boundingRect().center();
    getMesh()->setTransformOriginPoint(projectileCenter);

    QPointF currPos = getMesh()->pos();
    int newX, newY;

    if (enemyProjectileDirection == EDirection::Left)
    {
        newX = currPos.x() - 15;
        newY = currPos.y();
        getMesh()->setRotation(-90);
    }
    if (enemyProjectileDirection == EDirection::Right)
    {
        newX = currPos.x() + 15;
        newY = currPos.y();
        getMesh()->setRotation(90);
    }
    if (enemyProjectileDirection == EDirection::Up)
    {
        newX = currPos.x();
        newY = currPos.y() - 15;
        getMesh()->setRotation(0);
    }
    if (enemyProjectileDirection == EDirection::Down)
    {
        newX = currPos.x();
        newY = currPos.y() + 15;
        getMesh()->setRotation(180);
    }

    getMesh()->setPos(newX, newY);
}

bool EnemyProjectile::checkPlayerCollision()
{
    const int collisionRange = 25;
    //check collision with player snake
    QRectF projectileRect = getMesh()->boundingRect().translated(getMesh()->pos());
    projectileRect = projectileRect.adjusted(20, 10, -20, -10);

    //fireballRect = fireballRect.adjusted(collisionRange, collisionRange, -collisionRange, -collisionRange);

    QRectF playerRect = player->getMesh()->boundingRect().translated(player->getMesh()->pos());

    if (projectileRect.intersects(playerRect))
    {
        if (player->getHealthCooldownTimer()->elapsed() >= player->healthCooldownDuration)
        {
            isHit = true;
            return isHit;
        }
    }
    return false;
}

void EnemyProjectile::handleCollidingWithPlayer()
{
    player->playHitSound();
    player->getHealth()->decreaseHealth();

    if (player->getHealth()->getHealth() <= 0)
    {
        scene->setGameState(EGameState::GameOver);
    }

    isHit = false;

    player->getHealthCooldownTimer()->restart();

    //delete enemy projectile
    delete this;
}

bool EnemyProjectile::isOutOfBoundaries()
{
    return getMesh()->pos().x() > 800 || getMesh()->pos().x() < -10
            || getMesh()->pos().y() > 600 || getMesh()->pos().y() < 50;
}





