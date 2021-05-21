#ifndef ASSEMBLEJSONFROMDARTSTOURNAMENTMODELS_H
#define ASSEMBLEJSONFROMDARTSTOURNAMENTMODELS_H

#include "iunaryservice.h"
#include "dartstournament.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>

class AssembleJsonFromDartsTournamentModels :
        public IUnaryService<const QVector<const IDartsTournament*>&,QJsonObject>
{
public:
    QJsonObject service(const QVector<const IDartsTournament*>& models) override
    {
        QJsonObject jsonObject;
        QJsonArray arr;
        for (const auto& model : models)
            arr << createJsonObjectByModel(model);
        jsonObject["DartsTournaments"] = arr;
        return jsonObject;
    }
private:
    QJsonObject createJsonObjectByModel(const IDartsTournament* model)
    {
        auto json = model->toJson();
        auto document = QJsonDocument::fromJson(json);
        auto obj = document.object();
        return obj;
    }
};
#endif // ASSEMBLEJSONFROMDARTSTOURNAMENTMODELS_H
