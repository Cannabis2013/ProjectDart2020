#ifndef CREATEJSONFROMDSCMODELS_H
#define CREATEJSONFROMDSCMODELS_H

#include "idcmodeltojson.h"

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "idcwinnerservice.h"

class CreateJsonFromDSCModels : public IDCModelToJson
{
public:
    QByteArray createJson(DCContext::IDCModel* model) const override
    {
        QJsonObject obj = toObject(model);
        return toByteArray(obj);
    }
    QByteArray createJson(const QVector<DCContext::IDCModel*>& inputModels) const override
    {
        QJsonArray arr = toArray(inputModels);
        return toByteArray(arr);
    }
private:
    QJsonArray toArray(const QVector<DCContext::IDCModel*> &inputModels) const
    {
        QJsonArray arr;
        for (const auto& inputModel : inputModels)
            arr << toObject(inputModel);
        return arr;
    }
    QJsonObject toObject(const DCContext::IDCModel *model) const
    {
        QJsonObject obj;
        obj["tournamentId"] = model->tournamentId().toString(QUuid::WithoutBraces);
        obj["score"] = model->score();
        obj["playerId"] = model->playerId().toString(QUuid::WithoutBraces);
        obj["playerName"] = model->playerName();
        obj["totalScore"] = model->totalScore();
        return obj;
    }
    QByteArray toByteArray(const QJsonObject &obj) const
    {
        auto document = QJsonDocument(obj);
        return document.toJson();
    }
    QByteArray toByteArray(const QJsonArray &arr) const
    {
        auto document = QJsonDocument(arr);
        return document.toJson();
    }
};
#endif // DARTSMULTIATTEMPTJSONSERVICE_H
