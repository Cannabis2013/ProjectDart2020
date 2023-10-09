#ifndef DARTINPUTS_H
#define DARTINPUTS_H

#include "IDartsInputs.h"
#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/IDartsInputEvalutor.h"
#include "src/DartsController/input/inputsio.h"
#include "src/DartsController/players/IDartsPlayers.h"

#include <QList>

class DartsInputs : public IDartsInputs
{
public:
        DartsInputs(IDartsIndexes* indexes, IDartsPlayers* players, IDartsInputEvaluator* evaluator);
        virtual void init() override;
        void initFromFile() override;
        Input evaluateAndAdd(const InputRequest& req) override;
        QList<Input> inputs(const QString& playerName) const override;
        bool saveState() override;
        void chop() override;

private:
        Input save(Input input);

        QList<Input> _inputs;

        // Services
        IDartsInputEvaluator* _evaluator;
        IDartsIndexes* _indexes;
        IDartsPlayers* _players;
        InputsIO* _inputsIO;
};

#endif // DARTINPUTS_H
