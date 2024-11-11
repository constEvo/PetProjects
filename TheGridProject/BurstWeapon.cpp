#include "BurstWeapon.h"
#include "GameCharacter.h"
#include "GameScene.h"
#include "EStates.h"
#include <QTimer>
#include "algorithm"
#include "AudioPlayer.h"

BurstWeapon::BurstWeapon(int size, GameScene *gameScene, GameCharacter *playerCharacter) :
    Item(size, ":/image/images/tripleShot.png", gameScene, playerCharacter ),
    scene(gameScene),
    player(playerCharacter)
{
    overlapSoundPath = "qrc:/sounds/sound/overlapBurstWeapon.wav";

    overlap_timer = new QTimer();
    QObject::connect(overlap_timer, SIGNAL(timeout()), this, SLOT(overlappingBurstWeapon()));
    overlap_timer->start(100);

}

BurstWeapon::~BurstWeapon()
{

}

void BurstWeapon::spawnItem()
{
    Item::spawnItem();
}

void BurstWeapon::overlapItem()
{
    Item::overlapItem();
}

void BurstWeapon::playOverlapItemSound()
{
    AudioPlayer::activateSoundEffect(overlapSoundPath);
}


void BurstWeapon::overlappingBurstWeapon()
{
    overlapItem();
    if (this->isOverlapped)
    {
        playOverlapItemSound();

        player->setWeaponState(EWeaponState::TripleShotWeapon);
        player->startBurstWeaponDurationTimer();


        std::vector<BurstWeapon*>::iterator instance = std::find(scene->activeBurstWeapon.begin(), scene->activeBurstWeapon.end(), this);
        if (instance != scene->activeBurstWeapon.end())
        {
            scene->activeBurstWeapon.erase(instance);
            delete this;
        }
    }
}
