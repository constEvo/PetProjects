#include "Health.h"
#include "GameCharacter.h"
#include <Fonts.h>

Health::Health(GameCharacter* playerCharacter, QGraphicsItem *parent) : player(playerCharacter)
{

    setPlainText(("x") + QString::number(player->health));
    setDefaultTextColor(QColor(255, 56, 100, 255));
    font = new GridFonts();
    setFont(font->getHUDFont());
    setPos(180, 10);
}

void Health::increaseHealth()
{
    player->health += 1;
    setPlainText(("x") + QString::number(player->health));
}

void Health::decreaseHealth()
{
    player->health -= 1;
    setPlainText(("x") + QString::number(player->health));
}

int Health::getHealth()
{
    return player->health;
}

void Health::setDefaultHealthValue()
{
    player->health = 3;
    setPlainText(("x") + QString::number(player->health));
}
