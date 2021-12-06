#ifndef DCINITPLAYERSCORES_H
#define DCINITPLAYERSCORES_H
#include "DartsController/DCScoresSLAs/absdcplayersctx.h"
#include "DartsController/PlayerStatsSLAs/idcstatscontext.h"
#include "DartsController/DCMetaServices/dcmeta.h"
#include "DartsController/DCMetaSLAs/idcmetacontext.h"
#include "DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h"
class DCInit
{
public:
    static void initTournamentMeta(AbstractDartsTournament *tournament,
                                   IDCMetaContext *metaInfo,
                                   AbsDCIdxCtrl *indexController,
                                   IDCIdxConverter *idxBuilder)
    {
        auto meta = &metaInfo->get();
        meta->initRemScore = tournament->initialRemaining();
        meta->tournamentId = tournament->id();
        meta->winnerName = tournament->winnerName();
        meta->entryRestricted = tournament->entryRestricted();
        indexController->init(idxBuilder->convert(tournament));
        auto pCount = tournament->playerIds().count();
        indexController->setPlayerCount(pCount);
    }
    static void initPlayerDetails(const QVector<IPlayerModel*> &playerMds, const DCMeta &meta,
                                  AbsDCPlayersCtx *playersContext, IDCStatsContext *playerStats)
    {
        auto playerNames = DCInit::convertPlayerMds(playerMds);
        /*
         * Initialize scoremodels with player details and iniitalscore
         */
        playersContext->set(playerNames,meta.initRemScore);
        /*
         * Initialize player statistiscs with player details
         */
        playerStats->setPlayers(playerNames);
    }
    static void initScores(const QVector<DCInput> &inputs, IDCStatsContext *statsContext,
                           AbsDCPlayersCtx *scoreModels)
    {
        scoreModels->updateScores(inputs);
        statsContext->update(inputs);
    }
    static void initStatus(IDCMetaContext *metaContext)
    {
        auto meta = &metaContext->get();
        if(meta->winnerName == QString())
            meta->status = IDCMetaContext::Initialized;
        else
            meta->status = IDCMetaContext::WinnerDeclared;
    }
private:
    static QStringList convertPlayerMds(const QVector<IPlayerModel*> &playerMds)
    {
        QStringList names;
        for (const auto &playerMd : playerMds)
            names << playerMd->name();
        return names;
    }
};
#endif // DCINITPLAYERSCORES_H
