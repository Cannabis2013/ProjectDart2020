#ifndef DARTPLAYERS_H
#define DARTPLAYERS_H

#include "idartsplayers.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/players/dartsplayer.h"
#include "src/DartsController/players/playersio.h"

#include <qstringlist.h>

class DartsPlayers : public IDartsPlayers
{
public:
        DartsPlayers(IDartsIndexes *indexes);
        void init() override;
        void initFromFile() override;
        void reset() override;
        DartsPlayer winner() const override;
        int playersCount() const override;
        const QStringList names() const override;
        bool saveState() override;
        DartsPlayer& player(const int& index) override;
        DartsPlayer& player(const QString& name) override;
        DartsPlayer& player() override;

private:
        QList<DartsPlayer> _players;

        // Helpers
        PlayersIO* _playersIO;

        // Services
        IDartsIndexes* _indexes;
};

#endif // DARTPLAYERS_H
