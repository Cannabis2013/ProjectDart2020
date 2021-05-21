#ifndef ADDWINNERNAMETOTOURNAMENTJSON_H
#define ADDWINNERNAMETOTOURNAMENTJSON_H

#include "ibinaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class AddWinnerNameToTournamentJson :
        public IBinaryService<const QByteArray&,const QString&, QByteArray>
{
public:
    QByteArray service(const QByteArray& json,const QString& name) override
    {
        auto document = QJsonDocument::fromJson(json);
        auto jsonObject = document.object();
        jsonObject["winnerName"] = name;
        auto newDocument = QJsonDocument(jsonObject);
        auto newJson = newDocument.toJson();
        return newJson;
    }
};

#endif // ADDWINNERNAMETOTOURNAMENTJSON_H
