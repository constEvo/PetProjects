#ifndef BURSTWEAPON_H
#define BURSTWEAPON_H

#include "Item.h"

class BurstWeapon : public Item
{
    Q_OBJECT
public:
    GameScene* scene;
    GameCharacter* player;

    BurstWeapon(int size, GameScene* gameScene, GameCharacter* playerCharacter);

    ~BurstWeapon();

    void spawnItem() override;

    void overlapItem() override;

    void playOverlapItemSound() override;


private slots:
    void overlappingBurstWeapon();
};

#endif // BURSTWEAPON_H
