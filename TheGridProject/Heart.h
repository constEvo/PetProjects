#ifndef HEART_H
#define HEART_H

#include "Item.h"

class Heart : public Item
{
    Q_OBJECT
public:
    GameScene* scene;
    GameCharacter* player;

    Heart(int size, GameScene* gameScene, GameCharacter* playerCharacter);

    ~Heart();

    void spawnItem() override;

    void overlapItem() override;

    void playOverlapItemSound() override;

    QGraphicsPixmapItem *getHeart();

    QUrl getOverlapSoundPath();

    //QTimer* overlap_timer;

private slots:
    void overlappingHeart();
};

#endif // HEART_H
