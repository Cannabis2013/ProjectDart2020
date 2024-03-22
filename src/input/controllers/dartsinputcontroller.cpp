#include "dartsinputcontroller.h"
#include "src/input/services/idartsinputupdate.h"
#include "src/scores/persistence/idartsscores.h"
#include "src/scores/services/iscoresupdate.h"
#include "src/servicecollection.h"
#include "src/status/idartsstatus.h"
#include "src/turns/persistences/idartsindexes.h"

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
