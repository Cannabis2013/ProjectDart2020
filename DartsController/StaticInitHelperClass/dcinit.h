#ifndef DCINITPLAYERSCORES_H
#define DCINITPLAYERSCORES_H
#include "DartsController/DCPlayerSLAs/IDCPlayerController.h"
#include "DartsController/DCScoresSLAs/idcscorebuilder.h"
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCScoresSLAs/idcupdateplayerscores.h"
#include "DartsController/PlayerStatsSLAs/idcplayerstats.h"
#include "DartsController/DCMetaSLAs/idartsstatuscodes.h"
#include "DartsController/DCMetaServices/dcmeta.h"
#include "DartsController/DCMetaSLAs/idcmetainfo.h"
#include "DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h"
class DCInit
{
public:
    typedef  IModel<QUuid> Player;
    typedef QVector<Player*> Players;
    static void initTournamentMeta(IModel<QUuid> *model, IDCMetaInfo *metaInfo)
    {
        auto tournament = dynamic_cast<AbstractDartsTournament*>(model);
        auto meta = &metaInfo->get();
        meta->initialRemainingScore = tournament->initialRemaining();
        meta->tournamentId = tournament->id();
        meta->winnerId = tournament->winnerId();
        meta->winnerName = tournament->winnerName();
    }
    static void initPlayerDetails(const Players &players, const DCMeta &meta, IDCScoreModels *scoreModels,
                                  const IDCScoreBuilder *scoreBuilder, IDCPlayerStats *playerStats, IDCPlayerController *playerController)
    {
        /*
         * Initialize scoremodels with player details and iniitalscore
         */
        auto models = scoreBuilder->createScores(players,meta.initialRemainingScore);
        scoreModels->scores().append(models);
        /*
         * Initialize player statistiscs with player details
         */
        playerStats->setPlayers(players);
        /*
         * Initialize playercontroller with player details
         */
        playerController->set(players);
    }
    static void initScores(const QVector<IModel<QUuid>*> &inputs,const IDCUpdatePlayerScores *updatePlayerScores,
                           const IDCUpdatePlayerStat *updatePlayerStats,IDCScoreModels *scoreModels,
                           IDCPlayerStats *playerStats)
    {
        updatePlayerScores->update(inputs,scoreModels);
        updatePlayerStats->update(inputs,playerStats);
    }
};
#endif // DCINITPLAYERSCORES_H
