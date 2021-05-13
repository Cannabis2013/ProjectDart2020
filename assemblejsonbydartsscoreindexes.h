#ifndef ASSEMBLEJSONFROMDARTSSCOREINDEXES_H
#define ASSEMBLEJSONFROMDARTSSCOREINDEXES_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "idartsscoreindexes.h"

class AssembleJsonByDartsScoreIndexes :
        public IUnaryService<const IDartsScoreIndexes*,QByteArray>
{
public:
    QByteArray service(const IDartsScoreIndexes* indexes) override
    {
        QJsonObject jsonObject;
        jsonObject["totalTurns"] = indexes->totalTurns();
        jsonObject["turnIndex"]  = indexes->turnIndex();
        jsonObject["roundIndex"] = indexes->roundIndex();
        jsonObject["setIndex"] = indexes->setIndex();
        auto json = QJsonDocument(jsonObject).toJson();
        return json;
    }
};

#endif // ASSEMBLEJSONFROMDARTSSCOREINDEXES_H
