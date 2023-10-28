#include "soundcontroller.h"

#include <QAudioOutput>

SoundController::SoundController(QObject *parent)
    : QObject{parent}
{
        _player = new QMediaPlayer();
        _player->setAudioOutput(new QAudioOutput());
        _player->audioOutput()->setVolume(50);
}

void SoundController::playIntroSong()
{
        _player->setSource(QUrl("qrc:/sounds/Ressources/Sounds/imperialMarch.mp3"));
        _player->play();
}

void SoundController::stop()
{
        _player->stop();
}
