#ifndef ASSEMBLETOURNAMENTJSONOBJECTFROMDARTSINDEXES_H
#define ASSEMBLETOURNAMENTJSONOBJECTFROMDARTSINDEXES_H

#include "iunaryservice.h"
#include "qjsonobject.h"
#include "qvector.h"

class AssembleJsonDartsIndexes :
        public IUnaryService<const QVector<int>&,QJsonObject>
{
public:
    QJsonObject service(const QVector<int>& indexes) override
    {
        QJsonObject jsonObject;
        jsonObject["totalTurns"] = indexes.at(0);
        jsonObject["turns"]  = indexes.at(1);
        jsonObject["roundIndex"] = indexes.at(2);
        jsonObject["setIndex"] = indexes.at(3);
        jsonObject["attemptIndex"] = indexes.at(4);
        return jsonObject;
    }
};

#endif // ASSEMBLETOURNAMENTJSONOBJECTFROMDARTSINDEXES_H
