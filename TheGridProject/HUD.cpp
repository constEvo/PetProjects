#include "HUD.h"
#include "GameCharacter.h"
#include <QFontDatabase>
#include <Fonts.h>
#include "GameScene.h"


HUD::HUD(GameScene *gameScene, GameCharacter* playerCharacter) : scene(gameScene), player(playerCharacter)
{
    font = new GridFonts();

    //Shield HUD details
    shieldPath = QString(":/image/images/Shield.png");
    shieldPng  = QPixmap(shieldPath).scaled(45, 45, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
    shieldIcon = new QGraphicsPixmapItem(shieldPng);
    shieldCountdownText = new QGraphicsTextItem ();


    //Burst Weapon HUD details
    burstWeaponPath = QString(":/image/images/tripleShot.png");
    burstWeaponPng = QPixmap(burstWeaponPath).scaled(45, 45, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation );
    burstWeaponIcon = new QGraphicsPixmapItem(burstWeaponPng);
    burstWeaponCountdownText = new QGraphicsTextItem ();

    heartPath = QString(":/image/images/Heart.png");
    heartPng = QPixmap(heartPath).scaled(35, 35, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
    heartIcon = new QGraphicsPixmapItem(heartPng);


}

void HUD::initHUD()
{
    //Implementation of Shield HUD information
    if (player->getShieldStatus())
    {
        if (player->getShieldDurationTimer()->elapsed() <= player->SHIELD_DURATION)
        {
            if (!shieldIcon->isActive())
            {
                scene->addItem(shieldIcon);
                shieldIcon->setPos(300, 5);
            }

            if (!shieldCountdownText->isActive())
            {
                shieldCountdownText->setDefaultTextColor(QColor("#ff5c00"));
                shieldCountdownText->setFont(font->getHUDFont());
                shieldCountdownText->setPos(340, 12);
                scene->addItem(shieldCountdownText);
            }
            int i = (player->SHIELD_DURATION - player->getShieldDurationTimer()->elapsed()) / 1000;
            shieldCountdownText->setPlainText(QString::number(i));
        }
    }
    else if (!player->getShieldStatus())
    {
        if (shieldIcon->isActive())
        {
            scene->removeItem(shieldIcon);
        }
        if (shieldCountdownText->isActive())
        {
            scene->removeItem(shieldCountdownText);
        }
    }


    //Implementation of BurstWeapon HUD information
    if (player->getWeaponState() == EWeaponState::TripleShotWeapon)
    {
        if (player->getBurstWeaponDurationTimer()->elapsed() <= player->BURST_WEAPON_DURATION)
        {
            if (!burstWeaponIcon->isActive())
            {
                scene->addItem(burstWeaponIcon);
                burstWeaponIcon->setPos(400, 5);
            }

            if (!burstWeaponCountdownText->isActive())
            {
                burstWeaponCountdownText->setDefaultTextColor(QColor("#6df1d8"));
                burstWeaponCountdownText->setFont(font->getHUDFont());
                burstWeaponCountdownText->setPos(440, 12);
                scene->addItem(burstWeaponCountdownText);
            }
            int i = (player->BURST_WEAPON_DURATION - player->getBurstWeaponDurationTimer()->elapsed()) / 1000;
            burstWeaponCountdownText->setPlainText(QString::number(i));
        }
    }
    else if (player->getWeaponState() == EWeaponState::SingleShotWeapon)
    {
        if (burstWeaponIcon->isActive())
        {
            scene->removeItem(burstWeaponIcon);
        }
        if (burstWeaponCountdownText->isActive())
        {
            scene->removeItem(burstWeaponCountdownText);
        }
    }

    //Implementation of Heart HUD information
    if (!heartIcon->isActive())
    {
        scene->addItem(heartIcon);
        heartIcon->setPos(150, 10);
    }

}



