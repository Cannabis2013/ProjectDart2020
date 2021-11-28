#ifndef DPCTURNVALUESBUILDER_H
#define DPCTURNVALUESBUILDER_H
#include "DartsController/DCTurnValuesSLAs/abstractdcturnvalues.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
#include "DartsController/DCIndexSLAs/abstractdcidxctrl.h"
#include "DartsController/DCFinishesSLAs/idcfinishbuilder.h"
class DPCTurnValuesBuilder : public AbstractDCTurnValues
{
public:
    DPCTurnValuesBuilder(AbstractDCIdxCtrl *indexController, AbstractDCScoresCtx *scoresModels,
                     const IDCFinishBuilder *logisticService = nullptr)
    {
        setIndexController(indexController);
        setScoreModels(scoresModels);
        setLogisticService(logisticService);
    }
    DCTurnValues turnValues() const override
    {
        DCTurnValues model;
        auto index = indexController()->index();
        auto scoreModel = scoreModels()->scores().at(index.setIndex);
        model.canUndo = index.turnIndex > 0;
        model.canRedo = index.turnIndex < index.totalTurns;
        model.roundIndex = index.roundIndex;
        model.setIndex = index.setIndex;
        model.attemptIndex = index.attemptIndex;
        model.targetRow = logisticService()->suggestTargetRow(scoreModel.remainingScore,index.attemptIndex);
        model.playerName = scoreModel.playerName;
        return model;
    }
};
#endif // BUILDDARTSPOINTTURNVALUES_H
