#ifndef PLAYERSIO_H
#define PLAYERSIO_H

#include "src/DartsController/players/models/dartsplayer.h"
#include <QStringList>

class PlayersIO
{
public:
        QList<DartsPlayer> initFromFile();
        bool saveToFile(const QList<DartsPlayer>& players);

private:
        const QString _filePath = "players.dat";
};

#endif // PLAYERSIO_H
