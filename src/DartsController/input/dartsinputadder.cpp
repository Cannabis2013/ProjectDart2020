#include "dartsinputadder.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/input/idartsinputs.h"
#include "src/DartsController/input/idartsinputtrimmer.h"
#include "src/DartsController/scores/persistence/idartsscores.h"
#include "src/DartsController/servicecollection.h"
#include "src/DartsController/status/idartsstatus.h"

DartsInputAdder::DartsInputAdder(ServiceCollection* services)
    : _services(services)
{
}

void DartsInputAdder::add(const QString& mod, const int& point)
{
        if (_services->status->isWinnerFound())
                return;
        _services->trimmer->trimInputs();
        evaluateAndPersist(Input(mod, point));
        _services->scores->update();
        _services->evaluator->evaluateWinnerCondition();
}

void DartsInputAdder::evaluateAndPersist(const Input& input)
{
        if (_services->evaluator->evaluateInput(input.mod(), input.point())) {
                _services->inputs->save(input);
                _services->indexes->next();
        } else {
                _services->trimmer->removeTurnInputs();
                _services->indexes->skipturn();
        }
}
