#ifndef TRIPLESHOT_H
#define TRIPLESHOT_H

#include "Projectile.h"
#include "EStates.h"

class GameScene;
class Cycle;

class TripleShot : public Projectile
{
    Q_OBJECT
public:
    GameScene* scene;

    TripleShot(int fireballSize, const EDirection& direction, GameScene* gameScene);

    ~TripleShot();

    void spawnProjectile( int posX, int posY) override;

    void playShotSound() override;

    void handleLeftShotMoveDirection();
    void handleMidShotMoveDirection();
    void handleRightShotMoveDirection();

    template<typename T>
    bool checkCollisionWithEnemy(T* enemy, std::vector<QGraphicsPixmapItem*>& tripleShot);

    template<typename T>
    void handleCollidingWithEnemy(T* enemy, std::vector<T*> &activeEnemy, int &enemyCount, int index, int reward);

    void passBoundaries(QGraphicsPixmapItem* shotMesh);

    bool isOutOfScene(QGraphicsPixmapItem* shotMesh);

private:
    QGraphicsPixmapItem* leftShotPng;
    QGraphicsPixmapItem* midShotPng;
    QGraphicsPixmapItem* rightShotPng;
    EDirection tripleShotlDirection;

    bool isHit;
private slots:
    void move();
};

#endif // TRIPLESHOT_H
