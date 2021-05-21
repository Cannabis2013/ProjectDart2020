#ifndef ASSEMBLEDARTSTOURNAMENTFROMJSONARRAY_H
#define ASSEMBLEDARTSTOURNAMENTFROMJSONARRAY_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "dartstournament.h"

class AssembleDartsTournamentsFromJsonArray :
        public IUnaryService<const QJsonObject&,QVector<const IDartsTournament*>>
{
public:
    QVector<const IDartsTournament*> service(const QJsonObject& json) override
    {
        using namespace DartsModelsContext;
        QVector<const IDartsTournament*> list;
        auto jsonArray = json.value("DartsTournaments").toArray();
        for (const auto& jsonValue : jsonArray) {
            auto jsonObject = jsonValue.toObject();
            auto model = DartsTournament::fromJsonObject(jsonObject);
            list << model;
        }
        return list;
    }
};

#endif // ASSEMBLEDARTSTOURNAMENTFROMJSONARRAY_H
