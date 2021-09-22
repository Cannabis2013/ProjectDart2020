#ifndef CREATEDPCTURNVALUES_H
#define CREATEDPCTURNVALUES_H

#include "icreatedcturnvalues.h"
#include "dcturnvalues.h"
#include "DCIndexSLA/idcindexservice.h"
#include "DCInputsSLA/idartsinputfinishes.h"
#include "idcplayer.h"
#include "DCInputsSLA/idcinputmodel.h"

class CreateDPCTurnValues : public ICreateDCTurnValues
{
public:
    const DCContext::DCTurnValues* createTurnValues(const IDCIndexService *indexService,
                                                    IDCScoresService* scoresService,
                                                    const IDartsInputFinishes* logisticService = nullptr) const override
    {
        auto model = new DCContext::DCTurnValues();
        model->setCanUndo(canUndo(indexService));
        model->setCanRedo(canRedo(indexService));
        model->setRoundIndex(indexService->roundIndex());
        model->setSetIndex(indexService->setIndex());
        model->setAttemptIndex(indexService->attemptIndex());
        model->setTargetRow(createTargetRow(indexService,scoresService,logisticService));
        model->setPlayerName(getPlayerName(indexService,scoresService));
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
        return model.name;
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
