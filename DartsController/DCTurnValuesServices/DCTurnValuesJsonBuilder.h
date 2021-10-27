#ifndef DCTURNVALUESJSONBUILDER_H
#define DCTURNVALUESJSONBUILDER_H

#include "dcturnvalues.h"
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"

class DCTurnValuesJsonBuilder : public IDCModelJsonBuilder<DCTurnValues>
{
public:
    virtual void setJsonValues(QJsonObject &obj, const Model &turnValues) const override
    {
        obj["currentRoundIndex"] = turnValues.roundIndex;
        obj["currentSetIndex"] = turnValues.setIndex;
        obj["currentAttemptIndex"] = turnValues.attemptIndex;
        obj["canUndo"] = turnValues.canUndo;
        obj["canRedo"] = turnValues.canRedo;
        obj["suggestedFinish"] = turnValues.targetRow;
        obj["currentPlayerName"] = turnValues.playerName;
        obj["inGame"] = turnValues.inGame;
    }
};

#endif // DCTURNVALUESJSONBUILDER_H
