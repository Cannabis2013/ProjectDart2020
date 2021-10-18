#ifndef CREATEDPCTURNVALUES_H
#define CREATEDPCTURNVALUES_H

#include "DartsController/DCTurnValuesSLAs/icreatedcturnvalues.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
#include "DartsController/DCIndexSLAs/idcindexservice.h"
#include "DartsController/DCFinishesSLAs/idartsinputfinishes.h"

class CreateDPCTurnValues : public ICreateDCTurnValues
{
public:
    DCTurnValues turnValues(const IDCIndexService *indexService, IDCScoresService* scoresService,
                            const IDartsInputFinishes* logisticService = nullptr) const override
    {
        DCTurnValues model;
        model.canUndo = canUndo(indexService);
        model.canRedo = canRedo(indexService);
        model.roundIndex = indexService->roundIndex();
        model.setIndex = indexService->setIndex();
        model.attemptIndex = indexService->attemptIndex();
        model.targetRow = createTargetRow(indexService,scoresService,logisticService);
        model.playerName = getPlayerName(indexService,scoresService);
        return model;
    }
private:
    QString createTargetRow(const IDCIndexService *indexService,
                           IDCScoresService *scoresService,
                           const IDartsInputFinishes* logisticService) const
    {
        if(logisticService == nullptr)
            return "Logistic service not injected";
        auto remainingScore = getPlayerScore(indexService,scoresService);
        auto attemptIndex = indexService->attemptIndex();
        auto targetRow = logisticService->suggestTargetRow(remainingScore,attemptIndex);
        return targetRow;
    }
    int getPlayerScore(const IDCIndexService *indexService, IDCScoresService *scoresService) const
    {
        auto models = scoresService->scoreModels();
        auto model = models.at(indexService->setIndex());
        return model.totalScore;
    }
    QString getPlayerName(const IDCIndexService *indexService, IDCScoresService *scoresService) const
    {
        auto models = scoresService->scoreModels();
        auto model = models.at(indexService->setIndex());
        return model.playerName;
    }
    bool canUndo(const IDCIndexService *indexService) const
    {
        return indexService->turnIndex() > 0;
    }
    bool canRedo(const IDCIndexService *indexService) const
    {
        return indexService->turnIndex() < indexService->totalIndex();
    }
};
#endif // BUILDDARTSPOINTTURNVALUES_H
