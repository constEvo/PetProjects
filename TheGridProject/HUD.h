#ifndef HUD_H
#define HUD_H

#include "QGraphicsPixmapItem"
#include <QWidget>
#include <QObject>



class GameScene;
class GameCharacter;
class GridFonts;


class HUD : public QObject
{
    Q_OBJECT
public:
    GameScene* scene;
    GameCharacter* player;

    HUD(GameScene* gameScene, GameCharacter* playerCharacter);

    void initHUD();

    QGraphicsProxyWidget* cpbarProxy;

private:
    //Shield HUD details
    QGraphicsPixmapItem* shieldIcon;
    QPixmap shieldPng;
    QString shieldPath;
    QGraphicsTextItem* shieldCountdownText;
    bool shieldHUD;

    //Burst Weapon HUD details
    QGraphicsPixmapItem* burstWeaponIcon;
    QPixmap burstWeaponPng;
    QString burstWeaponPath;
    QGraphicsTextItem* burstWeaponCountdownText;

    //Heart HUD details
    QGraphicsPixmapItem* heartIcon;
    QPixmap heartPng;
    QString heartPath;

    //Font
    GridFonts* font;

};








#endif // HUD_H
