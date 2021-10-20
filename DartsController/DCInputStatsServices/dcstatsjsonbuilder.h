#ifndef DCSTATSJSONBUILDER_H
#define DCSTATSJSONBUILDER_H

#include "DartsController/DCInputStatsSLAs/dcinputstats.h"
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"

class DCStatsJsonBuilder : public IDCModelJsonBuilder<DCInputStat>
{
public:
    virtual void json(QJsonObject &obj, const Model &model) const override
    {
        obj["average"] = model.average;
        obj["lowerValue"] = model.lowest;
        obj["upperValue"] = model.highest;
    }
};

#endif // DCSTATSJSONBUILDER_H
