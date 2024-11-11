#include "EnemyTank.h"
#include <QTimer>
#include "GameCharacter.h"
#include <QRandomGenerator>
#include "EnemyProjectile.h"
#include "GameScene.h"
#include "AudioPlayer.h"


EnemyTank::EnemyTank(int size, GameCharacter* playerCharacter, GameScene* gameScene) :
    Character(size, ":/image/images/EnemyTank/Hull_01.png"),
    scene(gameScene),
    player(playerCharacter)
{
    initCharacter(0, 0);

    direction = EDirection::Idle;

    engage = false;
    targetReached = false;

    deathPathSound = QString("qrc:/sounds/sound/TankDeathSound.wav");
    hitPathSound = QString("qrc:/sounds/sound/TankHitSound.mp3");

    //Connect slots
    QObject::connect(scene->moveTank_timer, SIGNAL(timeout()), this, SLOT(move()));


    QObject::connect(scene->shootTank_timer, SIGNAL(timeout()), this, SLOT(shoot()));
}

EnemyTank::~EnemyTank()
{
    if (shootTimer)
    {
        shootTimer->stop();
        delete shootTimer;
        shootTimer = nullptr;
    }
    if (getMesh() && scene && gunMesh)
    {
        scene->removeItem(getMesh());
        scene->removeItem(gunMesh);
        delete characterMesh;
        characterMesh = nullptr;
        delete gunMesh;
        gunMesh = nullptr;
    }
}


