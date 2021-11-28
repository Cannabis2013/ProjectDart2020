#ifndef DCREQIDXJSONBUILDER_H
#define DCREQIDXJSONBUILDER_H
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsController/DCIndexSLAs/dcindex.h"
class DCReqIdxJsonBuilder : public IDCModelJsonBuilder<DCIndex>
{
public:
    virtual void setJsonValues(QJsonObject &obj, Model index) const override
    {
        obj["reqTotalTurns"] = index.totalTurns;
        obj["reqTurnIndex"] = index.turnIndex;
        obj["reqRoundIndex"] = index.roundIndex;
        obj["reqSetIndex"] = index.setIndex;
        obj["reqAttemptIndex"] = index.attemptIndex;
    }
};

#endif // DCREQIDXJSONBUILDER_H
