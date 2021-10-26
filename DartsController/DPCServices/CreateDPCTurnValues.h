#ifndef CREATEDPCTURNVALUES_H
#define CREATEDPCTURNVALUES_H

#include "DartsController/DCTurnValuesSLAs/icreatedcturnvalues.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCFinishesSLAs/idartsinputfinishes.h"

class CreateDPCTurnValues : public ICreateDCTurnValues
{
public:
    DCTurnValues turnValues(const DCIndex &index, IDCScoreModels* scoresService,
                            const IDartsInputFinishes* logisticService = nullptr) const override
    {
        DCTurnValues model;
        model.canUndo = index.turnIndex > 0;
        model.canRedo = index.turnIndex < index.totalTurns;
        model.roundIndex = index.roundIndex;
        model.setIndex = index.setIndex;
        model.attemptIndex = index.attemptIndex;
        model.targetRow = createTargetRow(index,scoresService,logisticService);
        model.playerName = getPlayerName(index,scoresService);
        return model;
    }
private:
    QString createTargetRow(const DCIndex &index, IDCScoreModels *scoresService,
                           const IDartsInputFinishes* logisticService) const
    {
        if(logisticService == nullptr)
            return "Logistic service not injected";
        auto remainingScore = getPlayerScore(index,scoresService);
        auto targetRow = logisticService->suggestTargetRow(remainingScore,index.attemptIndex);
        return targetRow;
    }
    int getPlayerScore(const DCIndex &index, IDCScoreModels *scoresService) const
    {
        auto models = scoresService->scores();
        auto model = models.at(index.setIndex);
        return model.remainingScore;
    }
    QString getPlayerName(const DCIndex &index, IDCScoreModels *scoresService) const
    {
        auto models = scoresService->scores();
        auto model = models.at(index.setIndex);
        return model.playerName;
    }
};
#endif // BUILDDARTSPOINTTURNVALUES_H
