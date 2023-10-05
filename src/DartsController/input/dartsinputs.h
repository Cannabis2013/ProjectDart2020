#ifndef DARTINPUTS_H
#define DARTINPUTS_H

#include "IDartInputs.h"
#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/DartsInternalInput.h"
#include "src/DartsController/input/inputsio.h"
#include "src/DartsController/players/IDartPlayers.h"

class DartsInputs : public IDartInputs
{
public:
        DartsInputs(IDartsIndexes *indexes, IDartPlayers *players);
        virtual void init() override;
        virtual void clear() override;
        virtual bool save(DartsInternalInput input) override;
        virtual QList<DartsInput> inputs() override;
        virtual QList<DartsInput> inputs(const QString& playerName, const int& turnIndex) override;
private:

    QList<DartsInternalInput> _inputs;

        // Services
        IDartsIndexes *_indexes;
        IDartPlayers *_players;
        InputsIO *_inputsIO;
};

#endif // DARTINPUTS_H
