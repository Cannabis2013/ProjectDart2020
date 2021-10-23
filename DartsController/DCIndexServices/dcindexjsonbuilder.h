#ifndef DCINDEXJSONBUILDER_H
#define DCINDEXJSONBUILDER_H
#include "dcindex.h"
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"
class DCIndexJsonBuilder : public IDCModelJsonBuilder<DCIndex>
{
public:
    virtual void setJsonValues(QJsonObject &obj, const Model &indexes) const override
    {
        obj["totalTurns"] = indexes.totalTurns;
        obj["turnIndex"] = indexes.turnIndex;
        obj["roundIndex"] = indexes.roundIndex;
        obj["setIndex"] = indexes.setIndex;
        obj["attemptIndex"] = indexes.attemptIndex;
    }
};

#endif // DCINDEXESJSONBUILDER_H
