#ifndef DARTSTURNS_H
#define DARTSTURNS_H

#include "src/DartsController/controller/idartsturns.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/input/idartsinputtrimmer.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/status/idartsstatus.h"
#include "src/DartsController/validation/abstractdartsevaluator.h"
#include <src/DartsController/scores/idartsscores.h>

class DartsTurns : public IDartsTurns {
public:
        DartsTurns(IDartsStatus* status,
            IDartsIndexes* indexes,
            IDartsScores* scores,
            IDartsPlayers* players,
            IDartsInputs* inputs,
            IDartsInputTrimmer* trimmer);

        void init(AbstractDartsEvaluator* evaluator) override;
        void undo() override;
        void redo() override;
        void skip() override;

private:
        void undoTurn();
        void redoTurn();

        // Services
        IDartsStatus* const _status;
        IDartsIndexes* const _indexes;
        IDartsScores* const _scores;
        AbstractDartsEvaluator* _evaluator;
        IDartsPlayers* const _players;
        IDartsInputs* const _inputs;
        IDartsInputTrimmer* const _trimmer;
};

#endif // DARTSTURNS_H
