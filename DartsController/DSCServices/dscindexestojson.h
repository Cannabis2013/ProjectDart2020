#ifndef DSCINDEXESTOJSON_H
#define DSCINDEXESTOJSON_H
#include "DartsController/DCIndexSLAs/idcindexestojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
class DSCIndexesToJson : public IDCIndexesToJson
{
public:
    virtual void toJson(QJsonObject &obj,const DCContext::IDCIndexes *indexes) const override
    {
        obj["totalTurns"] = indexes->totalTurns();
        obj["turnIndex"] = indexes->turnIndex();
        obj["roundIndex"] = indexes->roundIndex();
        obj["setIndex"] = indexes->setIndex();
    }
};
#endif // DSCINDEXESTOJSON_H
