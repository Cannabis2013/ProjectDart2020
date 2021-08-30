#ifndef CREATEDPCTURNVALUES_H
#define CREATEDPCTURNVALUES_H

#include "icreatedpcturnvalues.h"
#include "dartspointturnvalues.h"
#include "idartspointindexservice.h"
#include "idartsinputsuggestion.h"
#include "idpcindexes.h"
#include "idcplayer.h"
#include "idpcmodel.h"

namespace DPCContext{
    class CreateDPCTurnValues : public ICreateDPCTurnValues
    {
    public:
        DartsPointTurnValues* createTurnValues(const IDartsPointIndexService *indexService,
                                               IDCScoresService* scoresService,
                                               const IDartsInputSuggestion* logisticService = nullptr) const override
        {
            auto model = new DartsPointTurnValues;
            model->setCanUndo(indexService->canUndo());
            model->setCanRedo(indexService->canRedo());
            model->setRoundIndex(indexService->roundIndex());
            model->setSetIndex(indexService->setIndex());
            model->setAttemptIndex(indexService->attemptIndex());
            model->setTargetRow(createTargetRow(indexService,scoresService,logisticService));
            model->setPlayerName(getPlayerName(indexService,scoresService));
            return model;
        }
    private:
        QString createTargetRow(const IDartsPointIndexService *indexService,
                               IDCScoresService *scoresService,
                               const IDartsInputSuggestion* logisticService) const
        {
            if(logisticService == nullptr)
                return "Logistic service not injected";
            auto remainingScore = getPlayerScore(indexService,scoresService);
            auto attemptIndex = indexService->attemptIndex();
            auto targetRow = logisticService->suggestTargetRow(remainingScore,attemptIndex);
            return targetRow;
        }
        int getPlayerScore(const IDartsPointIndexService *indexService, IDCScoresService *scoresService) const
        {
            auto models = scoresService->tuples();
            auto model = models.at(indexService->setIndex());
            return model.totalScore;
        }
        QString getPlayerName(const IDartsPointIndexService *indexService, IDCScoresService *scoresService) const
        {
            auto models = scoresService->tuples();
            auto model = models.at(indexService->setIndex());
            return model.name;
        }
    };
}
#endif // BUILDDARTSPOINTTURNVALUES_H
