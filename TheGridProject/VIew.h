#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class Menu;
class GameScene;
class Settings;
class QMediaPlayer;
class QAudioOutput;
class QUrl;


class View : public QGraphicsView
{
    Q_OBJECT
public:

    View();

    void changeScene(QGraphicsScene* currScene);
    void pauseGame();

private:

    Menu* menu;
    GameScene* game;
    Settings* settings;

    void keyPressEvent(QKeyEvent* event);


    QString inGameMusic = QString("qrc:/sounds/sound/Velocity.mp3");
    QString menuMusic = QString("qrc:/sounds/sound/Wave.mp3");

    QPixmap menuWindow;

    QString buttonSoundPath;

int screenWidth, screenHeight;

private slots:
    void startButton_clicked();
    void settingsButton_clicked();
    void exitButton_clicked();
    void backButton_clicked();

    void setResolution(const QString &text);
    void changeVolume(int value);
    void changeEffectsVolume(int value);

};

#endif // VIEW_H

