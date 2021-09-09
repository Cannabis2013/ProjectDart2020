#ifndef CREATEJSONFROMDARTSPOINTINDEXES_H
#define CREATEJSONFROMDARTSPOINTINDEXES_H

#include "idartsindexestojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
namespace ModelsContext {
    class CreateJsonFromDartsPointIndexes : public IDartsIndexesToJson
    {
    public:
        virtual QByteArray toJson(const IDartsPointIndexes *indexes) const override
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
}

#endif // CREATEJSONFROMDARTSPOINTINDEXES_H
