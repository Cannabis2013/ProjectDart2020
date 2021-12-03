#ifndef DSCVALUESBUILDER_H
#define DSCVALUESBUILDER_H
#include "DartsController/DCTurnValuesSLAs/abstractdcturnvalues.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
class DSCValuesBuilder : public AbstractDCTurnValues
{
public:
    DSCValuesBuilder(AbstractDCIdxCtrl *indexController, AbstractDCScoresCtx *scoresModels,
                     const IDCFinishBuilder *logisticService = nullptr)
    {
        setIndexController(indexController);
        setScoreModels(scoresModels);
        setLogisticService(logisticService);
    }
    DCTurnValues turnValues() const override
    {
        auto scores = scoreModels()->scores();
        DCTurnValues model;
        auto index = indexController()->index();
        auto scoreModel = scoreModels()->scores().at(index.setIndex);
        model.canUndo = index.turnIndex > 0;
        model.canRedo = index.turnIndex < index.totalTurns;
        model.roundIndex = index.roundIndex;
        model.setIndex = index.setIndex;
        model.attemptIndex = index.attemptIndex;
        model.targetRow = createRowSuggestionByScore(logisticService(),scoreModel.remScore);
        model.playerName = scoreModel.name;
        return model;
    }
private:
    QString createRowSuggestionByScore(const IDCFinishBuilder* logisticService,
                                       const int& score) const
    {
        if(logisticService == nullptr)
            return "Logistic controller not injected";
        auto targetRow = logisticService->suggestTargetRow(score,0);
        return targetRow;
    }
};

#endif // ASSEMBLEDARTSSCORETURNVALUES_H
