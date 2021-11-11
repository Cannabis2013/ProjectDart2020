#ifndef DCINITPLAYERSCORES_H
#define DCINITPLAYERSCORES_H

#include "DartsController/DCPlayerServices/dcplayer.h"
#include "DartsController/DCPlayerSLAs/IDCPlayerController.h"
#include "DartsController/DCScoresSLAs/idcscorebuilder.h"
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCScoresSLAs/idcupdateplayerscores.h"
#include "DartsController/PlayerStatsSLAs/idcplayerstats.h"
#include "DartsController/DCMetaSLAs/idartsstatuscodes.h"
#include "DartsController/DCMetaServices/dcmeta.h"
class DCInit
{
public:
    static void init(const QVector<DCPlayer> &players, const DCMeta &meta, IDCScoreModels *scoreModels, const IDCScoreBuilder *scoreBuilder, IDCPlayerStats *playerStats, IDCPlayerController *playerController)
    {
        auto models = scoreBuilder->createScores(players,meta.initialRemainingScore);
        scoreModels->scores().append(models);
        playerStats->setPlayers(players);
        playerController->set(players);
    }
    static void init(const QVector<DCInput> &inputs,const IDCUpdatePlayerScores *updatePlayerScores,const IDCUpdatePlayerStat *updatePlayerStats,
                     IDCScoreModels *scoreModels, IDCPlayerStats *playerStats)
    {
        updatePlayerScores->update(inputs,scoreModels);
        updatePlayerStats->update(inputs,playerStats);
    }
    static void init(const DCPlayer &winner, DCMeta &meta, const IDartsStatusCodes *statusCodes)
    {
        meta.winnerId = winner.id;
        meta.winnerName = winner.name;
        if(meta.winnerId != QUuid())
            meta.status = statusCodes->winnerFound();
    }
};

#endif // DCINITPLAYERSCORES_H
