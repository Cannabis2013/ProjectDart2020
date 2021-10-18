#ifndef DSCVALUESBUILDER_H
#define DSCVALUESBUILDER_H

#include "DartsController/DCTurnValuesSLAs/icreatedcturnvalues.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"

class DSCValuesBuilder : public ICreateDCTurnValues
{
public:
    DCTurnValues turnValues(const IDCIndexService* indexService, IDCScoresService* scoresService,
                                   const IDartsInputFinishes* logisticService) const override
    {
        auto tuples = scoresService->scoreModels();
        DCTurnValues model;
        model.canUndo = canUndo(indexService);
        model.canRedo = canRedo(indexService);
        model.roundIndex = indexService->roundIndex();
        model.setIndex = indexService->setIndex();
        model.targetRow = createRowSuggestionByScore(logisticService,tuples.at(model.setIndex).totalScore);
        model.playerName = tuples.at(model.setIndex).playerName;
        return model;
    }
private:
    QString createRowSuggestionByScore(const IDartsInputFinishes* logisticService,
                                       const int& score) const
    {
        if(logisticService == nullptr)
            return "Logistic controller not injected";
        auto targetRow = logisticService->suggestTargetRow(score,0);
        return targetRow;
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

#endif // ASSEMBLEDARTSSCORETURNVALUES_H
