#ifndef APPLE_H
#define APPLE_H

#include "Item.h"
#include <QUrl>

class GameCharacter;
class Score;

class Apple : public Item
{
    Q_OBJECT
public:
    GameScene* scene;
    GameCharacter* player;
    Score* score;

    Apple(int size, GameScene* gameScene, GameCharacter* playerCharacter, Score* score);

    ~Apple();

    QGraphicsPixmapItem* getApple();

    void spawnItem() override;

    void overlapItem() override;

    void playOverlapItemSound() override;

    QUrl getOverlapSoundPath();

    //QTimer* overlap_timer;
private:

private slots:
    void overlappingApple();

};

#endif // APPLE_H
