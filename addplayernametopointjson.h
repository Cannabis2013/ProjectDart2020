#ifndef ADDPLAYERNAMETOPOINTJSON_H
#define ADDPLAYERNAMETOPOINTJSON_H

#include "idartsscoreinput.h"
#include "ibinaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class AddPlayerNameToJsonInputModel :
        public IBinaryService<const IDartsScoreInput*,
                              const QString&,
                              QByteArray>
{
public:
    QByteArray service(const IDartsScoreInput* dartsScore,const QString& playerName) override
    {
        QJsonObject jsonObject;
        jsonObject["score"] = dartsScore->score();
        jsonObject["hint"] = dartsScore->hint();
        jsonObject["playerId"] = dartsScore->playerId().toString(QUuid::WithoutBraces);
        jsonObject["playerName"] = playerName;
        jsonObject["roundIndex"] = dartsScore->roundIndex();
        jsonObject["setIndex"] = dartsScore->setIndex();
        jsonObject["tournamentId"] = dartsScore->tournamentId().toString(QUuid::WithoutBraces);
        auto document = QJsonDocument(jsonObject);
        auto json = document.toJson();
        return json;
    }
};
#endif // ADDPLAYERNAMETOPOINTJSON_H
