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
    QJsonObject createJsonObjectByModel(const ITournament* tournamentModel) const
    {
        auto model = dynamic_cast<const IDartsTournament*>(tournamentModel);
        QJsonObject obj;
        obj["id"] = model->id().toString(QUuid::WithoutBraces);
        obj["title"] = model->title();
        obj["gameMode"] = model->gameMode();
        obj["attempts"] = model->attempts();
        obj["keyPoint"] = model->keyPoint();
        obj["displayHint"] = model->displayHint();
        obj["inputHint"] = model->inputHint();
        obj["winnerId"] = model->winnerId().toString(QUuid::WithoutBraces);
        obj["terminalKeyCode"] = model->terminalKeyCode();
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
    QJsonArray createJsonArrayFromPlayerIds(const ITournament *model) const
    {
        QJsonArray arr;
        for (const auto& assignedPlayerId : model->assignedPlayerIds())
            arr << assignedPlayerId.toString(QUuid::WithoutBraces);
        return arr;
    }
    QJsonArray createJsonArrayFromPlayerNames(const ITournament *model) const
    {
        QJsonArray arr;
        for (const auto& assignedPlayerName : model->assignedPlayerNames())
            arr << assignedPlayerName;
        return arr;
    }
};
#endif // ASSEMBLEJSONFROMDARTSTOURNAMENTMODELS_H
