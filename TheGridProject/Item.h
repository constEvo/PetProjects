#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsPixmapItem>
#include <QUrl>
#include <QObject>
#include <QRandomGenerator>
#include <QMediaPlayer>
#include <QAudioOutput>


class GameScene;
class GameCharacter;

class Item : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GameScene* scene;
    GameCharacter* player;

    Item(int itemSize, const QString& itemPath, GameScene* gameScene, GameCharacter* playerCharacter);
    virtual ~Item();

    virtual void spawnItem();

    int getBoundX();
    int getBoundY();

    virtual void overlapItem();

    virtual void playOverlapItemSound() = 0;

    QGraphicsPixmapItem *getItem();

    QTimer* overlap_timer;
protected:

    QGraphicsPixmapItem* itemPng;

    QRandomGenerator* rand;

    QPixmap item;

    int size;

    QString overlapSoundPath;

    bool isOverlapped;




};

#endif // ITEM_H
