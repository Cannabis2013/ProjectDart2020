#ifndef GETTOURNAMENTIDBYJSON_H
#define GETTOURNAMENTIDBYJSON_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class GetTournamentIdByJson : public
        IUnaryService<const QByteArray&, QUuid>
{
public:
    QUuid service(const QByteArray& json) override
    {
         auto document = QJsonDocument::fromJson(json);
         auto jsonObject = document.object();
         auto tournamentStringId = jsonObject.value("tournamentId").toString();
         auto tournamentId = QUuid::fromString(tournamentStringId);
         return tournamentId;
    }
};

#endif // GETTOURNAMENTIDBYJSON_H
