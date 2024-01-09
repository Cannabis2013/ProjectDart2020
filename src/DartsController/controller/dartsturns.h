#ifndef DARTSTURNS_H
#define DARTSTURNS_H

#include "src/DartsController/controller/idartsturns.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/status/idartsstatus.h"
#include "src/DartsController/validation/idartsevaluator.h"
#include "src/DartsController/validation/iplayerallowances.h"
#include <src/DartsController/scores/idartsscores.h>

class DartsTurns : public IDartsTurns {
public:
        DartsTurns(IDartsStatus* status,
            IDartsIndexes* indexes,
            IDartsScores* scores,
            IDartsPlayers* players,
            IPlayerAllowances* allowances,
            IDartsInputs* inputs);

        void init(IDartsEvaluator* evaluator) override;
        void undo() override;
        void redo() override;

private:
        void updateAllowance(const QString& name);
        void undoTurn();
        void redoTurn();

        // Services
        IDartsStatus* const _status;
        IDartsIndexes* const _indexes;
        IDartsScores* const _scores;
        IDartsEvaluator* _evaluator;
        IDartsPlayers* const _players;
        IPlayerAllowances* const _allowances;
        IDartsInputs* const _inputs;
};

#endif // DARTSTURNS_H
