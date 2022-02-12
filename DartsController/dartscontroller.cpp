#include "dartscontroller.h"
#include "SLAs/absdartsctx.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
#include "Models/dcmeta.h"

QString DartsController::tournamentId() const
{
    return metaService()->tournamentId().toString(QUuid::WithBraces);
}

QByteArray DartsController::getPlayerScores() const
{
    return createJson()->create(playerManager()->players());
}

int DartsController::status() const
{
    return metaService()->status();
}

int DartsController::initialize(const QUuid &tournamentId)
{
    initializer()->init(tournamentId,modelsContext());
    return metaService()->status();
}

QByteArray DartsController::addInput(const QByteArray& byteArray)
{
    auto input = addInputToModelsContext()->add(byteArray);
    return createJson()->create(input,metaService()->meta());
}

bool DartsController::reset()
{
    resetServices()->reset();
    return modelsContext()->resetTournament(metaService()->tournamentId());
}

QByteArray DartsController::undoTurn()
{
    indexController()->undo();
    externalInputService()->hideInput();
    auto ipt = externalInputService()->getPreviousInput();
    playerManager()->updateScore(ipt);
    return createJson()->create(ipt,metaService()->meta());
}

QByteArray DartsController::redoTurn()
{
    externalInputService()->displayInput();
    auto ipt = externalInputService()->getCurrentInput();
    playerManager()->updateScore(ipt);
    indexController()->redo();
    return createJson()->create(ipt,metaService()->meta());
}

QByteArray DartsController::getTurnValues() const {
    auto values = turnValuesBuilder()->create();
    return createJson()->create(values,metaService()->meta());
}

QByteArray DartsController::getWinnerJson() const
{
    return createJson()->create(createMeta()->winnerMeta(metaService(),indexController(),playerManager()));
}
