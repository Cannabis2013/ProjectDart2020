#ifndef DCTURNVALUESJSONBUILDER_H
#define DCTURNVALUESJSONBUILDER_H
#include "dcturnvalues.h"
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"
class DCTurnValuesJsonBuilder : public IDCModelJsonBuilder<const DCTurnValues&>
{
public:
    virtual void setJsonValues(QJsonObject &obj, Model turnValues) const override
    {
        obj["currentRoundIndex"] = turnValues.roundIndex;
        obj["currentSetIndex"] = turnValues.setIndex;
        obj["currentAttemptIndex"] = turnValues.attemptIndex;
        obj["canUndo"] = turnValues.canUndo;
        obj["canRedo"] = turnValues.canRedo;
        obj["finishCandidate"] = turnValues.targetRow;
        obj["currentPlayerName"] = turnValues.playerName;
        obj["inGame"] = turnValues.inGame;
    }
};

#endif // DCTURNVALUESJSONBUILDER_H
