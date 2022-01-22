#include "dcinitialize.h"
#include "DCScoresSLAs/absdcplayersctx.h"
#include "PlayerStatsSLAs/idcstatistics.h"
#include "DCMetaSLAs/idcmetabuilder.h"
#include "DbSLAs/iplayer.h"
#include <qstringlist.h>
#include <qvector.h>
#include "Models/dcmeta.h"
#include "DCMetaSLAs/idcmetacontext.h"
#include "DCIndexSLAs/idcindexcontroller.h"
#include "Models/dcplayer.h"
DCInitialize::DCInitialize(AbsDCPlayersCtx *plaCtx, IDCStatistics *statistics, IDCMetaContext *metaCtx, IDCIndexController *idxCtrl):
    _playersContext(plaCtx),_statistics(statistics),_metaContext(metaCtx),_indexController(idxCtrl)
{}

void DCInitialize::init(const QVector<DCPlayer> &playerMds, const DCMeta &meta, const QVector<DCInput> &inputs)
{
    initMeta(meta);
    initPlayerDetails(playerMds,meta);
    initScores(inputs);
    initStatus();
}

void DCInitialize::initMeta(const DCMeta &meta)
{
    _metaContext->setMeta(meta);
    _indexController->init(meta);
}

void DCInitialize::initPlayerDetails(const QVector<DCPlayer> &players, const DCMeta &meta)
{
    auto playerNames = toPlayerNames(players);
    _playersContext->set(playerNames,meta.initRemScore);
    _statistics->setPlayers(playerNames);
}

void DCInitialize::initScores(const QVector<DCInput> &inputs)
{
    _playersContext->updateScores(inputs);
    _statistics->update(inputs);
}

void DCInitialize::initStatus()
{
    auto meta = &_metaContext->meta();
    if(meta->winnerName == QString())
        meta->status = IDCMetaContext::Initialized;
    else
        meta->status = IDCMetaContext::WinnerDeclared;
}

QStringList DCInitialize::toPlayerNames(const QVector<DCPlayer> &players)
{
    QStringList names;
    for (const auto &playerMd : players)
        names << playerMd.name;
    return names;
}
