#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QUrl>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPixmap>
#include <QTimer>

class Projectile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    QPixmap projectile;

    Projectile(int projectileSize, const QString& projectileImagePath)
    {
        projectile = QPixmap(projectileImagePath).scaled(projectileSize, projectileSize, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
    }

    virtual ~Projectile()
    {
        if (moveTimer)
        {
            moveTimer->stop();
            delete moveTimer;
            moveTimer = nullptr;
        }
    }

    virtual void spawnProjectile(int posX, int posY) = 0;

    virtual void playShotSound() = 0;


protected:

    QString shotSoundPath;



    QTimer* moveTimer;
};

#endif // PROJECTILE_H
