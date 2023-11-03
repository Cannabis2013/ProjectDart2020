#ifndef DARTPLAYERS_H
#define DARTPLAYERS_H

#include "idartsplayers.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/players/DartsPlayer.h"
#include "src/DartsController/players/playersio.h"

#include <qstringlist.h>

class DartsPlayers : public IDartsPlayers
{
public:
        DartsPlayers(IDartsIndexes *indexes);

        void init(const QStringList& names) override;
        void initFromFile() override;
        virtual void reset() override;
        QString name(int index) const override;
        QString name() const override;
        virtual QString winnerName() const override;
        int playersCount() const override;
        const QStringList names() const override;
        bool saveState() override;
        int indexOf(const QString& name) const override;
        void declareAsWinner(const QString& name) override;

private:
        QList<DartsPlayer> _players;

        // Helpers
        PlayersIO* _playersIO;

        // Services
        IDartsIndexes* _indexes;
};

#endif // DARTPLAYERS_H
