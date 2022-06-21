#include "gettournamentasjson.h"
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <quuid.h>
#include <DartsModelsContext/Contracts/dartsmodelsservices.h>
#include <DartsModelsContext/Contracts/Model/imodel.h>

QByteArray GetTournamentAsJson::tournamentToJson(const QUuid &ID, const DartsModelsServices *services) const
{
        auto converter = services->tournamentServices()->dartsConverter();
        auto tournament = getTournamentByID(ID,services);
        auto json = converter->convert(tournament);
        return toByteArray(json);
}

QByteArray GetTournamentAsJson::tournamentToJson(const QString &ID, const DartsModelsServices *services) const
{
        auto cvtr = services->tournamentServices()->dartsConverter();
        auto tournament = getTournamentByID(QUuid::fromString(ID),services);
        auto json = cvtr->convert(tournament);
        return toByteArray(json);
}

GetTournamentAsJson::ByteArray GetTournamentAsJson::tournamentToJson(const int &index, const DartsModelsServices *services) const
{
        auto cvtr = services->tournamentServices()->dartsConverter();
        auto dbContext = services->tournamentServices()->dbContext();
        auto tournament = dbContext->model(index);
        auto json = cvtr->convert(tournament);
        return toByteArray(json);
}

GetTournamentAsJson::Model *GetTournamentAsJson::getTournamentByID(const QUuid &ID, const DartsModelsServices *services) const
{
        auto dbContext = services->tournamentServices()->dbContext();
        auto models = dbContext->models();
        for (const auto &model : qAsConst(models)) {
                if(model->id() == ID)
                        return model;
        }
        return nullptr;
}

QJsonObject GetTournamentAsJson::fromByteArray(const QByteArray &byteArray) const
{
    return QJsonDocument::fromJson(byteArray).object();
}

QByteArray GetTournamentAsJson::toByteArray(const QJsonObject &obj) const
{
    auto document = QJsonDocument(obj);
    auto json = document.toJson();
    return json;
}

QByteArray GetTournamentAsJson::toByteArray(const QJsonArray &arr) const
{
    auto document = QJsonDocument(arr);
    auto json = document.toJson();
    return json;
}
