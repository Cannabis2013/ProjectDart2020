#ifndef DPCTURNVALUESBUILDER_H
#define DPCTURNVALUESBUILDER_H
#include "DartsController/DCTurnValuesSLAs/abstractdcturnvalues.h"
#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
#include "DartsController/DCIndexSLAs/idcidxctrl.h"
#include "DartsController/DCFinishesSLAs/idcfinishbuilder.h"
class DPCTurnValuesBuilder : public AbstractDCTurnValues
{
public:
    DCTurnValues create(const DCIndex &index, const DCPlayer &player, const QString &finish) const override
    {
        DCTurnValues model;
        model.canUndo = index.turnIndex > 0;
        model.canRedo = index.turnIndex < index.totalTurns;
        model.roundIndex = index.roundIndex;
        model.setIndex = index.setIndex;
        model.attemptIndex = index.attemptIndex;
        model.targetRow = finish;
        model.playerName = player.name;
        return model;
    }
};
#endif // BUILDDARTSPOINTTURNVALUES_H
