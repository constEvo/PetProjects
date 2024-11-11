#ifndef MENU_H
#define MENU_H

#include <QGraphicsScene>
#include "EStates.h"

class GameScene;
class QPushButton;
class GridFonts;


class Menu : public QGraphicsScene
{

public:
    Menu();

    //Buttons
    QPushButton* startButton;
    QPushButton* settingsButton;
    QPushButton* exitButton;

    //Buttons Image
    QString buttonPath;
    QPixmap buttonPng;


private:
    GameScene* game;

    QPixmap snake;
    QGraphicsPixmapItem* snakePng;

    QGraphicsProxyWidget* startProxy;
    QGraphicsProxyWidget* settingsProxy;
    QGraphicsProxyWidget* exitProxy;



    //Font
    GridFonts* font;
};

#endif // MENU_H
