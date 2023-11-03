#include "soundcontroller.h"
#include <QAudioOutput>

SoundController::SoundController(QObject* parent)
    : QObject { parent }
{
        _player = new QMediaPlayer();
        _player->setAudioOutput(new QAudioOutput());
        _player->audioOutput()->setVolume(50);
}

void SoundController::introSong()
{
}

void SoundController::keyPress()
{
}

void SoundController::stop()
{
        _player->stop();
}

bool SoundController::isPlaying()
{
        return _player->isPlaying();
}
