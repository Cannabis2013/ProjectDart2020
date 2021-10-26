#ifndef DSCVALUESBUILDER_H
#define DSCVALUESBUILDER_H

#include "DartsController/DCTurnValuesSLAs/icreatedcturnvalues.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"

class DSCValuesBuilder : public ICreateDCTurnValues
{
public:
    DCTurnValues turnValues(const DCIndex &index, IDCScoreModels* scoresService,
                            const IDartsInputFinishes* logisticService) const override
    {
        auto scoreModels = scoresService->scores();
        DCTurnValues model;
        model.canUndo = index.turnIndex > 0;
        model.canRedo = index.turnIndex < index.totalTurns;
        model.roundIndex = index.roundIndex;
        model.setIndex = index.setIndex;
        model.attemptIndex = index.attemptIndex;
        model.targetRow = createRowSuggestionByScore(logisticService,scoreModels.at(model.setIndex).remainingScore);
        model.playerName = scoreModels.at(model.setIndex).playerName;
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
};

#endif // ASSEMBLEDARTSSCORETURNVALUES_H
