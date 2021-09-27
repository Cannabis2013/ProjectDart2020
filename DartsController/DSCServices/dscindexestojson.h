#ifndef DSCINDEXESTOJSON_H
#define DSCINDEXESTOJSON_H
#include "DartsController/DCIndexSLAs/idcindexestojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
class DSCIndexesToJson : public IDCIndexesToJson
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
        return obj;
    }
};
#endif // DSCINDEXESTOJSON_H
