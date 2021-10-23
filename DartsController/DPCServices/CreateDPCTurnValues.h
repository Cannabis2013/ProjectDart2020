#ifndef CREATEDPCTURNVALUES_H
#define CREATEDPCTURNVALUES_H

#include "DartsController/DCTurnValuesSLAs/icreatedcturnvalues.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCFinishesSLAs/idartsinputfinishes.h"

class CreateDPCTurnValues : public ICreateDCTurnValues
{
public:
    DCTurnValues turnValues(const IDCIndexController *indexService, IDCScoresService* scoresService,
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
    QString createTargetRow(const IDCIndexController *indexService,
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
    int getPlayerScore(const IDCIndexController *indexService, IDCScoresService *scoresService) const
    {
        auto models = scoresService->scoreModels();
        auto model = models.at(indexService->setIndex());
        return model.remainingScore;
    }
    QString getPlayerName(const IDCIndexController *indexService, IDCScoresService *scoresService) const
    {
        auto models = scoresService->scoreModels();
        auto model = models.at(indexService->setIndex());
        return model.playerName;
    }
    bool canUndo(const IDCIndexController *indexService) const
    {
        return indexService->turnIndex() > 0;
    }
    bool canRedo(const IDCIndexController *indexService) const
    {
        return indexService->turnIndex() < indexService->totalIndex();
    }
};
#endif // BUILDDARTSPOINTTURNVALUES_H
