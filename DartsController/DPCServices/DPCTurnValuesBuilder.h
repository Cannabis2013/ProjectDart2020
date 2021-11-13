#ifndef DPCTURNVALUESBUILDER_H
#define DPCTURNVALUESBUILDER_H

#include "DartsController/DCTurnValuesSLAs/icreatedcturnvalues.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCFinishesSLAs/idartsinputfinishes.h"

class DPCTurnValuesBuilder : public ICreateDCTurnValues
{
public:
    DCTurnValues turnValues(IDartsIndex *index, IDCScoreModels *scoresService,
                            const IDartsInputFinishes *logisticService = nullptr) const override
    {
        DCTurnValues model;
        model.canUndo = index->turnIndex() > 0;
        model.canRedo = index->turnIndex() < index->totalTurns();
        model.roundIndex = index->roundIndex();
        model.setIndex = index->setIndex();
        model.attemptIndex = index->attemptIndex();
        model.targetRow = logisticService->suggestTargetRow(getPlayerScore(index,scoresService),index->attemptIndex());
        model.playerName = scoresService->scores().at(index->setIndex()).playerName;
        return model;
    }
private:
    int getPlayerScore(IDartsIndex *index, IDCScoreModels *scoresService) const
    {
        auto models = scoresService->scores();
        auto model = models.at(index->setIndex());
        return model.remainingScore;
    }
};
#endif // BUILDDARTSPOINTTURNVALUES_H
