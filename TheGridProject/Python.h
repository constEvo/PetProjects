#ifndef PYTHON_H
#define PYTHON_H


#include "Character.h"
#include "EStates.h"
#include "QUrl"
#include "QObject"
#include <vector>


class GameCharacter;
class GameScene;
class Apple;
class QRandomGenerator;

class Python : public Character
{
    Q_OBJECT
public:
    GameCharacter* player;
    GameScene* scene;


    Python(int size, GameCharacter* playerCharacter, GameScene* gameScene);

    ~Python() = default;

    void initCharacter(int startX, int startY) override;
    void deleteCharacter() override;

    QGraphicsPixmapItem* getMesh();

    //void setLength();
    void pickUpApple(Apple* apple);

    int getBoundX();
    int getBoundY();

    bool isTooCloseToPlayer(int cyclePosX, int cyclePosY);

    void playDeathSound();

    bool crashed;

    QVector<QGraphicsPixmapItem*> vPython;
    struct Cell;

protected:

    double distance(const QPointF& p1, const QPointF& p2);

    void moveTowards(const QPointF &target);

    void calculateCell(const QPointF& currPos, const QPointF& target, const QPointF& direction, double g, std::vector<Cell>& availableCells);

    void setMoveDirection(EDirection newMoveDirection);

    void handlingCycleMovement(const std::vector<Cell>& availableCells, const QPointF& cyclePosition);

    void calculateDestination(bool& targetReached, QPointF& randomDestination);

    QPointF chooseRoute(const QPointF& cyclePos);


private:

    QRandomGenerator* rand;
    const int MIN_DISTANCE_TO_CHARACTER = 150;

    QMediaPlayer* deathMediaPlayer;
    QAudioOutput* deathOutput;
    QUrl deathPythonSoundPath;

    bool targetReached;
    QPointF randomDestination;

    EDirection moveDirection;

    QTimer* shootingTimer;
    QTimer* moveTimer;

    int speed;


private slots:
void move();
};

#endif // PYTHON_H
