#include "GameCharacter.h"
#include "EStates.h"
#include <QElapsedTimer>
#include "Health.h"
#include "Fireball.h"
#include "TripleShot.h"
#include "GameScene.h"
#include "Cycle.h"
#include "Score.h"
#include "EnemyTank.h"
#include "AudioPlayer.h"



GameCharacter::GameCharacter(GameScene* gameScene, int size)
    : scene(gameScene), Character(size, ":/image/images/main.png")
{
    leftDirection = false;
    rightDirection = false;
    upDirection = false;
    downDirection = false;


    initCharacter(150, 150);

    health = 3;
    healthCooldownTimer = new QElapsedTimer();
    healthCooldownTimer->start();

    shieldDurationTimer = new QElapsedTimer();

    burstWeaponDurationTimer = new QElapsedTimer();

    isShieldActive = false;
    isHit = false;

    weaponState = EWeaponState::SingleShotWeapon;
    currentDirection = EDirection::Idle;

    //Health String
    healthString = new Health(this);
    scene->addItem(healthString);

    hitSoundPath = QString("qrc:/sounds/sound/HitSound.mp3");
}

GameCharacter::~GameCharacter()
{

}

void GameCharacter::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    if ((key == Qt::Key_Left) && (!rightDirection))
    {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
        rightDirection = false;
        currentDirection = EDirection::Left;
    }
    if ((key == Qt::Key_Right) && (!leftDirection))
    {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
        leftDirection = false;
        currentDirection = EDirection::Right;
    }
    if ((key == Qt::Key_Up) && (!downDirection) )
    {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
        downDirection = false;
        currentDirection = EDirection::Up;
    }
    if ((key == Qt::Key_Down) && (!upDirection))
    {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
        upDirection = false;
        currentDirection = EDirection::Down;
    }
    if (key == Qt::Key_Space)
    {
        shoot();
    }
}

void GameCharacter::initCharacter(int startX, int startY)
{
    characterMesh = new QGraphicsPixmapItem(meshPng);
    characterMesh->setPos(startX, startY);
    vPlayer.push_back(characterMesh);
    scene->addItem(characterMesh);
}


void GameCharacter::deleteCharacter()
{
    if (getMesh())
    {
        scene->removeItem(getMesh());
        delete characterMesh;
    }
}

void GameCharacter::collidingWithEnemy()
{
    std::vector<Cycle*> activeCycles = scene->getActiveCycles();

    QRectF playerRect = getAdjustedPlayerRect();

   for (int i = 0; i < activeCycles.size(); ++i)
    {
        Cycle* cycle = activeCycles[i];
        if (cycle)
        {
            if (checkCollisionWithEnemy(cycle, playerRect))
            {
                handleCycleCollision(cycle, i);
                return;
            }
        }
    }

   std::vector<EnemyTank*> activeTanks = scene->activeTanks;

   for (int i = 0; i < activeTanks.size(); ++i)
    {
        EnemyTank* tank = activeTanks[i];
        if (tank)
        {
            if (checkCollisionWithEnemy(tank, playerRect) && !getShieldStatus())
            {
                handleTankColliding();
            }
        }
    }
}

QRectF GameCharacter::getAdjustedPlayerRect()
{
    //adjusting collision for player mesh
    QRectF playerRect = this->getMesh()->boundingRect().translated(this->getMesh()->pos());
    playerRect = playerRect.adjusted(10, 10, -4, -10);

    return playerRect;
}


QGraphicsPixmapItem *GameCharacter::getMesh()
{
    return this->characterMesh;
}

EWeaponState GameCharacter::getWeaponState()
{
    return weaponState;
}

void GameCharacter::setWeaponState(EWeaponState weaponState)
{
    this->weaponState = weaponState;
}

EDirection GameCharacter::getDirectionState()
{
    return currentDirection;
}

void GameCharacter::stopLocomotion()
{
    leftDirection = false;
    rightDirection = false;
    upDirection = false;
    downDirection = false;
}

void GameCharacter::shoot()
{
    if (getWeaponState() == EWeaponState::SingleShotWeapon)
    {
        Fireball* fireball = new Fireball(60, getDirectionState(), scene);
        int posX = this->getMesh()->pos().x() - 10;
        int posY = this->getMesh()->pos().y() + 15;
        fireball->spawnProjectile(posX, posY);
    }
    else if (getWeaponState() == EWeaponState::TripleShotWeapon)
    {
        TripleShot* tripleShot = new TripleShot(30, getDirectionState(), scene);
        int posX = this->getMesh()->pos().x() + 10;
        int posY = this->getMesh()->pos().y() + 10;
        tripleShot->spawnProjectile(posX, posY);
    }
}

