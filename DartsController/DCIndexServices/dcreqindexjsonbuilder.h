#ifndef DCREQINDEXJSONBUILDER_H
#define DCREQINDEXJSONBUILDER_H
#include "dcindex.h"
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"
class DCReqIndexJsonBuilder : public IDCModelJsonBuilder<DCIndex>
{
public:
    virtual void setJsonValues(QJsonObject &obj, const Model &model) const override
    {
        obj["reqTotalTurns"] = model.totalTurns;
        obj["reqTurnIndex"] = model.turnIndex;
        obj["reqRoundIndex"] = model.roundIndex;
        obj["reqSetIndex"] = model.setIndex;
        obj["reqAttemptIndex"] = model.attemptIndex;
    }
};

#endif // DCREQINDEXJSONBUILDER_H
