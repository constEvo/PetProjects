#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QAudioOutput>


class Character : public QObject
{
    Q_OBJECT
public:
    Character(int size, const QString &meshImagePath) :
            size(size)
    {
        meshPng = QPixmap(meshImagePath).scaled(size , size , Qt::AspectRatioMode::KeepAspectRatio, Qt::SmoothTransformation);;
    }

    virtual ~Character() {}

    virtual QGraphicsPixmapItem* getMesh()
    {
        return characterMesh;
    }

    QGraphicsPixmapItem* characterMesh;

protected:
    virtual void initCharacter(int startX, int startY) = 0;

    int size;

    QPixmap meshPng;


};

#endif // CHARACTER_H

