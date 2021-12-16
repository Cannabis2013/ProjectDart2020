#ifndef DCINITPLAYERSCORES_H
#define DCINITPLAYERSCORES_H
#include "DartsController/DCScoresSLAs/absdcplayersctx.h"
#include "DartsController/PlayerStatsSLAs/idcstatscontext.h"
#include "DartsController/DCMetaServices/dcmeta.h"
#include "DartsController/DCMetaSLAs/idcmetacontext.h"
#include "DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h"
#include "DartsModelsContext//TournamentModels/tnmvalues.h"
#include <DartsController/DCMetaSLAs/abstractdcmetabuilder.h>
class DCInit
{
public:
    static void initTournamentMeta(const DCMeta &meta,
                                   IDCMetaContext *metaCtx,
                                   IDCIdxCtrl *indexController)
    {
        metaCtx->set(meta);
        indexController->init(meta);
    }
    static void initPlayerDetails(const QVector<IPlayer*> &playerMds, const DCMeta &meta,
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
    static QStringList convertPlayerMds(const QVector<IPlayer*> &playerMds)
    {
        QStringList names;
        for (const auto &playerMd : playerMds)
            names << playerMd->name();
        return names;
    }
};
#endif // DCINITPLAYERSCORES_H
