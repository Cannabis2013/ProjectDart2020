#ifndef DCINITPLAYERSCORES_H
#define DCINITPLAYERSCORES_H

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
    typedef  IModel<QUuid> Player;
    typedef QVector<Player*> Players;
    static void initPlayerDetails(const Players &players, const DCMeta &meta, IDCScoreModels *scoreModels,
                     const IDCScoreBuilder *scoreBuilder, IDCPlayerStats *playerStats, IDCPlayerController *playerController)
    {
        auto models = scoreBuilder->createScores(players,meta.initialRemainingScore);
        scoreModels->scores().append(models);
        playerStats->setPlayers(players);
        playerController->set(players);
    }
    static void initScores(const QVector<AbstractDartsInput*> &inputs,const IDCUpdatePlayerScores *updatePlayerScores,const IDCUpdatePlayerStat *updatePlayerStats,
                     IDCScoreModels *scoreModels, IDCPlayerStats *playerStats)
    {
        updatePlayerScores->update(inputs,scoreModels);
        updatePlayerStats->update(inputs,playerStats);
    }
    static void initWinnerDetails(const Player *winner, DCMeta &meta, const IDartsStatusCodes *statusCodes)
    {
        auto player = dynamic_cast<const IPlayerModel*>(winner);
        meta.winnerId = player->id();
        meta.winnerName = player->playerName();
        if(meta.winnerId != QUuid())
            meta.status = statusCodes->winnerFound();
    }
};

#endif // DCINITPLAYERSCORES_H
