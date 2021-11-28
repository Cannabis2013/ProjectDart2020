#ifndef DCIDXJSONBUILDER_H
#define DCIDXJSONBUILDER_H
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsController/DCIndexSLAs/dcindex.h"
class DCIdxJsonBuilder : public IDCModelJsonBuilder<DCIndex>
{
public:
    virtual void setJsonValues(QJsonObject &obj, Model index) const override
    {
        obj["totalTurns"] = index.totalTurns;
        obj["turnIndex"] = index.turnIndex;
        obj["roundIndex"] = index.roundIndex;
        obj["setIndex"] = index.setIndex;
        obj["attemptIndex"] = index.attemptIndex;
    }
};

#endif // DCINDEXESJSONBUILDER_H
