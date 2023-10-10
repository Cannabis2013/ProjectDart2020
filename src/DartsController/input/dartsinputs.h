#ifndef DARTINPUTS_H
#define DARTINPUTS_H

#include "IDartsInputs.h"
#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/inputsio.h"
#include "src/DartsController/players/IDartsPlayers.h"

#include <QList>

class DartsInputs : public IDartsInputs
{
public:
        DartsInputs(IDartsIndexes* indexes, IDartsPlayers* players);
        virtual void init() override;
        virtual void setInputs(const QList<Input>& inputs) override;
        void initFromFile() override;
        const QList<Input>& inputs() const override;
        QList<Input> inputs(const QString& playerName, const int& throwIndex) const override;
        bool saveState() override;
        Input save(Input input) override;

private:
        QList<Input> _inputs;

        // Services
        IDartsIndexes* _indexes;
        IDartsPlayers* _players;
        InputsIO* _inputsIO;
};

#endif // DARTINPUTS_H
