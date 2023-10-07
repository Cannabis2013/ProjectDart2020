#ifndef DARTINPUTS_H
#define DARTINPUTS_H

#include "IDartsInputs.h"
#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/inputsio.h"
#include "src/DartsController/players/IDartPlayers.h"

class DartsInputs : public IDartsInputs
{
public:
        DartsInputs(IDartsIndexes *indexes, IDartPlayers *players);
        virtual void init() override;
        virtual void clear() override;
        virtual bool save(Input input) override;
        virtual QList<Input> inputs(const QString& playerName, const int& turnIndex) override;
private:

        QList<Input> _inputs;

        // Services
        IDartsIndexes *_indexes;
        IDartPlayers *_players;
        InputsIO *_inputsIO;
};

#endif // DARTINPUTS_H
