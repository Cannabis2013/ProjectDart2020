#ifndef DCINPUTJSONBUILDER_H
#define DCINPUTJSONBUILDER_H

#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"

class DCInputJsonBuilder : public IDCModelJsonBuilder<DCInput>
{
public:
    virtual void json(QJsonObject &obj, const Model &input) const override
    {
        obj["point"] = input.point;
        obj["modKeyCode"] = input.modKeyCode;
        obj["score"] = input.score;
        obj["inputPlayerId"] = input.playerId.toString(QUuid::WithoutBraces);
        obj["inputPlayerName"] = input.playerName;
        obj["totalScore"] = input.remainingScore;
    }
};

#endif // DCINPUTJSONBUILDER_H
