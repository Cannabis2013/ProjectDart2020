#ifndef DARTSTURNS_H
#define DARTSTURNS_H

#include "src/DartsController/controller/idartsturns.h"

class IDartsStatus;
class IDartsInputTrimmer;
class IDartsInputs;
class IDartsPlayers;
class IDartsScores;
class IDartsIndexes;

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
