#ifndef DCINDEXJSONBUILDER_H
#define DCINDEXJSONBUILDER_H
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
class DCIndexJsonBuilder : public IDCModelJsonBuilder<IDartsIndex*>
{
public:
    virtual void setJsonValues(QJsonObject &obj, Model index) const override
    {
        obj["totalTurns"] = index->totalTurns();
        obj["turnIndex"] = index->turnIndex();
        obj["roundIndex"] = index->roundIndex();
        obj["setIndex"] = index->setIndex();
        obj["attemptIndex"] = index->attemptIndex();
    }
};

#endif // DCINDEXESJSONBUILDER_H
