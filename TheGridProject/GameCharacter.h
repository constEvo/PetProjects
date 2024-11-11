#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "Character.h"
#include <QGraphicsPixmapItem>
#include "EStates.h"
#include "QUrl"
#include <QKeyEvent>

class QElapsedTimer;
class GameScene;
class Health;
class QMediaPlayer;
class QAudioOutput;
class Cycle;
class EnemyTank;

class GameCharacter : public Character
{
    Q_OBJECT
public:
    GameScene* scene;

    GameCharacter(GameScene* gameScene,int size);

    ~GameCharacter();

    void initCharacter(int startX, int startY) override;

    void deleteCharacter();

    QGraphicsPixmapItem* getMesh();

    EDirection getDirectionState();

    void keyPressEvent(QKeyEvent *event);

    //action functions
    void move();
    void shoot();
    void stopLocomotion();

    void checkCollision();

    QRectF getAdjustedPlayerRect();

    EWeaponState getWeaponState();
    void setWeaponState(EWeaponState weaponState);

    //combat functions
    void collidingWithEnemy();
    template<typename T>
    bool checkCollisionWithEnemy(T* py, const QRectF &playerRect);
    void handleCycleCollision(Cycle* py, int index);
    void handleTankColliding();

    //health management functions
    Health *getHealth();
    void setDefaultHealthValue();
    QElapsedTimer* getHealthCooldownTimer();

    //pick-up effects functions
    //Shield effects functions
    bool getShieldStatus();
    void setShieldStatus(bool status);
    void shieldHasEnabled(Cycle* py, int index);
    void shieldHasDisabled();
    QElapsedTimer *getShieldDurationTimer();
    void startShieldDurationTimer();
    //Burst Weapon effects functions
    QElapsedTimer *getBurstWeaponDurationTimer();
    void startBurstWeaponDurationTimer();

    //media functions
    void playHitSound();

    const int MAX_HEALTH = 3;

    const int SHIELD_DURATION = 10000;

    const int BURST_WEAPON_DURATION = 5000;

    const int healthCooldownDuration = 2500;

    const std::vector<QPoint> directionUV = { {0, 0,}, {0, -1}, {0, 1}, {-1, 0}, {1, 0} }; // Idle, Up, Down, Left, Right

    int health;

private:

    //input variables
    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;

    QVector<QGraphicsPixmapItem*> vPlayer;

    Health* healthString;
    QElapsedTimer* healthCooldownTimer;

    bool isShieldActive;
    bool isHit;
    EWeaponState weaponState;
    EDirection currentDirection;


    QString hitSoundPath;

    QElapsedTimer* shieldDurationTimer;
    QElapsedTimer* burstWeaponDurationTimer;


};

#endif // GAMECHARACTER_H
