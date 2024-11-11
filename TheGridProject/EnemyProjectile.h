#ifndef ENEMYPROJECTILE_H
#define ENEMYPROJECTILE_H


#include "Projectile.h"
#include "EStates.h"

class GameScene;
class GameCharacter;

class EnemyProjectile : public Projectile
{
    Q_OBJECT
public:
    GameScene* scene;
    GameCharacter* player;

    EnemyProjectile(int size, const EDirection& direction, GameScene* gameScene, GameCharacter* playerCharacter);

    ~EnemyProjectile();

    void spawnProjectile(int posX, int posY) override;

    void playShotSound() override;

    void handleEnemyShotMoveDirection();

    bool checkPlayerCollision();

    void handleCollidingWithPlayer();

    bool isOutOfBoundaries();

    QGraphicsPixmapItem* getMesh();

    //void collidingWithPlayer(GameCharacter* player);

private:
    QGraphicsPixmapItem* enemyProjectileMesh;
    EDirection enemyProjectileDirection;

    bool isHit;

private slots:
    void move();
};

#endif // ENEMYPROJECTILE_H
