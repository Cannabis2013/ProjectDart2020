#ifndef ASSEMBLEJSONFROMDARTSTOURNAMENTMODELS_H
#define ASSEMBLEJSONFROMDARTSTOURNAMENTMODELS_H
#include "dartstournament.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "icreatejsonfromdartstournaments.h"
class CreateJsonFromDartsTournaments :
        public ICreateJsonFromDartsTournaments
{
public:
    virtual QByteArray createJson(const QVector<const ITournament*> &models) const override
    {
        QJsonArray arr = createJsonArray(models);
        QJsonObject obj = createJsonObject(arr);
        return createJsonByteArray(obj);
    }
private:
    QJsonArray createJsonArray(const QVector<const ITournament *> &models) const
    {
        QJsonArray arr;
        for (const auto& model : models)
            arr << createJsonObjectByModel(model);
        return arr;
    }
    QJsonObject createJsonObjectByModel(const ITournament* model) const
    {
        auto json = model->toJson();
        auto document = QJsonDocument::fromJson(json);
        auto obj = document.object();
        return obj;
    }
    QJsonObject createJsonObject(const QJsonArray &arr) const
    {
        QJsonObject obj;
        obj["DartsTournaments"] = arr;
        return obj;
    }
    QByteArray createJsonByteArray(const QJsonObject &obj) const
    {
        auto document = QJsonDocument(obj);
        auto json = document.toJson();
        return json;
    }
};
#endif // ASSEMBLEJSONFROMDARTSTOURNAMENTMODELS_H
