#ifndef DARTSINPUTADDER_H
#define DARTSINPUTADDER_H

#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/input/idartsinputadder.h"
#include "src/DartsController/input/idartsinputtrimmer.h"
#include "src/DartsController/status/idartsstatus.h"
#include "src/DartsController/validation/idartsevaluator.h"

class DartsInputAdder : public IDartsInputAdder {
public:
        DartsInputAdder(IDartsInputs* inputs, IDartsInputTrimmer* trimmer,
            IDartsIndexes* indexes, IDartsStatus* status);

        void add(const QString& mod, const int& point) override;
        void setEvaluator(IDartsEvaluator** evaluatorRef) override;

private:
        bool persistInput(const Input& input);

        // Services
        IDartsInputs* const _inputs;
        IDartsInputTrimmer* const _trimmer;
        IDartsIndexes* const _indexes;
        IDartsEvaluator** _evaluator;
        IDartsStatus* const _status;
};

#endif // DARTSINPUTADDER_H
