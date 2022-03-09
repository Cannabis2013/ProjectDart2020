#include "dartsconverttojson.h"
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <quuid.h>
#include "SLAs/dartsmodelsservices.h"

QByteArray DartsConvertToJson::tournamentToJson(const QUuid &ID, const DartsModelsServices *services) const
{
    auto cvtr = services->tournamentServices()->dartsConverter();
    auto tournament = getTournamentByID(ID,services);
    auto json = cvtr->create(tournament);
    return toByteArray(json);
}

QByteArray DartsConvertToJson::tournamentToJson(const QString &ID, const DartsModelsServices *services) const
{
    auto cvtr = services->tournamentServices()->dartsConverter();
    auto tournament = getTournamentByID(QUuid::fromString(ID),services);
    auto json = cvtr->create(tournament);
    return toByteArray(json);
}

DartsConvertToJson::ByteArray DartsConvertToJson::tournamentToJson(const int &index, const DartsModelsServices *services) const
{
    auto cvtr = services->tournamentServices()->dartsConverter();
    auto dbContext = services->tournamentServices()->dbContext();
    auto tournament = dbContext->model(index);
    auto json = cvtr->create(tournament);
    return toByteArray(json);
}

QByteArray DartsConvertToJson::tournamentsToJson(const DartsModelsServices *services) const
{
    auto dbContext = services->tournamentServices()->dbContext();
    auto tournaments = dbContext->models();
    auto arr = toJsonArray(tournaments,services);
    return toByteArray(arr);
}

DartsConvertToJson::Model *DartsConvertToJson::getTournamentByID(const QUuid &ID, const DartsModelsServices *services) const
{
    auto dbContext = services->tournamentServices()->dbContext();
    auto models = dbContext->models();
    for (const auto &model : qAsConst(models)) {
        if(model->id() == ID)
            return model;
    }
    return nullptr;
}

QJsonObject DartsConvertToJson::fromByteArray(const QByteArray &byteArray) const
{
    return QJsonDocument::fromJson(byteArray).object();
}

QJsonArray DartsConvertToJson::toJsonArray(const QVector<IModel<QUuid> *> &models, const DartsModelsServices *services) const
{
    auto cvtr = services->tournamentServices()->dartsConverter();
    QJsonArray arr;
    for (auto& model : models)
        arr << cvtr->create(model);
    return arr;
}

QByteArray DartsConvertToJson::toByteArray(const QJsonObject &obj) const
{
    auto document = QJsonDocument(obj);
    auto json = document.toJson();
    return json;
}

QByteArray DartsConvertToJson::toByteArray(const QJsonArray &arr) const
{
    auto document = QJsonDocument(arr);
    auto json = document.toJson();
    return json;
}
