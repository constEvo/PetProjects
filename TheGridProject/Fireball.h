#ifndef FIREBALL_H
#define FIREBALL_H

#include "Projectile.h"
#include "EStates.h"

class Cycle;
class GameScene;

class Fireball : public Projectile
{
    Q_OBJECT
public:
    GameScene* scene;

    Fireball(int fireballSize, const EDirection& direction, GameScene* gameScene);

    ~Fireball();

    void spawnProjectile(int posX, int posY) override;

    void playShotSound() override;

    void calculatingDirection();

    template<typename T>
    bool checkCollisionWithEnemy(T* py);

    template<typename T>
    void handleCollidingWithEnemy(T* enemy, std::vector<T*> &activeEnemies, int &enemyCount, int index, int reward);

    bool isOutOfScene(QGraphicsPixmapItem* fireballMesh);

private:
    QGraphicsPixmapItem* fireballPng;
    EDirection fireballDirection;

    bool isHit;
private slots:
    void move();
};

#endif // FIREBALL_H
