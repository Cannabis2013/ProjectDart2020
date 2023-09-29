#include "dartscontroller.h"
#include <quuid.h>
#include <DartsController/Contracts/Meta/dcmetaservices.h>

QString DartsController::tournamentId() const
{
    return _metaServices->metaManager()->tournamentID().toString(QUuid::WithBraces);
}

QByteArray DartsController::getPlayerScores() const
{
    return _playerScores->get();
}

int DartsController::status() const
{
    return _metaServices->metaManager()->status();
}

int DartsController::initialize(const QUuid &tournamentId)
{
    return _initialize->init(tournamentId);
}

QByteArray DartsController::addInput(const QByteArray& byteArray)
{
    return _inputPersist->add(byteArray, this);
}

bool DartsController::reset()
{
    return _resetServices->reset();
}

QByteArray DartsController::undoTurn()
{
    return _undoTurn->undo();
}

QByteArray DartsController::redoTurn()
{
    return _redoTurn->redo();
}

QByteArray DartsController::getTurnValues() const
{
    return _getTurnValuesAsJson->toJson();
}

QByteArray DartsController::getWinnerJson() const
{
    return _createWinnerReport->create();
}
