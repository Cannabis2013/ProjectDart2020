#include "dartscontroller.h"
#include "SLAs/absdartsctx.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
#include "Models/dcmeta.h"
#include "Models/dcturnvalues.h"

QString DartsController::tournamentId() const
{
    return metaServices()->metaManager()->tournamentID().toString(QUuid::WithBraces);
}

QByteArray DartsController::getPlayerScores() const
{
    auto playerModels = playerServices()->playerManager()->players();
    return jsonServices()->createJson()->create(playerModels);
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
    auto input = routines()->addInputToModelsContext()->add(byteArray);
    auto meta = metaServices()->metaManager()->meta();
    return jsonServices()->createJson()->create(input,meta);
}

bool DartsController::reset()
{
    routines()->resetServices()->reset();
    auto tournamentID = metaServices()->metaManager()->tournamentID();
    return modelsContext()->resetTournament(tournamentID);
}

QByteArray DartsController::undoTurn()
{
    auto inputAsByteArray = routines()->undoTurn()->undo();
    return inputAsByteArray;
}

QByteArray DartsController::redoTurn()
{
    auto inputAsByteArray = routines()->redoTurn()->redo();
    return inputAsByteArray;
}

QByteArray DartsController::getTurnValues() const {
    auto values = turnValsServices()->turnValuesBuilder()->create();
    auto meta = metaServices()->metaManager()->meta();
    return jsonServices()->createJson()->create(values,meta);
}

QByteArray DartsController::getWinnerJson() const
{
    auto metaService = metaServices()->metaManager();
    auto indexController = indexServices()->indexController();
    auto playerManager = playerServices()->playerManager();
    auto createMeta = metaServices()->createMeta();
    auto winnerMeta = createMeta->winnerMeta(metaService,indexController,playerManager);
    return jsonServices()->createJson()->create(winnerMeta);
}
