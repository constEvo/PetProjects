#include "Cycle.h"
#include <QRandomGenerator>
#include <QTimer>
#include "GameCharacter.h"
#include "Apple.h"
#include "GameScene.h"
#include "AudioPlayer.h"

Cycle::Cycle(int size, GameCharacter* playerCharacter, GameScene* gameScene) :
    Character(size,":/image/images/enemy.png"),
    player(playerCharacter),
    scene(gameScene)
{
            initCharacter(0, 0);
            moveDirection = EDirection::Idle;

            crashed = false;
            targetReached = false;

            deathCycleSoundPath = QString("qrc:/sounds/sound/DestroyedPython.wav");


            QObject::connect(scene->moveCycle_timer, SIGNAL(timeout()), this, SLOT(move()));
}

Cycle::~Cycle()
{
    if (getMesh())
    {
        scene->removeItem(getMesh());
        delete characterMesh;
        characterMesh = nullptr;
    }
}

void Cycle::initCharacter(int startX, int startY)
{
    characterMesh = new QGraphicsPixmapItem(meshPng);

    rand = QRandomGenerator::global();
    do
    {
        startX = getBoundX();
        startY = getBoundY();
    } while (isTooCloseToPlayer(startX, startY));

    characterMesh->setPos(startX, startY);
    characterMesh->setZValue(1);
    scene->addItem(characterMesh);
    setStartHealthValue();
}


QGraphicsPixmapItem *Cycle::getMesh()
{
    return characterMesh;
}

int Cycle::getBoundX()
{
    if (scene)
    {
        int first = 1;
        int second = scene->gameCanvasWidth / size;
        int randPosX = rand->bounded(first, second);
        return randPosX * size ;
    }
}

int Cycle::getBoundY()
{
    if (scene)
    {
        int first = 3;
        int second = scene->gameCanvasHeight / size;
        int randPosY = rand->bounded(first, second);
        return randPosY * size;
    }
}

bool Cycle::isTooCloseToPlayer(int cyclePosX, int cyclePosY)
{
    int playerX = player->getMesh()->pos().x();
    int playerY = player->getMesh()->pos().y();

    int deltaX = cyclePosX - playerX;
    int deltaY = cyclePosY - playerY;

    double distance = qSqrt(qPow(deltaX, 2) + qPow(deltaY, 2));

    return distance < MIN_DISTANCE_TO_CHARACTER;
}


void Cycle::move()
{
    QPointF cyclePos = getMesh()->pos();

    calculateDestination(targetReached, randomDestination);

    moveTowards(chooseRoute(cyclePos));

    if (distance(cyclePos, randomDestination) < 10)
    {
        targetReached = true;
    }
}

void Cycle::calculateDestination(bool& targetReached, QPointF& randomDestination)
{
    if (targetReached || randomDestination.isNull())
    {
        int posX = getBoundX() / 1.5;
        int posY = getBoundY() / 1.5;
        randomDestination = QPointF(posX, posY);
        targetReached = false;
    }
}

QPointF Cycle::chooseRoute(const QPointF& cyclePos)
{
    QPointF playerPos = player->getMesh()->pos();
    QPointF target;
    qreal engageDistance = 150;

    // Adjust movement based on proximity to the player
    if ( distance(cyclePos, playerPos) < engageDistance )
    {
        // Chase the target if close enough
        target = playerPos;
        speed = size / 6;
        return target;
    }
    else
    {
        //Take route to the destination
        target = randomDestination;
        speed = size / 10;
        return target;
    }
}

double Cycle::distance(const QPointF &p1, const QPointF &p2)
{
    //calculate distance between two points
    return std::sqrt(std::pow(p1.x() - p2.x(), 2) + (std::pow(p1.y() - p2.y(), 2)));
}

struct Cycle::Cell {
    QPointF position;
    double fScore;

    // Constructor
    Cell(QPointF pos, double f) : position(pos), fScore(f) {}
};

void Cycle::moveTowards(const QPointF &target)
{
    QPointF currPos = getMesh()->pos();
    //speed enemy
    double g = speed;

    // Available cells for movement
    std::vector<Cell> availableCells;

    // Directions for movement: up, down, right, left
    std::vector<QPointF> directions = { {0, -1}, {0, 1}, {1, 0}, {-1, 0} };

    // Check all four directions
    for (const auto& direction : directions) {
        calculateCell(currPos, target, direction, g,  availableCells);
    }

    // Sort cells based on their f-score and move towards the best one
    std::sort(availableCells.begin(), availableCells.end(), [](const Cell& a, const Cell& b) {
        return a.fScore < b.fScore;});  // Sort based on f-score

    handlingCycleMovement(availableCells, currPos);

    availableCells.clear();
}


void Cycle::calculateCell(const QPointF& currPos, const QPointF& target, const QPointF& direction, double g,  std::vector<Cell>& availableCells)
{
    QPointF newPos = currPos + direction * g;

    double h = abs(newPos.x() - target.x()) + abs(newPos.y() - target.y()); // Manhattan distance heuristic
    double f = g + h; // calculate distance for all free cells
    availableCells.emplace_back(newPos, f);
}

void Cycle::handlingCycleMovement(const std::vector<Cell> &availableCells, const QPointF& cyclePosition)
{
    // Move to the best available cell if any exist
    if (availableCells.empty()) return;

    QPointF nextPos = availableCells.front().position;

    getMesh()->setPos(nextPos);

    QPointF direction = nextPos - cyclePosition;

    //Set transfrom point
    QPointF center = getMesh()->boundingRect().center();
    getMesh()->setTransformOriginPoint(center);

    //set rotation
    //rotate lightCycle to right
    if (direction.x() > 0)
    {
        getMesh()->setRotation(90);
        setMoveDirection(EDirection::Right);
    }
    //rotate lightCycle to left
    else if (direction.x() < 0)
    {
        getMesh()->setRotation(-90);
        setMoveDirection(EDirection::Left);
    }
    //rotate lightCycle to bot
    else if (direction.y() > 0)
    {
        getMesh()->setRotation(180);
        setMoveDirection(EDirection::Down);
    }
    //rotate lightCycle to top
    else if (direction.y() < 0)
    {
        getMesh()->setRotation(0);
        setMoveDirection(EDirection::Up);
    }
}

void Cycle::setMoveDirection(EDirection newMoveDirection)
{
    moveDirection = newMoveDirection;
}


void Cycle::playDeathSound()
{
    AudioPlayer::activateSoundEffect(deathCycleSoundPath);
}

void Cycle::playHitSound()
{

}

int Cycle::getHealth()
{
    return health;
}

void Cycle::setStartHealthValue()
{
    health = 1;
}

void Cycle::decreaseHealth()
{
    --health;
}


