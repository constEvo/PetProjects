#include "AudioPlayer.h"

QMediaPlayer* AudioPlayer::musicMediaPlayer = nullptr;
QAudioOutput* AudioPlayer::musicAudioOutput = nullptr;

QMediaPlayer* AudioPlayer::soundEffectsMediaPlayer = nullptr;
QAudioOutput* AudioPlayer::soundEffectsAudioOutput = nullptr;

float AudioPlayer::musicVolume = 0.1f;
float AudioPlayer::soundEffectsVolume = 0.1f;

void AudioPlayer::initialize()
{
    if (!musicMediaPlayer && !musicAudioOutput)
    {
        musicMediaPlayer = new QMediaPlayer();
        musicAudioOutput = new QAudioOutput();
        musicMediaPlayer->setAudioOutput(musicAudioOutput);

    }

    if (!soundEffectsMediaPlayer && !soundEffectsAudioOutput)
    {
        soundEffectsMediaPlayer = new QMediaPlayer();
        soundEffectsAudioOutput = new QAudioOutput();
        soundEffectsMediaPlayer->setAudioOutput(soundEffectsAudioOutput);
    }
}

void AudioPlayer::cleanup()
{
    delete musicMediaPlayer;
    delete musicAudioOutput;

    delete soundEffectsMediaPlayer;
    delete soundEffectsAudioOutput;

    musicMediaPlayer = nullptr;
    musicAudioOutput = nullptr;
    soundEffectsMediaPlayer = nullptr;
    soundEffectsAudioOutput = nullptr;
}

void AudioPlayer::setBackgroundMusic(const QString &musicPath)
{
    if (!musicMediaPlayer || !musicAudioOutput) return;

    QUrl musicFile = QUrl(musicPath);
    if (!musicFile.isEmpty())
    {
        musicMediaPlayer->setSource(musicFile);
        musicMediaPlayer->setLoops(QMediaPlayer::Infinite);
        musicAudioOutput->setVolume(musicVolume);
        musicMediaPlayer->play();
    }
}

void AudioPlayer::stopBackgroundMusic()
{
    musicMediaPlayer->stop();
}

void AudioPlayer::changeMusicVolume(int value)
{
    musicVolume = static_cast<float>(value) / 100.0f;

    if (musicAudioOutput)
    {
        musicAudioOutput->setVolume(musicVolume);
    }

}

void AudioPlayer::activateSoundEffect(const QString &soundPath)
{
    if (!soundEffectsMediaPlayer || !soundEffectsAudioOutput) return;

    QUrl soundFile = QUrl(soundPath);
    if (!soundFile.isEmpty())
    {
        soundEffectsMediaPlayer->setSource(soundFile);
        soundEffectsAudioOutput->setVolume(soundEffectsVolume);
        soundEffectsMediaPlayer->play();
    }
}

void AudioPlayer::changeEffectsVolume(int value)
{
    soundEffectsVolume = static_cast<float>(value) / 100.0f;
    if (soundEffectsAudioOutput)
    {
        soundEffectsAudioOutput->setVolume(soundEffectsVolume);
    }
}

