#ifndef DCINPUTJSONBUILDER_H
#define DCINPUTJSONBUILDER_H
#include "DCJsonSLAs/idcmodeljsonbuilder.h"
#include "Models/dcinput.h"
class DCInputJsonBuilder : public IDCModelJsonBuilder<DCInput>
{
public:
    virtual void setJsonValues(QJsonObject &obj, Model input) const override
    {
        obj["point"] = input.point;
        obj["modKeyCode"] = input.modKeyCode;
        obj["score"] = input.score;
        obj["remainingScore"] = input.remScore;
        obj["inputPlayerName"] = input.playerName;
        obj["middleValue"] = input.mid;
        obj["minimumValue"] = input.min;
        obj["maximumValue"] = input.max;
        obj["inGame"] = input.inGame;
        obj["approved"] = input.approved;
    }
};
#endif // DCINPUTJSONBUILDER_H
