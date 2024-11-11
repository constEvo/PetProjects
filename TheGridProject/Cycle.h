#ifndef CYCLE_H
#define CYCLE_H


#include "Character.h"
#include "EStates.h"
#include "QUrl"
#include "QObject"
#include <vector>


class GameCharacter;
class GameScene;
class Apple;
class QRandomGenerator;


class Cycle : public Character
{
    Q_OBJECT
public:
    GameCharacter* player;
    GameScene* scene;

    Cycle(int size, GameCharacter* playerCharacter, GameScene* gameScene);

    ~Cycle();

    void initCharacter(int startX, int startY) override;

    QGraphicsPixmapItem* getMesh();

    //spawn Functions
    int getBoundX();
    int getBoundY();
    bool isTooCloseToPlayer(int cyclePosX, int cyclePosY);

    //movement function
    double distance(const QPointF& p1, const QPointF& p2);
    void moveTowards(const QPointF &target);
    struct Cell;
    void calculateCell(const QPointF& currPos, const QPointF& target, const QPointF& direction, double g, std::vector<Cell>& availableCells);
    void setMoveDirection(EDirection newMoveDirection);
    void handlingCycleMovement(const std::vector<Cell>& availableCells, const QPointF& cyclePosition);
    void calculateDestination(bool& targetReached, QPointF& randomDestination);
    QPointF chooseRoute(const QPointF& cyclePos);

    //health management functions
    int getHealth();
    void setStartHealthValue();
    void decreaseHealth();

    //media functions
    void playDeathSound();
    void playHitSound();

    bool crashed;

private:

    QRandomGenerator* rand;
    const int MIN_DISTANCE_TO_CHARACTER = 150;

    QString deathCycleSoundPath;

    bool targetReached;
    QPointF randomDestination;

    EDirection moveDirection;

    int speed;
    int health;


private slots:
void move();
};

#endif // CYCLE_H
