#ifndef DARTSINPUTADDER_H
#define DARTSINPUTADDER_H

#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/IDartsInputEvalutor.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/input/InputRequest.h"
#include "src/DartsController/scores/IDartsScores.h"

class DartsInputAdder {
public:
        DartsInputAdder(IDartsInputs* inputs, IDartsInputEvaluator* evaluator, IDartsIndexes* indexes, IDartsScores* scores);

        void add(const InputRequest& req);

private:
        void chopInputs();
        void nullifyTurn();

        bool addInput(const Input& input);

        // Services
        IDartsInputs* const _inputs;
        IDartsInputEvaluator* const _evaluator;
        IDartsIndexes* const _indexes;
        IDartsScores* const _scores;
};

#endif // DARTSINPUTADDER_H
