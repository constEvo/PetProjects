#include <Menu.h>
#include <QPushButton>
#include <Fonts.h>
#include <QGraphicsTextItem>

Menu::Menu()
{
    setSceneRect(0, 0, 800, 600);

    //create font
    font = new GridFonts();

    //Create Label for Game Name
    QGraphicsTextItem* label = new QGraphicsTextItem();
    label->setPlainText("The Grid");
    label->setDefaultTextColor(Qt::white);
    label->setFont(font->getTitleFont());
    label->setPos(320, 70);
    addItem(label);

    /*
    //Add Snake to Menu
    snake = QPixmap(":/image/images/snake.png");
    snake = snake.scaled(100, 100, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
    snakePng = new QGraphicsPixmapItem(snake);
    snakePng->setPos(450, 20);
    addItem(snakePng);
*/

    //Set Qpixmap for Button Icon
    buttonPath = QString(":/image/images/Menu/Button.png");
    buttonPng = QPixmap(buttonPath);



    //Create Start Game Button
    startButton = new QPushButton("Start Game");
    startButton->setVisible(true);
    startButton->setFont(font->getHUDFont());
    startButton->setStyleSheet("QPushButton {"
                                "border-image : url(:/image/images/Menu/Button.png) stretch ;"
                                "color: white;"
                                "padding-bottom: 10px; }");
    startButton->resize(200, 50);
    startButton->move(300, 200);
    startProxy = addWidget(startButton);


    //Create Settings Button
    settingsButton = new QPushButton("Settings");
    settingsButton->setVisible(true);
    settingsButton->setFont(font->getHUDFont());
    settingsButton->setStyleSheet("QPushButton {"
                                    "border-image : url(:/image/images/Menu/Button.png) stretch;"
                                    "color: white;"
                                    "padding-bottom: 10px; }");
    settingsButton->resize(200, 50);
    settingsButton->move(300, 250);
    settingsProxy = addWidget(settingsButton);

    //Create Exit Button
    exitButton = new QPushButton("Exit Game");
    exitButton->setVisible(true);
    exitButton->setFont(font->getHUDFont());
    exitButton->setStyleSheet("QPushButton {"
                                "border-image : url(:/image/images/Menu/Button.png) stretch;"
                                "color: white; "
                                "padding-bottom : 10px;}");
    exitButton->resize(200, 50);
    exitButton->move(300, 300);
    exitProxy = addWidget(exitButton);

}
