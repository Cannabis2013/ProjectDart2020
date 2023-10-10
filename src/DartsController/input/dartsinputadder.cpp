#include "dartsinputadder.h"
#include "src/DartsController/input/inputsservice.h"

DartsInputAdder::DartsInputAdder(IDartsInputs* inputs, IDartsInputEvaluator* evaluator, IDartsIndexes* indexes, IDartsScores* scores)
    : _inputs(inputs)
    , _evaluator(evaluator)
    , _indexes(indexes)
    , _scores(scores)
{
}

void DartsInputAdder::add(const InputRequest& req)
{
        trimInputs();
        if (addInput(req.toInput()))
                _indexes->next();
        else {
                nullifyTurn();
                _indexes->skipturn();
        }
}

void DartsInputAdder::trimInputs()
{
        auto trimmed = InputsUtility().trimmed(_inputs->inputs(), _indexes->index().throwIndex());
        _inputs->setInputs(trimmed);
}

void DartsInputAdder::nullifyTurn()
{
        auto turnIndex = _indexes->index().turnIndex();
        auto altered = InputsUtility().nullifyTurnInputs(_inputs->inputs(), turnIndex);
        _inputs->setInputs(altered);
}

bool DartsInputAdder::addInput(const Input& input)
{
        if (!_evaluator->isValid(input.mod(), input.point()))
                _inputs->save(Input());
        if (_evaluator->isWithinBounds(input.mod(), input.point()))
                _inputs->save(input);
        else {
                _inputs->save(Input());
                return false;
        }
        return true;
}
