#include "dartsinputcontroller.h"
#include "src/DartsController/input/services/idartsinputupdate.h"
#include "src/DartsController/scores/persistence/idartsscores.h"
#include "src/DartsController/scores/services/iscoresupdate.h"
#include "src/DartsController/servicecollection.h"
#include "src/DartsController/status/idartsstatus.h"
#include "src/DartsController/turns/persistences/idartsindexes.h"

DartsInputController::DartsInputController(ServiceCollection* services)
    : _services(services)
{
}

void DartsInputController::add(const QString& mod, const int& point)
{
        if (_services->status->isWinnerFound())
                return;
        _services->inputsUpdate->removeExcessInputs();
        if (_services->evaluator->evaluateInput(mod, point)) {
                _services->inputsUpdate->save(mod, point);
                _services->indexes->next();
        } else {
                _services->inputsUpdate->removeCurrentTurnInputs();
                _services->indexes->skipturn();
        }
        _services->scoresUpdate->updatePlayerScores();
        _services->evaluator->evaluateWinnerCondition();
}
