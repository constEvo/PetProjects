#include <Shield.h>
#include "GameCharacter.h"
#include "GameScene.h"
#include <QTimer>
#include <algorithm>
#include "AudioPlayer.h"

Shield::Shield(int size, GameScene* gameScene, GameCharacter* playerCharacter) :
    Item(size, ":/image/images/Shield.png", gameScene, playerCharacter),
    scene(gameScene),
    player(playerCharacter)
{
    overlapSoundPath = QString("qrc:/sounds/sound/ShieldPickUp.mp3");

    overlap_timer = new QTimer();
    QObject::connect(overlap_timer, SIGNAL(timeout()), this, SLOT(overlappingShield()));
    overlap_timer->start(100);
}

Shield::~Shield()
{

}

void Shield::spawnItem()
{
    Item::spawnItem();
}

void Shield::overlapItem()
{
    Item::overlapItem();
}

void Shield::playOverlapItemSound()
{
    AudioPlayer::activateSoundEffect(overlapSoundPath);
}

QUrl Shield::getOverlapSoundPath()
{
    return overlapSoundPath;
}

QGraphicsPixmapItem *Shield::getShield()
{
    return this->getItem();
}

void Shield::overlappingShield()
{
    overlapItem();
    if (this->isOverlapped)
    {
        playOverlapItemSound();

        player->setShieldStatus(true);
        player->startShieldDurationTimer();

        std::vector<Shield*>::iterator instance = std::find(scene->activeShields.begin(), scene->activeShields.end(), this);
        if (instance != scene->activeShields.end())
        {
            scene->activeShields.erase(instance);
            delete this;
        }

    }
}
