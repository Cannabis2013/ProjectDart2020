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
    return getScoresAsJson()->get();
}

int DartsController::status() const
{
    return metaServices()->metaManager()->status();
}

int DartsController::initialize(const QUuid &tournamentId)
{
    return initializer()->init(tournamentId);
}

QByteArray DartsController::addInput(const QByteArray& byteArray)
{
    return addInputModel()->add(byteArray,this);
}

bool DartsController::reset()
{
    return resetServices()->reset();
}

QByteArray DartsController::undoTurn()
{
    return undoPlayerTurn()->undo();
}

QByteArray DartsController::redoTurn()
{
    return redoPlayerTurn()->redo();
}

QByteArray DartsController::getTurnValues() const
{
    return turnValuesAsJson()->toJson();
}

QByteArray DartsController::getWinnerJson() const
{
    return createWinnerReport()->create();
}
