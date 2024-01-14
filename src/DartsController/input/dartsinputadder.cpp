#include "dartsinputadder.h"

DartsInputAdder::DartsInputAdder(IDartsInputs* inputs, IDartsInputTrimmer* trimmer,
    IDartsIndexes* indexes, IDartsStatus* status, IDartsScores* scores)
    : _inputs(inputs)
    , _trimmer(trimmer)
    , _indexes(indexes)
    , _status(status)
    , _scores(scores)
{
}

void DartsInputAdder::add(const QString& mod, const int& point)
{
        if (_status->isWinnerFound())
                return;
        _trimmer->trimInputs();
        evaluateAndPersist(Input(mod, point));
        _scores->update();
        (*_evaluator)->evaluateWinnerCondition();
}

void DartsInputAdder::setEvaluator(AbstractDartsEvaluator** evaluatorPtr)
{
        _evaluator = evaluatorPtr;
}

void DartsInputAdder::evaluateAndPersist(const Input& input)
{
        if ((*_evaluator)->evaluateInput(input.mod(), input.point())) {
                _inputs->save(input);
                _indexes->next();
        } else {
                _trimmer->removeTurnInputs();
                _indexes->skipturn();
        }
}
