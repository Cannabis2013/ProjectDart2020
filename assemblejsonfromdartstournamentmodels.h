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
        for (const auto& model : models) {
            auto obj = assembleJsonObjectFromModel(model);
            arr << obj;
        }
        jsonObject["DartsTournaments"] = arr;
        return jsonObject;
    }
private:
    QJsonObject assembleJsonObjectFromModel(const IDartsTournament* model)
    {
        QJsonObject jsonObject;
        jsonObject["id"] = model->id().toString(QUuid::WithoutBraces);
        jsonObject["title"] = model->title();
        jsonObject["gameMode"] = model->gameMode();
        jsonObject["attempts"] = model->attempts();
        jsonObject["keyPoint"] = model->keyPoint();
        jsonObject["terminalKeyCode"] = model->terminalKeyCode();
        jsonObject["winnerId"] = model->winnerId().toString(QUuid::WithoutBraces);
        jsonObject["displayHint"] = model->displayHint();
        jsonObject["inputHint"] = model->inputHint();
        jsonObject["assignedPlayerIds"] = assembleJSonArrayFromListOfQuuids(model->assignedPlayerIdentities());
        return jsonObject;
    }
    QJsonArray assembleJSonArrayFromListOfQuuids(const QVector<QUuid>& uuids)
    {
        QJsonArray arr;
        for (const auto& uuid : uuids) {
            auto stringUuid = uuid.toString(QUuid::WithoutBraces);
            arr << stringUuid;
        }
        return arr;
    }
};
#endif // ASSEMBLEJSONFROMDARTSTOURNAMENTMODELS_H
