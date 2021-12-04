#ifndef DCPLAYERSTATSJSONBUILDER_H
#define DCPLAYERSTATSJSONBUILDER_H
#include "DartsController/PlayerStatsSLAs/dcplayerstats.h"
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"
class DCPlayerStatsJsonBuilder : public IDCModelJsonBuilder<const DCPlayerStats&>
{
public:
    virtual void setJsonValues(QJsonObject &obj, Model playerStat) const override
    {
        obj["middleValue"] = playerStat.middle;
        obj["currentMinimum"] = playerStat.min;
        obj["currentMaximum"] = playerStat.max;
    }
};

#endif // DCPLAYERSTATSJSONBUILDER_H
