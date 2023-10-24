#include "dartsinputadder.h"

DartsInputAdder::DartsInputAdder(IDartsInputs* inputs, IDartsEvaluator** evaluator,
    IDartsIndexes* indexes, IDartsStatus* status)
    : _inputs(inputs)
    , _evaluator(evaluator)
    , _indexes(indexes)
    , _status(status)
{
}

void DartsInputAdder::add(const QString& mod, const int& point){
        if (!_status->isWinnerFound()) {
                trimInputs();
                if (persistInput(Input(mod, point)))
                        _indexes->next();
                else {
                        removeTurnInputs();
                        _indexes->skipturn();
                }
        }
}

void DartsInputAdder::trimInputs(){
        auto throwIndex = _indexes->index().throwIndex();
        _inputs->remove([throwIndex](const Input& input) {
                return input.throwIndex() < throwIndex;
        });
}

void DartsInputAdder::removeTurnInputs(){
        auto indexModel = _indexes->index();
        auto index = indexModel.throwIndex() - indexModel.turnIndex();
        _inputs->remove([index](const Input& input) {
                return input.throwIndex() < index;
        });
}

bool DartsInputAdder::persistInput(const Input& input){
        if ((*_evaluator)->evaluatorInput(input.mod(), input.point()))
                _inputs->save(input);
        else
                return false;
        return true;
}
