#include "GameScene.h"
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include "QTimer"
#include <QBrush>
#include <QColor>
#include <QGraphicsRectItem>
#include "GameCharacter.h"
#include "Score.h"
#include "Apple.h"
#include "HUD.h"
#include "EnemyTank.h"
#include "Cycle.h"
#include "Shield.h"
#include "Heart.h"
#include "BurstWeapon.h"
#include <Fonts.h>
#include <QUrl>
#include "AudioPlayer.h"



GameScene::GameScene()
{
    setSceneRect(0, 0, GAME_WIDTH, GAME_HEIGHT);

    gameStatus = EGameState::InGame;

    //Setup background image
    background = QPixmap(":/image/images/Wallpaper/GameSceneBackground_4.jpg").scaled(GAME_WIDTH, GAME_HEIGHT, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
    setBackgroundBrush(QBrush(background));

    setupGameCanvas();

    font = new GridFonts();


    player = new GameCharacter(this, 80);

    score = new Score();
    addItem(score);

    apple = new Apple(30, this, player, score);

    apple->spawnItem();

    cycleCount = 0;

    tankCount = 0;

    hud = new HUD(this, player);

    inGameMusic = QString("qrc:/sounds/sound/Velocity.mp3");

    gameOverPath = QString("qrc:/sounds/sound/GameOver.wav");

    buttonSoundPath = QString("qrc:/sounds/sound/ButtonBloop.mp3");

    //Connect slots
    playerMovement_timer = new QTimer();
    QObject::connect(playerMovement_timer, SIGNAL(timeout()), this, SLOT(move()));

    spawnEnemy_timer = new QTimer();
    QObject::connect(spawnEnemy_timer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));

    gameLoop_timer = new QTimer();
    QObject::connect(gameLoop_timer, SIGNAL(timeout()), this, SLOT(gameLoop()));

    spawnItems_timer = new QTimer();
    QObject::connect(spawnItems_timer, SIGNAL(timeout()), this, SLOT(spawnItems()));

    //launch timers for enemies
    moveCycle_timer = new QTimer();

    moveTank_timer = new QTimer();

    shootTank_timer = new QTimer();
}

void GameScene::keyPressEvent(QKeyEvent *event)
{

    player->keyPressEvent(event);
}


void GameScene::gameLoop()
{
    if (getGameState() == EGameState::InGame)
    {
        checkCollision();
    }

    if (getGameState() == EGameState::GameOver)
    {
        gameOver();
    }

    if (hud)
    {
        hud->initHUD();
    }
}

void GameScene::checkCollision()
{
    player->checkCollision();
}


void GameScene::setGameState(EGameState newGameState)
{
    gameStatus = newGameState;
}

EGameState GameScene::getGameState()
{
    return gameStatus;
}

void GameScene::gameOver()
{
    addGameOverTitle();

    addResetButton();

    stopTimers();

    playGameOverSound();
}

void GameScene::addGameOverTitle()
{
    //Game Over text pop's up
    gameOverString = QString("Game Over");
    gameOverText = new QGraphicsTextItem();
    gameOverText->setPlainText(gameOverString);
    gameOverText->setFont(font->getTitleFont());
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setPos(300, 200);
    addItem(gameOverText);
}

void GameScene::addResetButton()
{
    //Add reset button to the scene
    resetButton = new QPushButton("Return to a Grid?");
    resetButton->setVisible(true);
    resetButton->setFont(font->getHUDFont());
    resetButton->setStyleSheet("QPushButton {"
                               "border-image : url(:/image/images/Menu/Button.png) stretch;"
                               "color : white;"
                               "padding-bottom : 10px; }");
    resetButton->resize(250, 50);
    resetButton->move(280, 250);
    resProxy = addWidget(resetButton);
    QObject::connect(resetButton, SIGNAL(clicked(bool)), this, SLOT(resetButton_clicked()));
}

void GameScene::playGameOverSound()
{
    AudioPlayer::stopBackgroundMusic();
    AudioPlayer::activateSoundEffect(gameOverPath);
}

void GameScene::stopTimers()
{
    //stop player movement timer
    if (playerMovement_timer && playerMovement_timer->isActive())
    {
        playerMovement_timer->stop();
    }
    //stop gameloop timer
    if (gameLoop_timer && gameLoop_timer->isActive())
    {
        gameLoop_timer->stop();
    }
    //stop enemy spawn timer
    if (spawnEnemy_timer && spawnEnemy_timer->isActive())
    {
       spawnEnemy_timer->stop();
    }
    //stop item's spawn timer
    if (spawnItems_timer && spawnItems_timer->isActive())
    {
        spawnItems_timer->stop();
    }
    //stop cycle movement's timer
    if (moveCycle_timer && moveCycle_timer->isActive())
    {
        moveCycle_timer->stop();
    }
    //stop tank movement's timer
    if (moveTank_timer && moveTank_timer->isActive())
    {
        moveTank_timer->stop();
    }
    //stop tank's shooting timer
    if (shootTank_timer && shootTank_timer->isActive())
    {
        shootTank_timer->stop();
    }
}

void GameScene::resetButton_clicked()
{
    AudioPlayer::activateSoundEffect(buttonSoundPath);
    reset();
}

void GameScene::reset()
{
    clearHUD();

    clearScene();

    setupGameScene();

    AudioPlayer::setBackgroundMusic(inGameMusic);
}

