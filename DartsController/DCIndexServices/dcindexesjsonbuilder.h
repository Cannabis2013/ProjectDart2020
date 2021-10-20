#ifndef DCINDEXESJSONBUILDER_H
#define DCINDEXESJSONBUILDER_H

#include "dcindexes.h"
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"

class DCIndexesJsonBuilder : public IDCModelJsonBuilder<DCIndexes>
{
public:
    virtual void json(QJsonObject &obj, const Model &indexes) const override
    {
        obj["totalTurns"] = indexes.totalTurns;
        obj["turnIndex"] = indexes.turnIndex;
        obj["roundIndex"] = indexes.roundIndex;
        obj["setIndex"] = indexes.setIndex;
        obj["attemptIndex"] = indexes.attemptIndex;
    }
};

#endif // DCINDEXESJSONBUILDER_H
