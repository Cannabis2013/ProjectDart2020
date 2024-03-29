#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

#include <QMediaPlayer>
#include <QObject>

class SoundController : public QObject
{
        Q_OBJECT
public:
        explicit SoundController(QObject* parent = nullptr);

        Q_INVOKABLE void introSong();
        Q_INVOKABLE void keyPress();
        Q_INVOKABLE void stop();
        Q_INVOKABLE bool isPlaying();

private:
        QMediaPlayer* _player;
};

#endif // SOUNDCONTROLLER_H
