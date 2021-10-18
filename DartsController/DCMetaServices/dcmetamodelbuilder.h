#ifndef DCMETAMODELBUILDER_H
#define DCMETAMODELBUILDER_H

#include "DartsController/DCMetaSLAs/idcmetamodelbuilder.h"

class DCMetaModelBuilder : public IDCMetaModelBuilder
{
public:
    DCMetaModelBuilder(IDCIndexService *indexContext, IDCScoresService *scoresContext):
        _indexContext(indexContext),_scoresContext(scoresContext)
    {
        if(_indexContext == nullptr || _scoresContext == nullptr)
            throw "INJECT ME";
    }
    virtual DCMetaInfo buildMeta(const IDCTournamentId *IdService, const IDCPlayerService *playerService,
                                 const IDCWinnerService *winnerService) const override
    {
        DCMetaInfo metaInfo;
        metaInfo.tournamentId = IdService->id();
        metaInfo.currentPlayerId = playerService->currentPlayerId(_indexContext,_scoresContext);
        metaInfo.currentPlayerName = playerService->currentPlayerName(_indexContext,_scoresContext);
        metaInfo.winnerId = winnerService->winnerId();
        metaInfo.winnerName = winnerService->winnerName();
        return metaInfo;
    }
private:
    const IDCIndexService *const _indexContext;
    IDCScoresService *const _scoresContext;
};

#endif // DCMETAMODELBUILDER_H
