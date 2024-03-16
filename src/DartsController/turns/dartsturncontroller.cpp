#include "dartsturncontroller.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/input/idartsinputs.h"
#include "src/DartsController/input/idartsinputtrimmer.h"
#include "src/DartsController/players/dartsplayer.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/scores/persistence/idartsscores.h"
#include "src/DartsController/servicecollection.h"
#include "src/DartsController/status/idartsstatus.h"
#include "src/DartsController/validation/abstractdartsevaluator.h"

DartsTurnController::DartsTurnController(ServiceCollection* services)
    : _services(services)
{
}

void DartsTurnController::undo()
{
        auto name = _services->players->one().name();
        undoTurn();
        auto index = _services->indexes->index();
        if (!_services->inputs->anyInputs(name, index.throwIndex()))
                _services->evaluator->updateAllowance(name, false);
}

void DartsTurnController::redo()
{
        auto name = _services->players->one().name();
        redoTurn();
        auto throwIndex = _services->indexes->index().throwIndex();
        if (_services->inputs->anyInputs(name, throwIndex))
                _services->evaluator->updateAllowance(name, true);
}

void DartsTurnController::skip()
{
        _services->trimmer->trimInputs();
        _services->indexes->skipturn();
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
        _services->scores->update();
        _services->evaluator->evaluateWinnerCondition();
}

void DartsTurnController::redoTurn()
{
        _services->indexes->redo();
        _services->scores->update();
        _services->evaluator->evaluateWinnerCondition();
}

int DartsTurnController::playerNumber() const
{
        return _services->indexes->index().playerIndex();
}

int DartsTurnController::playerTurn() const
{
        return _services->indexes->index().turnIndex();
}