bool GameCharacter::getShieldStatus()
{
    return isShieldActive;
}

void GameCharacter::setShieldStatus(bool status)
{
    isShieldActive = status;
}

void GameCharacter::shieldHasEnabled(Cycle* cycle, int index)
{
    scene->getScore()->increaseScore(5);

    //Setup sound when Cycle destroyed
    cycle->playDeathSound();

    //delete cycle from the scene
    scene->activeCycles.erase(scene->activeCycles.begin() + index);
    delete cycle;

    //decrease current activeCycles
    --scene->cycleCount;

}

void GameCharacter::shieldHasDisabled()
{
    healthString->decreaseHealth();

    //play hit sound
    playHitSound();

    if (healthString->getHealth() <= 0)
    {
        scene->setGameState(EGameState::GameOver);
    }

    healthCooldownTimer->restart();
}

void GameCharacter::playHitSound()
{
    AudioPlayer::activateSoundEffect(hitSoundPath);
}

void GameCharacter::setDefaultHealthValue()
{
    healthString->setDefaultHealthValue();
}

QElapsedTimer *GameCharacter::getShieldDurationTimer()
{
    return shieldDurationTimer;
}

void GameCharacter::startShieldDurationTimer()
{
    shieldDurationTimer->start();
}

QElapsedTimer *GameCharacter::getBurstWeaponDurationTimer()
{
    return burstWeaponDurationTimer;
}

void GameCharacter::startBurstWeaponDurationTimer()
{
    burstWeaponDurationTimer->start();
}

QElapsedTimer *GameCharacter::getHealthCooldownTimer()
{
    return healthCooldownTimer;
}

Health *GameCharacter::getHealth()
{
    return healthString;
}

void GameCharacter::checkCollision()
{
    QRectF playerRect = getMesh()->boundingRect().translated(getMesh()->pos());
    playerRect = getAdjustedPlayerRect();
    QRectF gameCanvasRect = scene->getGameCanvas()->boundingRect();
    QPainterPath canvasPath;
    canvasPath.addRect(gameCanvasRect);

    if (!gameCanvasRect.contains(playerRect))
    {
        scene->setGameState(EGameState::GameOver);
    }
}


void GameCharacter::move()
{

    QPointF center = getMesh()->boundingRect().center();
    getMesh()->setTransformOriginPoint(center);

    if (leftDirection)
    {
        getMesh()->setRotation(-90);
        getMesh()->moveBy(-15, 0);

    }
    if (rightDirection)
    {
        getMesh()->setRotation(90);
        getMesh()->moveBy(15, 0);
    }
    if (upDirection)
    {
        getMesh()->setRotation(0);
        getMesh()->moveBy(0, -15);
    }
    if (downDirection)
    {
        getMesh()->setRotation(180);
        getMesh()->moveBy(0, 15);
    }

    if (isShieldActive)
    {
        if (shieldDurationTimer->elapsed() > SHIELD_DURATION)
            isShieldActive = false;
    }

    if (getWeaponState() == EWeaponState::TripleShotWeapon)
    {
        if (burstWeaponDurationTimer->elapsed() > BURST_WEAPON_DURATION)
            setWeaponState(EWeaponState::SingleShotWeapon);
    }

    collidingWithEnemy();
}

template<typename T >
bool GameCharacter::checkCollisionWithEnemy(T *enemy, const QRectF &playerRect)
{
    QRectF enemyRect = enemy->getMesh()->boundingRect().translated(enemy->getMesh()->pos());

    enemyRect = enemyRect.adjusted(10, 10, -4, -10);

    if (playerRect.intersects(enemyRect))
    {
        if (isShieldActive || healthCooldownTimer->elapsed() >= healthCooldownDuration)
        {
            isHit = true;
        }
        return isHit;
    }
    return false;
}


void GameCharacter::handleCycleCollision(Cycle *cycle, int index)
{
    if (isHit && isShieldActive)
    {
        shieldHasEnabled(cycle, index);
    }
    else if (isHit && !isShieldActive)
    {
        shieldHasDisabled();
    }
    isHit = false;
}

void GameCharacter::handleTankColliding()
{
    healthString->decreaseHealth();

    //play hit sound
    playHitSound();

    if (healthString->getHealth() <= 0)
    {
        scene->setGameState(EGameState::GameOver);
    }

    isHit = false;

    healthCooldownTimer->restart();
}
