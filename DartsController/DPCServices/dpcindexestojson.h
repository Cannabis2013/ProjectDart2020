#ifndef DPCINDEXESTOJSON_H
#define DPCINDEXESTOJSON_H
#include "DartsController/DCIndexSLAs/idcindexestojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
class DPCIndexesToJson : public IDCIndexesToJson
{
public:
    virtual QJsonObject toJson(const DCContext::IDCIndexes *indexes) const override
    {
        return toJsonobject(indexes);
    }
private:
    QJsonObject toJsonobject(const DCContext::IDCIndexes *indexes) const
    {
        QJsonObject obj;
        obj["totalTurns"] = indexes->totalTurns();
        obj["turnIndex"] = indexes->turnIndex();
        obj["roundIndex"] = indexes->roundIndex();
        obj["setIndex"] = indexes->setIndex();
        obj["attemptIndex"] = indexes->attemptIndex();
        return obj;
    }
};
#endif // DPCINDEXESTOJSON_H
