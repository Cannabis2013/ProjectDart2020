#include "dartsconverttojson.h"
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <quuid.h>
#include "SLAs/dartsmodelsservices.h"

DartsConvertToJson::DartsConvertToJson(DartsModelsServices *services): _services(services)
{
    _cvtr = _services->tournamentServices()->dartsConverter();
    _dartsDb = _services->tournamentServices()->dartsDbCtx();
}

QByteArray DartsConvertToJson::fromTournament(const QUuid &ID) const
{
    auto tournament = getTournamentByID(ID);
    auto json = _cvtr->create(tournament);
    return toByteArray(json);
}

QByteArray DartsConvertToJson::fromTournament(const QString &ID) const
{
    auto tournament = getTournamentByID(QUuid::fromString(ID));
    auto json = _cvtr->create(tournament);
    return toByteArray(json);
}

DartsConvertToJson::ByteArray DartsConvertToJson::fromTournament(const int &index) const
{
    auto tournament = _dartsDb->model(index);
    auto json = _cvtr->create(tournament);
    return toByteArray(json);
}

QByteArray DartsConvertToJson::fromTournaments() const
{
    auto tournaments = _dartsDb->models();
    auto arr = toJsonArray(tournaments);
    return toByteArray(arr);
}

DartsConvertToJson::Model *DartsConvertToJson::getTournamentByID(const QUuid &ID) const
{
    auto models = _dartsDb->models();
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

QJsonArray DartsConvertToJson::toJsonArray(const QVector<IModel<QUuid> *> &models) const
{
    QJsonArray arr;
    for (auto& model : models)
        arr << _cvtr->create(model);
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
