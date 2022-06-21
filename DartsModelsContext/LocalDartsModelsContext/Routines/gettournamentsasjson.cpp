#include "gettournamentsasjson.h"
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <DartsModelsContext/Contracts/dartsmodelsservices.h>

QByteArray GetTournamentsAsJson::tournamentsToJson(const DartsModelsServices *services) const
{
    auto dbContext = services->tournamentServices()->dbContext();
    auto tournaments = dbContext->models();
    auto arr = toJsonArray(tournaments,services);
    return toByteArray(arr);
}

QJsonArray GetTournamentsAsJson::toJsonArray(const QVector<IModel<QUuid> *> &models, const DartsModelsServices *services) const
{
    auto cvtr = services->tournamentServices()->dartsConverter();
    QJsonArray arr;
    for (auto& model : models)
        arr << cvtr->convert(model);
    return arr;
}

QByteArray GetTournamentsAsJson::toByteArray(const QJsonArray &arr) const
{
    auto document = QJsonDocument(arr);
    auto json = document.toJson();
    return json;
}
