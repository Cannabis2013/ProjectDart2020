#ifndef DMCINDEXESTOJSON_H
#define DMCINDEXESTOJSON_H

#include "DartsModelsContext/DMCIndexesSLAs/idartsindexestojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class DMCIndexesToJson : public IDartsIndexesToJson
{
public:
    virtual QByteArray toJson(const IDartsIndexes *indexes) const override
    {
        QJsonObject jsonObject;
        jsonObject["totalTurns"] = indexes->totalTurns();
        jsonObject["turnIndex"]  = indexes->turnIndex();
        jsonObject["roundIndex"] = indexes->roundIndex();
        jsonObject["setIndex"] = indexes->setIndex();
        jsonObject["attemptIndex"] = indexes->attemptIndex();
        auto json = QJsonDocument(jsonObject).toJson();
        return json;
    }
};
#endif
