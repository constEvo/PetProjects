#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QObject>
#include "EStates.h"

class Cycle;
class EnemyTank;
class Score;
class Shield;
class Heart;
class BurstWeapon;
class QPushButton;
class HUD;
class GameCharacter;
class Apple;
class GridFonts;
class Character;
class QMediaPlayer;
class QAudioOutput;
class QUrl;


class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene();

    void keyPressEvent(QKeyEvent *event);

    void setGameState(EGameState newGameState);
    EGameState getGameState();

    QGraphicsRectItem *getGameCanvas();
    void setupGameCanvas();

    Score *getScore();

    //game over functions
    void gameOver();
    void addGameOverTitle();
    void addResetButton();
    void playGameOverSound();
    void stopTimers();

    //reet functions
    void reset();
    void clearHUD();
    void clearScene();
    void setupGameScene();
    void restartTimers();
    template<typename T>
    void clearItems(std::vector<T*>& items);
    template<typename T>
    void clearEnemies(std::vector<T*>& enemy, int &enemyCount);

    void checkCollision();



    std::vector<Cycle*> getActiveCycles();

    QGraphicsRectItem* gameCanvas;
    int gameCanvasWidth;
    int gameCanvasHeight;

    int cycleCount;
    int tankCount;

    //vectors with active items on GameScene
    std::vector<Cycle*> activeCycles;
    std::vector<EnemyTank*> activeTanks;
    std::vector<Shield*> activeShields;
    std::vector<Heart*> activeHearts;
    std::vector<BurstWeapon*> activeBurstWeapon;


    static const int GAME_WIDTH = 800;
    static const int GAME_HEIGHT = 600;

    //QTimers
    QTimer* playerMovement_timer;
    QTimer* spawnEnemy_timer;
    QTimer* gameLoop_timer;
    QTimer* spawnItems_timer;
    QTimer* moveCycle_timer;
    QTimer* moveTank_timer;

private:

    //Scene items
    QPixmap background;
    GridFonts* font;
    HUD* hud;
    GameCharacter* player;
    Apple* apple;
    Score* score;
    QString inGameMusic;

    //GameOver Components
    QString gameOverString;
    QGraphicsTextItem* gameOverText;
    //Buttons
    QPushButton* resetButton;
    QGraphicsProxyWidget* resProxy;

    QPushButton* backToMenuButton;
    QGraphicsProxyWidget* backToMenuProxy;
    //Game Over Media player components
    QString gameOverPath;

    QString buttonSoundPath;


    EGameState gameStatus;

    bool pauseInput;
    bool inGame;


private slots:
    //input func
    void move();
    void spawnEnemy();
    void spawnItems();
    void gameLoop();
    void resetButton_clicked();

};
#endif // GAMESCENE_H
