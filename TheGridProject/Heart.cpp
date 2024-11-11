#include "Heart.h"
#include "GameCharacter.h"
#include "GameScene.h"
#include "Health.h"
#include "algorithm"
#include <QTimer>
#include "AudioPlayer.h"


Heart::Heart(int size, GameScene *gameScene, GameCharacter *playerCharacter) :
    Item(size, ":/image/images/Heart.png", gameScene, playerCharacter),
    scene(gameScene),
    player(playerCharacter)
{
    overlapSoundPath = QString("qrc:/sounds/sound/HeartPickUp.mp3");

    overlap_timer = new QTimer();
    QObject::connect(overlap_timer, SIGNAL(timeout()), this, SLOT(overlappingHeart()));
    overlap_timer->start(100);

}

Heart::~Heart()
{

}

void Heart::spawnItem()
{
    Item::spawnItem();
}


void Heart::overlapItem()
{
    Item::overlapItem();
}

void Heart::playOverlapItemSound()
{
    AudioPlayer::activateSoundEffect(overlapSoundPath);
}

QUrl Heart::getOverlapSoundPath()
{
    return overlapSoundPath;
}

QGraphicsPixmapItem *Heart::getHeart()
{
    this->getItem();
}

void Heart::overlappingHeart()
{
    overlapItem();
    if (this->isOverlapped)
    {
        playOverlapItemSound();

        Health* health = player->getHealth();
        health->increaseHealth();

        std::vector<Heart*>::iterator instance = std::find(scene->activeHearts.begin(), scene->activeHearts.end(), this);
        if (instance != scene->activeHearts.end())
        {
            scene->activeHearts.erase(instance);
            delete this;
        }
    }
}

