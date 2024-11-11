#include "Apple.h"
#include <QTimer>
#include "Score.h"
#include "AudioPlayer.h"
#include "GameScene.h"


Apple::Apple(int size, GameScene* gameScene, GameCharacter* playerCharacter, Score* playerScore)
    : Item(size, ":/image/images/memoryBank.png", gameScene, playerCharacter ),
    score(playerScore),
    scene(gameScene)
{
    overlapSoundPath = QString("qrc:/sounds/sound/PickUpApple.mp3");

    overlap_timer = new QTimer();
    QObject::connect(overlap_timer, SIGNAL(timeout()), this, SLOT(overlappingApple()));
    overlap_timer->start(100);
}

Apple::~Apple()
{

}

void Apple::spawnItem()
{
    Item::spawnItem();
}

void Apple::overlapItem()
{
    Item::overlapItem();
}

void Apple::playOverlapItemSound()
{
    AudioPlayer::activateSoundEffect(overlapSoundPath);
}

QUrl Apple::getOverlapSoundPath()
{
    return overlapSoundPath;
}

QGraphicsPixmapItem* Apple::getApple()
{
    return this->getItem();
}


void Apple::overlappingApple()
{
    overlapItem();
    if (this->isOverlapped)
    {
        playOverlapItemSound();

        score->increaseScore(1);

        delete this->getItem();
        spawnItem();
        this->isOverlapped = false;
    }

}
