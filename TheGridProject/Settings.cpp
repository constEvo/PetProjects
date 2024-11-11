#include "Settings.h"
#include <QGraphicsTextItem>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <Fonts.h>

Settings::Settings()
{
    setSceneRect(0, 0, 800, 600);

    //create font
    font = new GridFonts();

    //Add Snake's Label
    QGraphicsTextItem* label = new QGraphicsTextItem();
    label->setPlainText("The Grid");
    label->setDefaultTextColor(Qt::white);
    label->setFont(font->getTitleFont());
    label->setPos(330, 70);
    addItem(label);

    addResolutionBox();

    addMusicSlider();

    addSoundEffectsSlider();

    //Add Back To Menu Button
    toMenuButton = new QPushButton();
    toMenuButton->setVisible(true);
    toMenuButton->setText("Back");
    toMenuButton->setFont(font->getHUDFont());
    toMenuButton->setStyleSheet("QPushButton { "
                                "border-image : url(:/image/images/Menu/Button.png) stretch ;"
                                "color : white; }");
    toMenuButton->setGeometry(370, 450, 100, 50);
    toMenuProxy = addWidget(toMenuButton);


    //Add Setting's Canvas
    QGraphicsRectItem* canvas = new QGraphicsRectItem(150, 50, 500, 500);
    QBrush brush(QColor(255, 255, 255, 255 * 0.2));
    canvas->setBrush(brush);
    canvas->setPen(Qt::SolidLine);
    addItem(canvas);

}

void Settings::addResolutionBox()
{
    //Video Resolution Text
    resolution = new QGraphicsTextItem();
    resolution->setPlainText("Video Resolution");
    resolution->setFont(font->getHUDFont());
    resolution->setDefaultTextColor(Qt::white);
    resolution->setTextWidth(200);
    resolution->setPos(200, 140);
    addItem(resolution);

    //Video Resolution changing box
    resBox = new QComboBox();
    resBox->setFont(font->getHUDFont());
    resBox->setStyleSheet("QComboBox { color : darkCyan; }");
    resBox->addItem("800x600");
    resBox->addItem("1280x720");
    resBox->addItem("1600x900");
    resBox->addItem("1920x1080");
    resBox->setAttribute(Qt::WA_TranslucentBackground);
    resBox->setGeometry(380, 150, 150, 50);
    resProxy = addWidget(resBox);
}

void Settings::addMusicSlider()
{
    //Music text
    music = new QGraphicsTextItem();
    music->setPlainText("Music");
    music->setFont(font->getHUDFont());
    music->setDefaultTextColor(Qt::white);
    music->setTextWidth(100);
    music->setPos(200, 250);
    addItem(music);

    //Add Music Volume Slider
    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(10);
    volumeSlider->move(380, 260);
    volumeSlider->setStyleSheet("QSlider::handle:horizontal { background-color : darkCyan; }");
    volumeProxy = addWidget(volumeSlider);

    //Add Music volume Value
    musicValue = new QLabel();
    musicValue->setFont(font->getHUDFont());
    musicValue->setGeometry(600, 260, 40, 20);
    musicValueProxy = new QGraphicsProxyWidget();
    musicValueProxy = addWidget((musicValue));
    musicValue->setStyleSheet("QLabel { color : white; }");
    musicValue->setAttribute(Qt::WA_TranslucentBackground);
    musicValue->setText(QString::number(volumeSlider->value()));
}

void Settings::addSoundEffectsSlider()
{
    //Sound Effects text
    soundEffects = new QGraphicsTextItem();
    soundEffects->setPlainText("Sound Effects");
    soundEffects->setFont(font->getHUDFont());
    soundEffects->setDefaultTextColor(Qt::white);
    soundEffects->setTextWidth(100);
    soundEffects->setPos(200, 300);
    addItem(soundEffects);


    //Add Sound Effects Volume Slider
    effectsVolumeSlider = new QSlider(Qt::Horizontal);
    effectsVolumeSlider->setRange(0, 100);
    effectsVolumeSlider->setValue(10);
    effectsVolumeSlider->move(380, 310);
    effectsVolumeSlider->setStyleSheet("QSlider::handle::horizontal { background-color: darkCyan; }");
    effectsVolumeProxy = addWidget(effectsVolumeSlider);

    //Add Sound Effects value
    soundEffectsValue = new QLabel();
    soundEffectsValue->setFont(font->getHUDFont());
    soundEffectsValue->setGeometry(600, 310, 40, 20);
    soundEffectsValue->setStyleSheet("QLabel { color : white; }");
    soundEffectsValue->setAttribute(Qt::WA_TranslucentBackground);
    soundEffectsValue->setText(QString::number(effectsVolumeSlider->value()));
    soundEffectsValueProxy = addWidget(soundEffectsValue);
}




