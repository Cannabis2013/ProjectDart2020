#ifndef DARTPLAYERS_H
#define DARTPLAYERS_H

#include "idartsplayers.h"
#include "src/DartsController/players/models/dartsplayer.h"
#include <qstringlist.h>

class IPlayerGenerator;
class PlayersIO;
class ServiceCollection;

class DartsPlayers : public IDartsPlayers
{
public:
        DartsPlayers(ServiceCollection* services);
        void init() override;
        void initFromFile() override;
        void reset() override;
        int playersCount() const override;
        QList<DartsPlayer> all() const override;
        bool saveState() override;
        DartsPlayer winner() const override;
        DartsPlayer& one(const int& index) override;
        DartsPlayer& one(const QString& name) override;
        DartsPlayer& one() override;

private:
        QList<DartsPlayer> _players;

        // Helpers
        PlayersIO* _playersIO;

        // Services
        ServiceCollection* const _services;
        IPlayerGenerator* _generator;
};

#endif // DARTPLAYERS_H
