#ifndef DARTPLAYERS_H
#define DARTPLAYERS_H

#include "idartsplayers.h"
#include "src/DartsController/players/models/dartsplayer.h"
#include <qstringlist.h>

class DartsPlayers : public IDartsPlayers
{
public:
        DartsPlayers(const QString& filepath);
        void init() override;
        void initFromFile() override;
        void reset() override;
        QList<DartsPlayer>& all() override;
        bool saveState() override;

private:
        QList<DartsPlayer> _players;
        const QString _storagePath;
};

#endif // DARTPLAYERS_H
