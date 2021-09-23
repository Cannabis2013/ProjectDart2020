#ifndef DSCINDEXESTOJSON_H
#define DSCINDEXESTOJSON_H
#include "DCIndexSLAs/idcindexestojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
class DSCIndexesToJson : public IDCIndexesToJson
{
public:
    virtual QByteArray toJson(const DCContext::IDCIndexes *indexes) const override
    {
        return toByteArray(toJsonobject(indexes));
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
    QByteArray toByteArray(const QJsonObject &obj) const
    {
        return QJsonDocument(obj).toJson();
    }
};
#endif // DSCINDEXESTOJSON_H
