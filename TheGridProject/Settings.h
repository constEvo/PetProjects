#ifndef SETTINGS_H
#define SETTINGS_H

#include <QGraphicsScene>


class QPushButton;
class QSlider;
class QComboBox;
class QLabel;
class GridFonts;

class Settings : public QGraphicsScene
{
    Q_OBJECT
public:
    Settings();


    void addResolutionBox();

    void addMusicSlider();

    void addSoundEffectsSlider();


    QGraphicsTextItem* resolution;
    QGraphicsTextItem* musicVolume;
    QPushButton* toMenuButton;

    QComboBox* resBox;

    //music sound
    QGraphicsTextItem* music;
    QSlider* volumeSlider;
    QLabel* musicValue;

    //sound effects
    QGraphicsTextItem* soundEffects;
    QSlider* effectsVolumeSlider;
    QLabel* soundEffectsValue;


private:
    QGraphicsProxyWidget* toMenuProxy;
    QGraphicsProxyWidget*  resProxy;
    QGraphicsProxyWidget* volumeProxy;
    QGraphicsProxyWidget* musicValueProxy;
    QGraphicsProxyWidget* effectsVolumeProxy;
    QGraphicsProxyWidget* soundEffectsValueProxy;

    //Font
    GridFonts* font;
};

#endif // SETTINGS_H
