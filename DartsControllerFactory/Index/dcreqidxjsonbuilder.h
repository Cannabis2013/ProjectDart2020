#ifndef DCREQIDXJSONBUILDER_H
#define DCREQIDXJSONBUILDER_H
#include "DCJsonSLAs/idcmodeljsonbuilder.h"
#include "Models/dcindex.h"
class DCReqIdxJsonBuilder : public IDCModelJsonBuilder<DCIndex>
{
public:
    virtual void setJsonValues(QJsonObject &obj, Model index) const override
    {
        obj["reqTotalTurns"] = index.totalTurns;
        obj["reqTurnIndex"] = index.turnIndex;
        obj["reqRoundIndex"] = index.roundIndex;
        obj["reqSetIndex"] = index.playerIndex;
        obj["reqAttemptIndex"] = index.attemptIndex;
    }
};

#endif // DCREQIDXJSONBUILDER_H
