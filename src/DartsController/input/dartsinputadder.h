#ifndef DARTSINPUTADDER_H
#define DARTSINPUTADDER_H

#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/IDartsInputEvalutor.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/input/idartsinputadder.h"
#include "src/DartsController/scores/IDartsScores.h"

class DartsInputAdder : public IDartsInputAdder {
public:
        DartsInputAdder(IDartsInputs* inputs, IDartsInputEvaluator* evaluator, IDartsIndexes* indexes, IDartsScores* scores);

        void add(const QString& mod, const int& point);

private:
        void trimInputs();
        void nullifyTurn();

        bool addInput(const Input& input);

        // Services
        IDartsInputs* const _inputs;
        IDartsInputEvaluator* const _evaluator;
        IDartsIndexes* const _indexes;
        IDartsScores* const _scores;
};

#endif // DARTSINPUTADDER_H
