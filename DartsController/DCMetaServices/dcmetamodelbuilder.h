#ifndef DCMETAMODELBUILDER_H
#define DCMETAMODELBUILDER_H

#include "DartsController/DCMetaSLAs/idcmetamodelbuilder.h"

class DCMetaModelBuilder : public IDCMetaModelBuilder
{
    // IDCMetaModelBuilder interface
public:
    virtual DCMetaInfo buildMeta(const IDCTournamentId *IdService, const IDCPlayerService *playerService,
                                 const IDCWinnerService *winnerService, const IDCIndexService *indexContext,
                                 IDCScoresService *scoresContext) const override
    {
        DCMetaInfo metaInfo;
        metaInfo.tournamentId = IdService->id();
        metaInfo.currentPlayerId = playerService->currentPlayerId(indexContext,scoresContext);
        metaInfo.currentPlayerName = playerService->currentPlayerName(indexContext,scoresContext);
        metaInfo.winnerId = winnerService->winnerId();
        metaInfo.winnerName = winnerService->winnerName();
        return metaInfo;
    }
};

#endif // DCMETAMODELBUILDER_H
