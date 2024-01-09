#ifndef DARTSINPUTADDER_H
#define DARTSINPUTADDER_H

#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/input/idartsinputadder.h"
#include "src/DartsController/input/idartsinputtrimmer.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/status/idartsstatus.h"
#include "src/DartsController/validation/abstractdartsevaluator.h"

class DartsInputAdder : public IDartsInputAdder {
public:
        DartsInputAdder(IDartsInputs* inputs, IDartsInputTrimmer* trimmer,
            IDartsIndexes* indexes, IDartsStatus* status, IDartsScores* scores);

        void add(const QString& mod, const int& point) override;
        void setEvaluator(AbstractDartsEvaluator** evaluatorRef) override;

private:
        // Private member methods
        void evaluateAndPersist(const QString& mod, const int& point);

        // Services
        IDartsInputs* const _inputs;
        IDartsInputTrimmer* const _trimmer;
        IDartsIndexes* const _indexes;
        AbstractDartsEvaluator** _evaluator;
        IDartsStatus* const _status;
        IDartsScores* const _scores;
};

#endif // DARTSINPUTADDER_H
