#ifndef ASSEMBLEJSONFROMDARTSTOURNAMENTMODELS_H
#define ASSEMBLEJSONFROMDARTSTOURNAMENTMODELS_H
#include "dartstournament.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "icreatejsonfrommodels.h"
class CreateJsonFromDartsTournaments :
        public ICreateJsonFromModels
{
public:
    virtual QByteArray toJson(const QVector<const IModel<QUuid>*> &models) const override
    {
        QJsonArray arr = createJsonArray(models);
        QJsonObject obj = createJsonObject(arr);
        return createJsonByteArray(obj);
    }
private:
    QJsonArray createJsonArray(const QVector<const IModel<QUuid> *> &models) const
    {
        QJsonArray arr;
        for (const auto& model : models)
            arr << createJsonObjectByModel(model);
        return arr;
    }
    QJsonObject createJsonObjectByModel(const IModel<QUuid>* tournamentModel) const
    {
        auto model = dynamic_cast<const AbstractDartsTournament*>(tournamentModel);
        QJsonObject obj;
        obj["id"] = model->id().toString(QUuid::WithoutBraces);
        obj["title"] = model->title();
        obj["gameMode"] = model->gameMode();
        obj["keyPoint"] = model->keyPoint();
        obj["displayHint"] = model->displayHint();
        obj["inputHint"] = model->inputHint();
        obj["winnerId"] = model->winnerId().toString(QUuid::WithoutBraces);
        obj["winnerName"] = model->winnerName();
        obj["assignedPlayerIds"] = createJsonArrayFromPlayerIds(tournamentModel);
        obj["assignedPlayerNames"] = createJsonArrayFromPlayerNames(tournamentModel);
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
    QJsonArray createJsonArrayFromPlayerIds(const IModel<QUuid> *model) const
    {
        auto tournamentModel = dynamic_cast<const ITournament*>(model);
        QJsonArray arr;
        for (const auto& assignedPlayerId : tournamentModel->assignedPlayerIds())
            arr << assignedPlayerId.toString(QUuid::WithoutBraces);
        return arr;
    }
    QJsonArray createJsonArrayFromPlayerNames(const IModel<QUuid> *model) const
    {
        auto tournamentModel = dynamic_cast<const ITournament*>(model);
        QJsonArray arr;
        for (const auto& assignedPlayerName : tournamentModel->assignedPlayerNames())
            arr << assignedPlayerName;
        return arr;
    }
};
#endif // ASSEMBLEJSONFROMDARTSTOURNAMENTMODELS_H
