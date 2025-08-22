#include "dartsturncontroller.h"
#include "src/input/services/idartsinputsfilter.h"
#include "src/players/models/dartsplayer.h"
#include "src/players/persistences/idartsplayers.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"
#include "src/validation/services/iclosurefilter.h"
#include "src/validation/services/iopenvalidator.h"

DartsTurnController::DartsTurnController(ServiceCollection* services)
    : _services(services)
{
}

void DartsTurnController::undo()
{
    undoTurn();
    auto playerIndex = _services->indexes->index().playerIndex();
    auto name = _services->playerFetcher->get(playerIndex).name();
    auto index = _services->indexes->index();
    if (!_services->inputsFilter->anyInputs(name, index.turnId()))
        _services->openingFilter->update(name, false);
}

void DartsTurnController::redo()
{
    auto playerIndex = _services->indexes->index().playerIndex();
    auto name = _services->playerFetcher->get(playerIndex).name();
    redoTurn();
    auto index = _services->indexes->index();
    if (_services->inputsFilter->anyInputs(name, index.turnId()))
        _services->openingFilter->update(name, true);
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
    _services->indexes->undo();
    _services->closeningFilter->evaluateWinnerCondition();
}

void DartsTurnController::redoTurn()
{
        _services->indexes->redo();
        _services->closeningFilter->evaluateWinnerCondition();
}

int DartsTurnController::playerNumber() const
{
    return _services->indexes->index().playerIndex();
}

QByteArray DartsTurnController::report() const
{
    auto jsonObj = _services->indexes->index().object();
    auto jsonDoc = QJsonDocument(jsonObj);
    return jsonDoc.toJson(QJsonDocument::Compact);
}
