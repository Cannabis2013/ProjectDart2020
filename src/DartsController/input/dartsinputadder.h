#ifndef DARTSINPUTADDER_H
#define DARTSINPUTADDER_H

#include "idartsinputadder.h"

class Input;
class IDartsScores;
class IDartsStatus;
class IDartsIndexes;
class IDartsInputTrimmer;
class IDartsInputs;

class DartsInputAdder : public IDartsInputAdder {
public:
        DartsInputAdder(IDartsInputs* inputs, IDartsInputTrimmer* trimmer,
            IDartsIndexes* indexes, IDartsStatus* status, IDartsScores* scores);

        void add(const QString& mod, const int& point) override;
        void setEvaluator(AbstractDartsEvaluator** evaluatorRef) override;

private:
        // Private member methods
        void evaluateAndPersist(const Input& input);

        // Services
        IDartsInputs* const _inputs;
        IDartsInputTrimmer* const _trimmer;
        IDartsIndexes* const _indexes;
        AbstractDartsEvaluator** _evaluator;
        IDartsStatus* const _status;
        IDartsScores* const _scores;
};

#endif // DARTSINPUTADDER_H
