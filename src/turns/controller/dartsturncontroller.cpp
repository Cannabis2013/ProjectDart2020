#include "dartsturncontroller.h"
#include "src/input/services/idartsinputsfilter.h"
#include "src/players/models/dartsplayer.h"
#include "src/players/persistences/idartsplayers.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/scores/services/iscoresupdate.h"
#include "src/servicecollection.h"
#include "src/status/idartsstatus.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"
#include "src/validation/abstractdartsevaluator.h"

DartsTurnController::DartsTurnController(ServiceCollection* services)
    : _services(services)
{
}

void DartsTurnController::undo()
{
        auto name = _services->playerFetcher->one().name();
        undoTurn();
        auto index = _services->indexes->index();
        if (!_services->inputsFilter->anyInputs(name, index.turnId()))
                _services->evaluator->updateAllowance(name, false);
}

void DartsTurnController::redo()
{
        auto name = _services->playerFetcher->one().name();
        redoTurn();
        auto index = _services->indexes->index();
        if (_services->inputsFilter->anyInputs(name, index.turnId()))
                _services->evaluator->updateAllowance(name, true);
}

bool DartsTurnController::canUndo() const
{
        return _services->indexes->canUndo();
}

bool DartsTurnController::canRedo() const
{
        return _services->indexes->canRedo();
}

void DartsTurnController::undoTurn()
{
        _services->status->running();
        _services->indexes->undo();
        _services->scoresUpdate->updatePlayerScores();
        _services->evaluator->evaluateWinnerCondition();
}

void DartsTurnController::redoTurn()
{
        _services->indexes->redo();
        _services->scoresUpdate->updatePlayerScores();
        _services->evaluator->evaluateWinnerCondition();
}

int DartsTurnController::playerNumber() const
{
        return _services->indexes->index().turnIndex();
}
