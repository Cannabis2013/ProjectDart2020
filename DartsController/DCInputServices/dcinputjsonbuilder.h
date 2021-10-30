#ifndef DCINPUTJSONBUILDER_H
#define DCINPUTJSONBUILDER_H
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"
class DCInputJsonBuilder : public IDCModelJsonBuilder<DCInput>
{
public:
    virtual void setJsonValues(QJsonObject &obj, const Model &input) const override
    {
        obj["point"] = input.point;
        obj["modKeyCode"] = input.modKeyCode;
        obj["score"] = input.score;
        obj["remainingScore"] = input.remainingScore;
        obj["inputPlayerId"] = input.playerId.toString(QUuid::WithoutBraces);
        obj["inputPlayerName"] = input.playerName;
        obj["totalScore"] = input.remainingScore;
        obj["middleValue"] = input.middle;
        obj["minimumValue"] = input.min;
        obj["maximumValue"] = input.max;
        obj["inGame"] = input.inGame;
        obj["approved"] = input.approved;
    }
};

#endif // DCINPUTJSONBUILDER_H