void EnemyTank::initCharacter(int startX, int startY)
{
    rand = QRandomGenerator::global();

    //Create tank's hull
    characterMesh = new QGraphicsPixmapItem(meshPng);
    do
    {
        startX = getBoundX();
        startY = getBoundY();
    } while (isTooCloseToPlayer(startX, startY));

    characterMesh->setPos(startX, startY );
    scene->addItem(characterMesh);

    //Create tank's gun
    gunMeshPath = QString(":/image/images/EnemyTank/Gun_03.png");
    gunPng = QPixmap(gunMeshPath).scaled(size + 5, size + 5, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
    gunMesh = new QGraphicsPixmapItem(gunPng);
    gunMesh->setPos(startX , startY);
    gunMesh->setZValue(1);
    scene->addItem(gunMesh);
    setStartHealthValue();
}


void EnemyTank::shoot()
{
    if (engage)
    {
        EnemyProjectile* projectile = new EnemyProjectile(50, direction, scene, player);
        int posX = getMesh()->pos().x() + 15;
        int posY = getMesh()->pos().y() + 15;
        projectile->spawnProjectile(posX, posY);
    }
}

void EnemyTank::move()
{
    QPointF playerPos = player->getMesh()->pos();

    QPointF tankPos = getMesh()->pos();

    calculateDestination(targetReached, randomDestination);

    QPointF target = chooseRoute(tankPos, playerPos);

    moveTowards(target);

    handlingTankShooting(tankPos, playerPos);
}


int EnemyTank::getBoundX()
{
    if (scene)
    {
        int first = 1;
        int second = scene->gameCanvasWidth / size;
        int randPosX = rand->bounded(first, second);
        return randPosX * size;
    }
}

int EnemyTank::getBoundY()
{
    if (scene)
    {
        int first = 3;
        int second = scene->gameCanvasHeight / size;
        int randPosY = rand->bounded(first, second);
        return randPosY * size;
    }
}

bool EnemyTank::isTooCloseToPlayer(int cyclePosX, int cyclePosY)
{
    int playerX = player->getMesh()->pos().x();
    int playerY = player->getMesh()->pos().y();

    int deltaX = cyclePosX - playerX;
    int deltaY = cyclePosY - playerY;

    double distance = qSqrt(qPow(deltaX, 2) + qPow(deltaY, 2));

    return distance < MIN_DISTANCE_TO_CHARACTER;
}

void EnemyTank::calculateDestination(bool &targetReached, QPointF &randomDestination)
{
    if (targetReached || randomDestination.isNull())
    {
        int posX = getBoundX();
        int posY = getBoundY();
        randomDestination = QPointF(posX, posY);
        targetReached = false;
    }
}

QPointF EnemyTank::chooseRoute(const QPointF &tankPos, const QPointF &playerPos)
{
    QPointF target;

    qreal engageDistance = 550;

    int deltaX = tankPos.x() - playerPos.x();
    int deltaY = tankPos.y() - playerPos.y();

    double distance = qSqrt(qPow(deltaX, 2) + qPow(deltaY, 2));

    if (distance < engageDistance)
    {
        target = playerPos;
        engage = true;
        return target;
    }
    else
    {
        target = randomDestination;
        engage = false;
        return target;
    }
}

struct EnemyTank::Cell {
    QPointF position;
    double fScore;

    // Constructor
    Cell(QPointF pos, double f) : position(pos), fScore(f) {}
};

void EnemyTank::moveTowards(const QPointF &target)
{
    QPointF tankPos = getMesh()->pos();

    double g = size / 14;

    // Available cells for movement
    std::vector<Cell> availableCells;

    // Directions for movement: up, down, right, left
    std::vector<QPointF> directions = { {0, -1}, {0, 1}, {1, 0}, {-1, 0} };

    // Check all four directions
    for (const auto& direction : directions) {
        calculateCell(tankPos, target, direction, g, availableCells);
    }

    // Sort cells based on their f-score and move towards the best one
    std::sort(availableCells.begin(), availableCells.end(), [](const Cell& a, const Cell& b) {
        return a.fScore < b.fScore;});  // Sort based on f-score

    // Move to the best available cell if any exist
    handlingTankMovement(availableCells, tankPos);

    availableCells.clear();
}



void EnemyTank::calculateCell(const QPointF &currPos, const QPointF &target, const QPointF &direction, double g,  std::vector<Cell> &availableCells)
{
    QPointF newPos = currPos + direction * g;

    double h = abs(newPos.x() - target.x()) + abs(newPos.y() - target.y()); // Manhattan distance heuristic
    double f = g + h; // calculate distance for all free cells
    availableCells.emplace_back(newPos, f);
}

void EnemyTank::handlingTankMovement(const std::vector<Cell> &availableCells, const QPointF &tankPos)
{
    if (availableCells.empty()) return;

    QPointF nextPos = availableCells.front().position;

    getMesh()->setPos(nextPos);

    QPointF moveDirection = nextPos - tankPos;

    //Set transfrom point for hullMesh
    QPointF hullCenter = getMesh()->boundingRect().center();
    getMesh()->setTransformOriginPoint(hullCenter);

    //Set transform point for gunMesh
    QPointF gunCenter = getGunMesh()->boundingRect().center();
    getGunMesh()->setTransformOriginPoint(gunCenter);

    //set rotation
    //rotate Tank to the right
    if (moveDirection.x() > 0)
    {
        getMesh()->setRotation(90);
        getGunMesh()->setRotation(90);
        setDirection(EDirection::Right);
    }
    //rotate Tank to the left
    else if (moveDirection.x() < 0)
    {
        getMesh()->setRotation(-90);
        getGunMesh()->setRotation(-90);
        setDirection(EDirection::Left);
    }
    //rotate Tank to the bot
    else if (moveDirection.y() > 0)
    {
        getMesh()->setRotation(180);
        getGunMesh()->setRotation(180);
        setDirection(EDirection::Down);
    }
    //rotate Tank to the top
    else if (moveDirection.y() < 0)
    {
        getMesh()->setRotation(0);
        getGunMesh()->setRotation(0);
        setDirection(EDirection::Up);
    }

    getGunMesh()->setPos(getMesh()->pos().x() + 30, getMesh()->pos().y() - 10);
}

void EnemyTank::handlingTankShooting(const QPointF &tankPos, const QPointF &playerPos)
{
    qreal activationThreshold = 20;

    qreal stopThreshold = 2;


    if (shouldStartShooting(tankPos, playerPos,activationThreshold, stopThreshold))
    {
        engage = true;
        if (!scene->shootTank_timer->isActive())
        {
            scene->shootTank_timer->start(700);
        }
    }
    else if (shouldStopShooting(tankPos, playerPos,activationThreshold ))
    {
        engage = false;
        if (scene->shootTank_timer->isActive())
        {
            scene->shootTank_timer->stop();
        }
    }
}

bool EnemyTank::shouldStartShooting(const QPointF& tankPos, const QPointF& playerPos, qreal activationThreshold, qreal stopThreshold)
{
    return (std::abs(tankPos.x() - playerPos.x()) < activationThreshold && std::abs(tankPos.x() - playerPos.x()) >= stopThreshold) ||
           (std::abs(tankPos.y() - playerPos.y()) < activationThreshold && std::abs(tankPos.y() - playerPos.y()) >= stopThreshold);
}

bool EnemyTank::shouldStopShooting(const QPointF &tankPos, const QPointF &playerPos, qreal activationThreshold)
{
    return std::abs(tankPos.x() - playerPos.x()) > activationThreshold &&
           std::abs(tankPos.y() - playerPos.y()) > activationThreshold;
}

void EnemyTank::playDeathSound()
{
    AudioPlayer::activateSoundEffect(deathPathSound);
}

void EnemyTank::playHitSound()
{
    AudioPlayer::activateSoundEffect(hitPathSound);
}

int EnemyTank::getHealth()
{
    return health;
}

void EnemyTank::setStartHealthValue()
{
    health = 6;
}

void EnemyTank::decreaseHealth()
{
    --health;
}

void EnemyTank::setDirection(EDirection moveDirection)
{
    direction = moveDirection;
}

QGraphicsPixmapItem *EnemyTank::getGunMesh()
{
    return gunMesh;
}




