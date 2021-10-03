#ifndef DPCINDEXESTOJSON_H
#define DPCINDEXESTOJSON_H
#include "DartsController/DCIndexSLAs/idcindexestojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
class DPCIndexesToJson : public IDCIndexesToJson
{
public:
    virtual void toJson(QJsonObject &obj, const DCContext::IDCIndexes *indexes, const IDCIndexesJsonKeys *keys) const override
    {
        obj[keys->totalTurns()] = indexes->totalTurns();
        obj[keys->turnIndex()] = indexes->turnIndex();
        obj[keys->roundIndex()] = indexes->roundIndex();
        obj[keys->setIndex()] = indexes->setIndex();
        obj[keys->attemptIndex()] = indexes->attemptIndex();
    }
};
#endif // DPCINDEXESTOJSON_H
