#ifndef DPCINDEXESTOJSON_H
#define DPCINDEXESTOJSON_H
#include "DartsController/DCIndexSLAs/idcindexestojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
class DPCIndexesToJson : public IDCIndexesToJson
{
public:
    virtual void toJson(QJsonObject &obj, const DCContext::IDCIndexes *indexes) const override
    {
        obj["totalTurns"] = indexes->totalTurns();
        obj["turnIndex"] = indexes->turnIndex();
        obj["roundIndex"] = indexes->roundIndex();
        obj["setIndex"] = indexes->setIndex();
        obj["attemptIndex"] = indexes->attemptIndex();
    }
};
#endif // DPCINDEXESTOJSON_H
