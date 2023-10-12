#ifndef DARTPLAYERS_H
#define DARTPLAYERS_H

#include "IDartsPlayers.h"
#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/players/playersio.h"

#include <qstringlist.h>

class DartsPlayers : public IDartsPlayers
{
public:
        DartsPlayers(IDartsIndexes *indexes);

        void initPlayers(const QStringList& names) override;
        void initPlayers() override;
        QString name(int index) const override;
        QString name() const override;
        int playersCount() const override;
        QStringList  names() const override;
        bool saveState() override;
        int indexOf(const QString& name) const override;

private:
        QStringList _names;

        // Helpers
        PlayersIO *_playersIO;

        // Services
        IDartsIndexes *_indexes;
};

#endif // DARTPLAYERS_H
