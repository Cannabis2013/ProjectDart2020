#include "dcinitializecontroller.h"
#include "SLAs/absdartsctx.h"
#include "Models/dcmeta.h"
#include "Models/dcinput.h"
#include "Models/dcplayer.h"
#include "qjsonobject.h"
#include "ServicesProvider/dcservices.h"

DCInitializeController::DCInitializeController(DCServices *services): _services(services){}

void DCInitializeController::init(const QUuid &tournamentId, AbsDartsCtx *ctx)
{
    auto convertInput = _services->iptBuilder();
    auto tnmtBa = ctx->tournament(tournamentId);
    auto convertPlayer = _services->playerConverter();
    auto meta = _services->metaConverter()->convert(tnmtBa);
    auto players = _services->convertPlayers()->convert(tnmtBa,convertPlayer);
    auto inputs = _services->convertInputs()->convert(ctx->inputs(tournamentId),convertInput);
    initMeta(meta);
    initPlayerDetails(players,meta);
    initPlayerScores(inputs);
    _services->metaService()->setStatus(Initialized);
}

void DCInitializeController::initMeta(const DCMeta &meta)
{
    _services->metaService()->setMeta(meta);
    _services->indexService()->init(meta);
}

void DCInitializeController::initPlayerDetails(const QVector<DCPlayer> &players, const DCMeta &meta)
{
    _services->playerService()->addPlayers(updatePlayers(players,meta.initRemScore));
    _services->statisticsService()->setPlayers(players);
}

void DCInitializeController::initPlayerScores(const QVector<DCInput> &inputs)
{
    _services->playerService()->updateScores(inputs);
    _services->statisticsService()->update(inputs);
}

void DCInitializeController::initStatus()
{
    auto meta = &_services->metaService()->meta();
    if(meta->winnerName == QString())
        meta->status = IDCMetaService<DCMeta>::Initialized;
    else
        meta->status = IDCMetaService<DCMeta>::WinnerDeclared;
}

QVector<DCPlayer> DCInitializeController::updatePlayers(const QVector<DCPlayer> &players, const int &remScore)
{
    auto updatedPlayers = players;
    for (auto &player : updatedPlayers)
        player.remScore =  remScore;
    return updatedPlayers;
}
