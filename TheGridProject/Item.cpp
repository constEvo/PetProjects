#include "Item.h"
#include <GameCharacter.h>
#include "GameScene.h"
#include <QTimer>




Item::Item(int itemSize, const QString& itemPath, GameScene* gameScene, GameCharacter* playerCharacter) :
    size(itemSize),
    scene(gameScene),
    player(playerCharacter)
{
    item = QPixmap(itemPath).scaled(size, size, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
    isOverlapped = false;
}

Item::~Item()
{

    if (overlap_timer)
    {
        overlap_timer->stop();
        delete overlap_timer;
        overlap_timer = nullptr;

    }

    if (itemPng && scene)
    {
        scene->removeItem(itemPng);
        delete itemPng;
        itemPng = nullptr;
    }

}

void Item::spawnItem()
{
    itemPng = new QGraphicsPixmapItem(item);
    scene->addItem(itemPng);

    rand = QRandomGenerator::global();

    int item_x = getBoundX();
    int item_y = getBoundY();

    itemPng->setPos(item_x, item_y);

}



int Item::getBoundX()
{
    if (scene)
    {
        int first = 1;
        int second = scene->gameCanvasWidth / size;
        int randPosX = rand->bounded(first, second);
        return randPosX * size;
    }
}

int Item::getBoundY()
{
    if (scene)
    {
        int first = 3;
        int second = scene->gameCanvasHeight / size;
        int randPosY = rand->bounded(first, second);
        return randPosY * size;
    }
}


void Item::overlapItem()
{
    const int collisionRange = 5;
    //calculate collision for player's head
    QRectF playerRect = player->getMesh()->boundingRect().translated(player->getMesh()->pos());
    playerRect = player->getAdjustedPlayerRect();
    //calcualate collision for apple
    QRectF itemRect = this->getItem()->boundingRect().translated(this->getItem()->pos());
    //add collision range to appleItem
    itemRect.adjust(collisionRange, -collisionRange, collisionRange, -collisionRange);

    if (playerRect.intersects(itemRect))
    {
        isOverlapped = true;
        return;
    }
}


QGraphicsPixmapItem *Item::getItem()
{
    return itemPng;
}
