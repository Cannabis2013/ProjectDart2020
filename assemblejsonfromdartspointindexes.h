#ifndef ASSEMBLETOURNAMENTJSONOBJECTFROMDARTSINDEXES_H
#define ASSEMBLETOURNAMENTJSONOBJECTFROMDARTSINDEXES_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "qvector.h"
#include "idartspointindexes.h"

namespace DartsModelsContext {
    class AssembleJsonFromDartsPointIndexes :
            public IUnaryService<const IDartsPointIndexes*,QByteArray>
    {
    public:
        QByteArray service(const IDartsPointIndexes* indexes) override
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


#endif // ASSEMBLETOURNAMENTJSONOBJECTFROMDARTSINDEXES_H
