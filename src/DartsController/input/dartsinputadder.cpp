#include "dartsinputadder.h"

DartsInputAdder::DartsInputAdder(IDartsInputs* inputs, IDartsInputTrimmer* trimmer,
    IDartsIndexes* indexes, IDartsStatus* status)
    : _inputs(inputs)
    , _trimmer(trimmer)
    , _indexes(indexes)
    , _status(status)
{
}

void DartsInputAdder::add(const QString& mod, const int& point)
{
        if (!_status->isWinnerFound()) {
                _trimmer->trimInputs();
                if (persistInput(Input(mod, point)))
                        _indexes->next();
                else {
                        _trimmer->removeTurnInputs();
                        _indexes->skipturn();
                }
        }
}

void DartsInputAdder::setEvaluator(IDartsEvaluator** evaluatorRef)
{
        _evaluator = evaluatorRef;
}

bool DartsInputAdder::persistInput(const Input& input){
        auto evaluator = *_evaluator;
        if (evaluator->evaluatorInput(input.mod(), input.point())) {
                _inputs->save(input);
                return true;
        }
        return false;
}
