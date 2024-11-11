#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>


class GameCharacter;
class GridFonts;

class Health : public QGraphicsTextItem
{
public:
    GameCharacter* player;

    Health(GameCharacter* playerCharacter, QGraphicsItem* parent = nullptr);

    int getHealth();

    void setDefaultHealthValue();

    void increaseHealth();

    void decreaseHealth();

private:
    //Font
    GridFonts* font;
};

#endif // HEALTH_H
