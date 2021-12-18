#ifndef DSCVALUESBUILDER_H
#define DSCVALUESBUILDER_H
#include "DCTurnValuesSLAs/abstractdcturnvalues.h"
#include "DCTurnValuesServices/dcturnvalues.h"
class DSCValuesBuilder : public AbstractDCTurnValues
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
#endif // ASSEMBLEDARTSSCORETURNVALUES_H
