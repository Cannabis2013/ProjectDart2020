#ifndef DARTSJSONBUILDER_H
#define DARTSJSONBUILDER_H
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h"
#include "DartsModelsContext/TournamentsDbSLAs/itournamentjsonbuilder.h"
class DartsJsonBuilder : public IDartsJsonBuilder
{
public:
public:
    virtual QJsonObject tournamentJsonObject(IModel<QUuid> *model) const override
    {
        return toJsonObject(dynamic_cast<AbstractDartsTournament*>(model));
    }
    virtual QByteArray tournamentJson(IModel<QUuid> *model) const override
    {
        auto obj = toJsonObject(dynamic_cast<AbstractDartsTournament*>(model));
        return toByteArray(obj);
    }
    virtual QByteArray tournamentsjson(const QVector<IModel<QUuid>*> &models) const override
    {
        QJsonArray arr = toJsonArray(models);
        return toByteArray(arr);
    }
    virtual QJsonArray assignedPlayersJson(IModel<QUuid> *model) const override
    {
        return fromPlayerDetails(model);
    }
    virtual QJsonObject winnerDetailsJson(IModel<QUuid> *model) const override
    {
        auto tournament = dynamic_cast<ITournament*>(model);
        return toJsonObject(tournament->winnerId(),tournament->winnerName());
    }
private:
    QJsonArray toJsonArray(const QVector<IModel<QUuid> *> &models) const
    {
        QJsonArray arr;
        for (auto& model : models)
            arr << toJsonObject(dynamic_cast<AbstractDartsTournament*>(model));
        return arr;
    }
    QJsonObject toJsonObject(AbstractDartsTournament* model) const
    {
        QJsonObject obj;
        obj["tournamentId"] = model->id().toString(QUuid::WithoutBraces);
        obj["title"] = model->title();
        obj["gameMode"] = model->gameMode();
        obj["keyPoint"] = model->initialRemaining();
        obj["inputHint"] = model->inputHint();
        obj["winnerId"] = model->winnerId().toString(QUuid::WithoutBraces);
        obj["winnerName"] = model->winnerName();
        obj["assignedPlayerDetails"] = fromPlayerDetails(model);
        obj["totalTurns"] = model->totalTurns();
        obj["turnIndex"] = model->turnIndex();
        obj["roundIndex"] = model->roundIndex();
        obj["setIndex"] = model->setIndex();
        obj["attemptIndex"] = model->attemptIndex();
        return obj;
    }
    QByteArray toByteArray(const QJsonObject &obj) const
    {
        auto document = QJsonDocument(obj);
        auto json = document.toJson();
        return json;
    }
    QByteArray toByteArray(const QJsonArray &arr) const
    {
        auto document = QJsonDocument(arr);
        auto json = document.toJson();
        return json;
    }
    QJsonArray fromPlayerDetails(IModel<QUuid> *model) const
    {
        QJsonArray arr;
        auto tournament = dynamic_cast<ITournament*>(model);
        for (int i = 0; i <tournament->playerNames().count() ; ++i) {
            auto id = tournament->playerIds().at(i);
            auto name = tournament->playerNames().at(i);
            arr << toJsonObject(id,name);
        }
        return arr;
    }
    QJsonObject toJsonObject(const QUuid &id, const QString &name) const
    {
        QJsonObject obj;
        obj["playerId"] = id.toString(QUuid::WithoutBraces);
        obj["playerName"] = name;
        return obj;
    }
};
#endif // ASSEMBLEJSONFROMDARTSTOURNAMENTMODELS_H
