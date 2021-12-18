#ifndef DPCTURNVALUESBUILDER_H
#define DPCTURNVALUESBUILDER_H
#include "DCTurnValuesSLAs/abstractdcturnvalues.h"
#include "DCTurnValuesServices/dcturnvalues.h"
#include "DCIndexSLAs/idcidxctrl.h"
#include "DCFinishesSLAs/idcfinishbuilder.h"
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
