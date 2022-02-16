#include "dartscontroller.h"
#include "SLAs/absdartsctx.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
#include "Models/dcmeta.h"

QString DartsController::tournamentId() const
{
    return metaServices()->metaManager()->tournamentID().toString(QUuid::WithBraces);
}

QByteArray DartsController::getPlayerScores() const
{
    return routines()->getScoresAsJson()->get();
}

int DartsController::status() const
{
    return metaServices()->metaManager()->status();
}

int DartsController::initialize(const QUuid &tournamentId)
{
    routines()->initializer()->init(tournamentId);
    return metaServices()->metaManager()->status();
}

QByteArray DartsController::addInput(const QByteArray& byteArray)
{
    return routines()->addInput()->add(byteArray);
}

bool DartsController::reset()
{
    return routines()->resetServices()->reset();
}

QByteArray DartsController::undoTurn()
{
    return routines()->undoTurn()->undo();
}

QByteArray DartsController::redoTurn()
{
    return routines()->redoTurn()->redo();
}

QByteArray DartsController::getTurnValues() const
{
    return routines()->turnValuesAsJson()->toJson();
}

QByteArray DartsController::getWinnerJson() const
{
    return routines()->createWinnerReport()->create();
}
