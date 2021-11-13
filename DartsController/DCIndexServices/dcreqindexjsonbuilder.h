#ifndef DCREQINDEXJSONBUILDER_H
#define DCREQINDEXJSONBUILDER_H
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
class DCReqIndexJsonBuilder : public IDCModelJsonBuilder<IDartsIndex*>
{
public:
    virtual void setJsonValues(QJsonObject &obj, Model index) const override
    {
        obj["reqTotalTurns"] = index->totalTurns();
        obj["reqTurnIndex"] = index->turnIndex();
        obj["reqRoundIndex"] = index->roundIndex();
        obj["reqSetIndex"] = index->setIndex();
        obj["reqAttemptIndex"] = index->attemptIndex();
    }
};

#endif // DCREQINDEXJSONBUILDER_H
