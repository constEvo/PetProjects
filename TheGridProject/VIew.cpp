 #include "View.h"
#include "Menu.h"
#include "Settings.h"
#include "GameScene.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPushButton>
#include <QComboBox>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QLabel>
#include <QSlider>
#include <QApplication>
#include <QKeyEvent>
#include "AudioPlayer.h"

View::View()
{
    screenWidth = 800;
    screenHeight = 600;
    setFixedSize(screenWidth, screenHeight);
    setSceneRect(0, 0, screenWidth, screenHeight);
    fitInView(0, 0, screenWidth, screenHeight, Qt::KeepAspectRatio);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    menuWindow = QPixmap(":/image/images/Menu/MenuWindow.png").scaled(800, 600);

    setStyleSheet("border-image : url(://image/images/Menu/MenuWindow.png) 0 0 0 0 stretch stretch") ;
    //setBackgroundBrush(QBrush(menuWindow));

    menu = new Menu();
    setScene(menu);

    game = new GameScene();

    settings = new Settings();

    game->setGameState(EGameState::InMenu);

    buttonSoundPath = QString("qrc:/sounds/sound/ButtonBloop.mp3");

    //set mediaPlayer for backgroundMusic
    if (game->getGameState() == EGameState::InMenu)
    {
        AudioPlayer::stopBackgroundMusic();
        AudioPlayer::setBackgroundMusic(menuMusic);
    }

    //connect All Buttons
    //Connect menu buttons
    QObject::connect(menu->startButton, &QPushButton::clicked, this, &View::startButton_clicked);
    QObject::connect(menu->settingsButton, &QPushButton::clicked, this, &View::settingsButton_clicked);
    QObject::connect(menu->exitButton, &QPushButton::clicked, this, &View::exitButton_clicked);
    QObject::connect(settings->toMenuButton, &QPushButton::clicked, this, &View::backButton_clicked);

    //connect settings buttons
    QObject::connect(settings->resBox, QComboBox::currentTextChanged, this, &View::setResolution);
    QObject::connect(settings->volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(changeVolume(int)));
    QObject::connect(settings->effectsVolumeSlider, SIGNAL(valueChanged(int)), this, SLOT(changeEffectsVolume(int)));
}


void View::startButton_clicked()
{
    if (game)
    {
        AudioPlayer::activateSoundEffect(buttonSoundPath);
        changeScene(game);
        game->setGameState(EGameState::InGame);
        AudioPlayer::setBackgroundMusic(inGameMusic);
        game->restartTimers();
        QPixmap background = QPixmap(":/image/images/Wallpaper/GameSceneBackground_4.jpg");
        this->setBackgroundBrush(QBrush(background));
    }
}

void View::settingsButton_clicked()
{
    if (settings)
    {
        changeScene(settings);
        AudioPlayer::activateSoundEffect(buttonSoundPath);
    }
}

void View::setResolution(const QString &text)
{

    if (text == "800x600" )
    {
        screenWidth = 800;
        screenHeight = 600;
        setSceneRect(0, 0, screenWidth, screenHeight);
        setFixedSize(screenWidth, screenHeight);
        menu->setSceneRect(0, 0, screenWidth, screenHeight);
        game->setSceneRect(0, 0, screenWidth, screenHeight);
        game->gameCanvasWidth = 790; // width = screenWidth * 0.975
        game->gameCanvasHeight = 550; // height = screenHeight * 0.91
        game->gameCanvas->setRect(5, 50, game->gameCanvasWidth, game->gameCanvasHeight); // x = CanvasWidth * 0.007, y = CanvasHeight * 0.08
        settings->setSceneRect(0, 0, screenWidth, screenHeight);
        return;
    }
    else if (text == "1280x720")
    {
        screenWidth = 1280;
        screenHeight = 720;
        setSceneRect(0, 0, screenWidth, screenHeight);
        setFixedSize(screenWidth, screenHeight);
        menu->setSceneRect(0, 0, screenWidth, screenHeight);
        game->setSceneRect(0, 0, screenWidth, screenHeight);
        game->gameCanvasWidth = 1250; // width = screenWidth * 0.975
        game->gameCanvasHeight = 655; // height = screenHeight * 0.91
        game->gameCanvas->setRect(9, 58, game->gameCanvasWidth, game->gameCanvasHeight); // x = CanvasWidth * 0.007, y = CanvasHeight * 0.08
        settings->setSceneRect(0, 0, screenWidth, screenHeight);
        return;
    }

    else if (text == "1600x900")
    {
        screenHeight = 1600;
        screenHeight = 900;
        setSceneRect(0, 0, screenWidth, screenHeight);
        setFixedSize(screenWidth, screenHeight);
        menu->setSceneRect(0, 0, screenWidth, screenHeight);
        game->setSceneRect(0, 0, screenWidth, screenHeight);
        game->gameCanvasWidth = 1560; // width = screenWidth * 0.975
        game->gameCanvasHeight = 820; // height = screenHeight * 0.91
        game->gameCanvas->setRect(12, 72, game->gameCanvasWidth, game->gameCanvasHeight); // x = CanvasWidth * 0.007, y = CanvasHeight * 0.08
        settings->setSceneRect(0, 0, screenWidth, screenHeight);
        return;
    }
    else if (text == "1920x1080")
    {
        screenWidth = 1920;
        screenHeight = 1080;
        setSceneRect(0, 0, screenWidth, screenHeight);
        setFixedSize(screenWidth, screenHeight);
        menu->setSceneRect(0, 0, screenWidth, screenHeight);
        game->setSceneRect(0, 0, screenWidth, screenHeight);
        game->gameCanvasWidth = 1870;  // width = screenWidth * 0.975
        game->gameCanvasHeight = 980;   // height = screenHeight * 0.91
        game->gameCanvas->setRect(13, 78, game->gameCanvasWidth, game->gameCanvasHeight); // x = CanvasWidth * 0.007, y = CanvasHeight * 0.08
        settings->setSceneRect(0, 0, screenWidth, screenHeight);
        return;
    }

}

void View::changeVolume(int value)
{
    settings->musicValue->setText(QString::number(settings->volumeSlider->value()));
    AudioPlayer::changeMusicVolume(value);

}

void View::changeEffectsVolume(int value)
{
    settings->soundEffectsValue->setText(QString::number(settings->effectsVolumeSlider->value()));
    AudioPlayer::changeEffectsVolume(value);
}

void View::exitButton_clicked()
{
    AudioPlayer::activateSoundEffect(buttonSoundPath);
    QApplication::instance()->quit();
}

void View::backButton_clicked()
{
    if (menu)
    {
        AudioPlayer::activateSoundEffect(buttonSoundPath);
        changeScene(menu);
        setBackgroundBrush(QBrush(menuWindow));
    }
}


void View::keyPressEvent(QKeyEvent *event)
{
    game->keyPressEvent(event);

    int key = event->key();
    if ((key == Qt::Key_Escape) && game->getGameState() == EGameState::InGame)
    {
        game->setGameState(EGameState::InMenu);
        pauseGame();
    }

}

void View::changeScene(QGraphicsScene* currScene)
{
    setScene(currScene);
}

void View::pauseGame()
{
    if (game->getGameState() == EGameState::InMenu)
    {
        changeScene(menu);
        setBackgroundBrush(menuWindow);
        game->stopTimers();
        AudioPlayer::stopBackgroundMusic();
        AudioPlayer::setBackgroundMusic(menuMusic);
    }
}