void GameScene::clearHUD()
{
    //Delete the Game Over Text from the Scene
    if (gameOverText && gameOverText->isActive())
    {
        removeItem(gameOverText);
        gameOverText = nullptr;
    }

    //Delete Reset Button from the Scene
    if (resProxy)
    {
        removeItem(resProxy);
        resProxy = nullptr;
    }

    //Reset Score
    if (score)
    {
        score->resetScore();
    }
}

void GameScene::clearScene()
{
    //Delete the Snake from the Scene
    if (player)
    {
        player->deleteCharacter();
    }

    //Remove apple from the scene
    if (apple)
    {
        removeItem(apple->getApple());
        delete apple->getApple();
    }


    //remove tanks from the scene
    clearEnemies(activeTanks, tankCount);

    //remove cycles from the scene
    clearEnemies(activeCycles, cycleCount);

    //remove shield from the scene
    clearItems(activeShields);

    //remove hearts from the scene
    clearItems(activeHearts);

    //remove burstWeapon from the scene
    clearItems(activeBurstWeapon);


}

template<typename T>
void GameScene::clearItems(std::vector<T*> &items)
{
    if (items.empty()) return;

    for (auto i = 0; i <= items.size(); i++ )
    {
        T* item = items[i];
        if (item != nullptr)
        {
            item->overlap_timer->stop();
            items.erase(items.begin() + i);
            delete item;
        }
    }
}

template<typename T>
void GameScene::clearEnemies(std::vector<T *> &enemy, int &enemyCount)
{
    if (enemy.empty()) return;

    for (auto i = 0 ; i <= enemy.size(); i++)
    {
        T* enemyInstance = enemy[i];

        enemy.erase(enemy.begin() + i);
        --enemyCount;
        delete enemyInstance;
    }
}

void GameScene::setupGameScene()
{
    //set GameScene flags
    setGameState(EGameState::InGame);

    //Add Snake head
    if (player)
    {
        player->initCharacter(150, 150);
        player->setDefaultHealthValue();
        player->setShieldStatus(false);
        player->setWeaponState(EWeaponState::SingleShotWeapon);
        player->stopLocomotion();
    }

    //Add apple to the scene
    if (apple)
    {
        apple->spawnItem();
    }

    //Restart game, movement and spawn timers
    restartTimers();
}

void GameScene::restartTimers()
{
    //launch gameloop timer
    if (gameLoop_timer && !gameLoop_timer->isActive())
    {
        gameLoop_timer->start(100);

    }
    //launch player movement timer
    if (playerMovement_timer && !playerMovement_timer->isActive())
    {
        playerMovement_timer->start(100);
    }
    //launch enemy spawn timer
    if (spawnEnemy_timer && !spawnEnemy_timer->isActive())
    {
        spawnEnemy_timer->start(2000);
    }
    //launch item's spawn timer
    if (spawnItems_timer && !spawnItems_timer->isActive())
    {
        spawnItems_timer->start(20000);
    }
    //launch cycle's move timer
    if (moveCycle_timer && !moveCycle_timer->isActive())
    {
        moveCycle_timer->start(100);
    }
    //launch tank's move timer
    if (moveTank_timer && !moveTank_timer->isActive())
    {
        moveTank_timer->start(100);
    }
    //launch tank's shoot timer
    if (shootTank_timer && !shootTank_timer->isActive())
    {
        shootTank_timer->start(700);
    }
}


std::vector<Cycle*> GameScene::getActiveCycles()
{
    return activeCycles;
}

Score *GameScene::getScore()
{
    return score;
}

QGraphicsRectItem *GameScene::getGameCanvas()
{
    return gameCanvas;
}

void GameScene::setupGameCanvas()
{
    gameCanvasWidth = 790;
    gameCanvasHeight = 550;
    gameCanvas = new QGraphicsRectItem(5, 50, gameCanvasWidth, gameCanvasHeight);
    QBrush gameCanvasBrush(QColor(255, 255, 255, 0));
    gameCanvas->setBrush(gameCanvasBrush);

    QPen gameCanvasPen(QColor(255, 255, 255));
    gameCanvasPen.setWidth(5);
    gameCanvasPen.setStyle(Qt::SolidLine);
    gameCanvas->setPen(gameCanvasPen);
    addItem(gameCanvas);
}


void GameScene::move()
{
    player->move();
}


void GameScene::spawnEnemy()
{

    if (cycleCount <= 6)
    {
        Cycle* newCycle = new Cycle(70, player, this);
        if (newCycle)
        {
            activeCycles.push_back(newCycle);
            cycleCount++;
        }
    }


    if (getScore()->getScore() > 250 && tankCount < 1)
    {
        EnemyTank* newTank = new EnemyTank(95, player, this);
        if (newTank)
        {
            activeTanks.push_back(newTank);
            tankCount++;
        }
    }
}

void GameScene::spawnItems()
{
    if (player->health < player->MAX_HEALTH && activeHearts.empty())
    {
        Heart* heart = new Heart(30, this, player);
        if (heart)
        {
            heart->spawnItem();
            activeHearts.push_back(heart);
        }
    }

    if (player->getWeaponState() == EWeaponState::SingleShotWeapon && activeBurstWeapon.empty())
    {
        BurstWeapon* burstWeapon = new BurstWeapon(30, this, player);
        if (burstWeapon)
        {
            burstWeapon->spawnItem();
            activeBurstWeapon.push_back(burstWeapon);
        }
    }

    if (activeShields.empty())
    {
        Shield* shield = new Shield(30, this, player);
        if (shield)
        {
            shield->spawnItem();
            activeShields.push_back(shield);
        }
    }
}






