#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QMediaPlayer>
#include <QAudioOutput>

class AudioPlayer
{
public:

    static void initialize();

    static void cleanup();

    static void setBackgroundMusic(const QString& musicPath);

    static void stopBackgroundMusic();

    static void changeMusicVolume(int value);

    static void activateSoundEffect(const QString& soundPath);

    static void changeEffectsVolume(int value);

private:

    static QMediaPlayer* musicMediaPlayer;
    static QAudioOutput* musicAudioOutput;

    static QMediaPlayer* soundEffectsMediaPlayer;
    static QAudioOutput* soundEffectsAudioOutput;

    static float musicVolume;

    static float soundEffectsVolume;
};


#endif // AUDIOPLAYER_H
