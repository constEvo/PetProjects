#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "Character.h"
#include "EStates.h"

class GameScene;
class GameCharacter;
class QRandomGenerator;


class EnemyTank : public Character
{
    Q_OBJECT
public:
    GameScene* scene;
    GameCharacter* player;

    EnemyTank(int size, GameCharacter* playerCharacter, GameScene* gameScene);
    ~EnemyTank();

    void initCharacter(int startX, int startY) override;

    QGraphicsPixmapItem *getGunMesh();

    void setDirection(EDirection moveDirection);

    //spawn functions
    int getBoundX();
    int getBoundY();
    bool isTooCloseToPlayer(int cyclePosX, int cyclePosY);

    //movement functions
    void calculateDestination(bool& targetReached, QPointF& randomDestination);
    QPointF chooseRoute(const QPointF& tankPos, const QPointF& playerPos);
    void moveTowards(const QPointF& target);
    struct Cell;
    void calculateCell(const QPointF& currPos, const QPointF& target, const QPointF& direction, double g, std::vector<Cell>& availableCells);
    void handlingTankMovement(const std::vector<Cell>& availableCells, const QPointF& tankPos);

    //combat functions
    //colliding with player
    bool checkCollidingWithPlayer();
    void handleCollidingWithPlayer();

    //shooting functions
    void handlingTankShooting(const QPointF& tankPos, const QPointF& playerPos);
    bool shouldStartShooting(const QPointF& tankPos, const QPointF& playerPos, qreal activationThreshold, qreal stopThreshold);
    bool shouldStopShooting(const QPointF& tankPos, const QPointF& playerPos, qreal activationThreshold);

    //sound functions
    void playDeathSound();
    void playHitSound();

    //health management functions
    int getHealth();
    void setStartHealthValue();
    void decreaseHealth();

private:

    //mesh
    QString gunMeshPath;
    QPixmap gunPng;
    QGraphicsPixmapItem* gunMesh;

    QRandomGenerator* rand;

    EDirection direction;

    const int MIN_ENGAGE_DISTANCE = 600;
    const int MIN_DISTANCE_TO_CHARACTER = 300;

    QPointF randomDestination;
    bool targetReached;

    int health;

    bool engage;

    QTimer* shootTimer;

    QString deathPathSound;
    QString hitPathSound;


public slots:
void move();
void shoot();

};
#endif // ENEMYTANK_H
