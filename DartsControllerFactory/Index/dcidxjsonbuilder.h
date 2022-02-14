#ifndef DCIDXJSONBUILDER_H
#define DCIDXJSONBUILDER_H
#include "DCJsonSLAs/idcmodeljsonbuilder.h"
#include "Models/dcindex.h"
class DCIdxJsonBuilder : public IDCModelJsonBuilder<DCIndex>
{
public:
    virtual void setJsonValues(QJsonObject &obj, Model index) const override
    {
        obj["totalTurns"] = index.totalTurns;
        obj["turnIndex"] = index.turnIndex;
        obj["roundIndex"] = index.roundIndex;
        obj["setIndex"] = index.playerIndex;
        obj["attemptIndex"] = index.attemptIndex;
    }
};

#endif // DCINDEXESJSONBUILDER_H
