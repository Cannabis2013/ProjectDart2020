#ifndef DCINITPLAYERSCORES_H
#define DCINITPLAYERSCORES_H
#include "DartsController/DCPlayerSLAs/IDCPlayerCtx.h"
#include "DartsController/DCScoresSLAs/idcscorebuilder.h"
#include "DartsController/DCScoresSLAs/abstractdcscoresctx.h"
#include "DartsController/DCScoresSLAs/idcupdateplayerscores.h"
#include "DartsController/PlayerStatsSLAs/idcstatscontext.h"
#include "DartsController/DCMetaSLAs/idartsstatuscodes.h"
#include "DartsController/DCMetaServices/dcmeta.h"
#include "DartsController/DCMetaSLAs/idcmetactx.h"
#include "DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h"
class DCInit
{
public:
    static void initTournamentMeta(AbstractDartsTournament *tournament,
                                   IDCMetaCtx *metaInfo,
                                   AbstractDCIdxCtrl *indexController,
                                   IDCIdxConverter *idxBuilder)
    {
        auto meta = &metaInfo->get();
        meta->initRemScore = tournament->initialRemaining();
        meta->tournamentId = tournament->id();
        meta->winnerId = tournament->winnerId();
        meta->winnerName = tournament->winnerName();
        indexController->init(idxBuilder->convert(tournament));
        auto pCount = tournament->playerIds().count();
        indexController->setPlayerCount(pCount);
    }
    static void initPlayerDetails(const QVector<IPlayerModel*> &playerMds, const DCMeta &meta, AbstractDCScoresCtx *scoreModels,
                                  const IDCScoreBuilder *scoreBuilder, IDCStatsContext *playerStats, IDCPlayerCtx *playerController)
    {
        auto playerNames = DCInit::convertPlayerMds(playerMds);
        /*
         * Initialize scoremodels with player details and iniitalscore
         */
        auto models = scoreBuilder->createScores(playerNames,meta.initRemScore);
        scoreModels->scores().append(models);
        /*
         * Initialize player statistiscs with player details
         */
        playerStats->setPlayers(playerNames);
        /*
         * Initialize playercontroller with player details
         */
        playerController->set(playerNames);
    }
    static void initScores(const QVector<DCIptVals> &inputs,const IDCUpdatePlayerScores *updatePlayerScores,
                           const IDCUpdatePlayerStat *updatePlayerStats,AbstractDCScoresCtx *scoreModels,
                           IDCStatsContext *playerStats)
    {
        updatePlayerScores->update(inputs,scoreModels);
        updatePlayerStats->update(inputs,playerStats);
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
