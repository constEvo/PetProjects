#ifndef SHIELD_H
#define SHIELD_H

#include "Item.h"

class Shield : public Item
{
    Q_OBJECT
public:
    GameScene* scene;
    GameCharacter* player;

    Shield(int size, GameScene* gameScene, GameCharacter* playerCharacter);
    ~Shield();

    void spawnItem() override;

    void overlapItem() override;

    void playOverlapItemSound() override;

    QUrl getOverlapSoundPath();

    QGraphicsPixmapItem *getShield();

    //QTimer* overlap_timer;
private:

private slots:
    void overlappingShield();

};

#endif // SHIELD_H
