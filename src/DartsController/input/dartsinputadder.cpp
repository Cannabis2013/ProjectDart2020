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
        evaluateAndPersist(mod, point);
        _scores->update();
        (*_evaluator)->evaluateWinnerCondition();
}

void DartsInputAdder::setEvaluator(AbstractDartsEvaluator** evaluatorPtr)
{
        _evaluator = evaluatorPtr;
}

void DartsInputAdder::evaluateAndPersist(const QString& mod, const int& point)
{
        if ((*_evaluator)->evaluateInput(mod, point)) {
                _inputs->save(Input(mod, point));
                _indexes->next();
        } else {
                _trimmer->removeTurnInputs();
                _indexes->skipturn();
        }
}
