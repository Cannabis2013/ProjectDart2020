#include "dartsinputadder.h"
#include "src/DartsController/input/inputsservice.h"

DartsInputAdder::DartsInputAdder(IDartsInputs* inputs, IDartsEvaluator** evaluator,
    IDartsIndexes* indexes, IDartsStatus* status)
    : _inputs(inputs)
    , _evaluator(evaluator)
    , _indexes(indexes)
    , _status(status)
{
}

void DartsInputAdder::add(const QString& mod, const int& point)
{
        if (!_status->isWinnerFound()) {
                trimInputs();
                if (persistInput(Input(mod, point)))
                        _indexes->next();
                else {
                        nullifyTurn();
                        _indexes->skipturn();
                }
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

bool DartsInputAdder::persistInput(const Input& input)
{
        if ((*_evaluator)->evaluatorInput(input.mod(), input.point()))
                _inputs->save(input);
        else {
                _inputs->save(Input());
                return false;
        }
        return true;
}
