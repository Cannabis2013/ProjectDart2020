#ifndef DARTSJSONBUILDER_H
#define DARTSJSONBUILDER_H
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "TournamentModelsSLAs/idartstournament.h"
#include "TournamentsDbSLAs/itournamentjsonbuilder.h"
class DartsJsonBuilder : public IDartsJsonBuilder<IModel<QUuid>,QByteArray>
{
public:
    virtual QByteArray create(IModel<QUuid> *model) const override
    {
        return toByteArray(toJsonObject(dynamic_cast<IDartsTournament*>(model)));
    }
    virtual QByteArray create(const QVector<Model*> &models) const override
    {
        return toByteArray(toJsonArray(models));
    }
    virtual QByteArray create(const QVector<Model*>& models, QByteArray &byteArray) const override
    {
        auto json = fromByteArray(byteArray);
        json["TournamentModels"] = toJsonArray(models);
        return toByteArray(json);
    }
private:
    QJsonObject fromByteArray(const QByteArray &byteArray) const
    {
        return QJsonDocument::fromJson(byteArray).object();
    }
    QJsonArray toJsonArray(const QVector<IModel<QUuid> *> &models) const
    {
        QJsonArray arr;
        for (auto& model : models)
            arr << toJsonObject(dynamic_cast<IDartsTournament*>(model));
        return arr;
    }
    QJsonObject toJsonObject(IDartsTournament* model) const
    {
        QJsonObject obj;
        obj["tournamentId"] = model->id().toString(QUuid::WithoutBraces);
        obj["title"] = model->title();
        obj["gameMode"] = model->gameMode();
        obj["initRemScore"] = model->initialRemaining();
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
        auto tournament = dynamic_cast<IDartsTournament*>(model);
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
