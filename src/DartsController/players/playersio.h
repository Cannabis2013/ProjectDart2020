#ifndef PLAYERSIO_H
#define PLAYERSIO_H

#include "src/DartsController/players/DartsPlayer.h"
#include <QStringList>

class PlayersIO
{
public:
        PlayersIO(const QString &filePath);

        QList<DartsPlayer> initFromFile();
        bool saveToFile(const QList<DartsPlayer>& players);

private:
        QString _filePath;
};

#endif // PLAYERSIO_H
