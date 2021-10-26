#ifndef DCMETAMODELBUILDER_H
#define DCMETAMODELBUILDER_H

#include "DartsController/DCMetaSLAs/idcmetamodelbuilder.h"

class DCMetaModelBuilder : public IDCMetaModelBuilder
{
public:
    virtual DCMetaInfo buildMeta(const IDCTournamentId *IdService, const DCIndex &index, IDCScoreModels *scoreModels,
                                 const IDCWinnerService *winnerService) const override
    {
        DCMetaInfo metaInfo;
        metaInfo.tournamentId = IdService->id();
        metaInfo.currentPlayerId = scoreModels->scores().at(index.setIndex).playerId;
        metaInfo.currentPlayerName = scoreModels->scores().at(index.setIndex).playerName;
        metaInfo.winnerId = winnerService->winnerId();
        metaInfo.winnerName = winnerService->winnerName();
        return metaInfo;
    }
};

#endif // DCMETAMODELBUILDER_H
