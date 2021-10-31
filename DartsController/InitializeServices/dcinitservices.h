#ifndef DCINITPLAYERSCORES_H
#define DCINITPLAYERSCORES_H

#include "DartsController/DCPlayerServices/dcplayer.h"
#include "DartsController/DCMetaSLAs/idcinitialscore.h"
#include "DartsController/DCPlayerSLAs/IDCPlayerController.h"
#include "DartsController/DCScoresSLAs/idcscorebuilder.h"
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCScoresSLAs/idcupdateplayerscores.h"
#include "DartsController/PlayerStatsSLAs/idcplayerstats.h"
#include "DartsController/DCMetaSLAs/idartsstatuscodes.h"
#include "DartsController/DCMetaSLAs/idcstatus.h"
#include "DartsController/DCMetaSLAs/idcwinnerservice.h"

class DCInitServices
{
public:
    static void init(const QVector<DCPlayer> &players, const IDCInitialScore *initialScore, IDCScoreModels *scoreModels,
                      const IDCScoreBuilder *scoreBuilder, IDCPlayerStats *playerStats, IDCPlayerController *playerController)
    {
        auto models = scoreBuilder->createScores(players,initialScore->get());
        scoreModels->scores().append(models);
        playerStats->setPlayers(players);
        playerController->setPlayers(players);
    }
    static void init(const QVector<DCInput> &inputs,const IDCUpdatePlayerScores *updatePlayerScores,const IDCUpdatePlayerStat *updatePlayerStats,
                     IDCScoreModels *scoreModels, IDCPlayerStats *playerStats)
    {
        updatePlayerScores->update(inputs,scoreModels);
        updatePlayerStats->update(inputs,playerStats);
    }
    static void init(const DCPlayer &winner, IDCWinnerService *winnerService, IDCStatus *controllerStatus, const IDartsStatusCodes *statusCodes)
    {
        winnerService->set(winner);
        if(winnerService->get().id != QUuid())
            controllerStatus->set(statusCodes->winnerFound());
    }
};

#endif // DCINITPLAYERSCORES_H
