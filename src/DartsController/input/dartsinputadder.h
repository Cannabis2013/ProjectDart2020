#ifndef DARTSINPUTADDER_H
#define DARTSINPUTADDER_H

#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/input/idartsinputadder.h"
#include "src/DartsController/status/idartsstatus.h"
#include "src/DartsController/validation/idartsevaluator.h"

class DartsInputAdder : public IDartsInputAdder {
public:
        DartsInputAdder(IDartsInputs* inputs, IDartsEvaluator** evaluator,
            IDartsIndexes* indexes, IDartsStatus* status);

        void add(const QString& mod, const int& point);

private:
        void trimInputs();
        void nullifyTurn();

        bool persistInput(const Input& input);

        // Services
        IDartsInputs* const _inputs;
        IDartsEvaluator** const _evaluator;
        IDartsIndexes* const _indexes;
        IDartsStatus* const _status;
};

#endif // DARTSINPUTADDER_H
