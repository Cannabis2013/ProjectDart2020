#ifndef DSCINPUTTOJSON_H
#define DSCINPUTTOJSON_H
#include "DCInputSLAs/idcinputstojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
class DSCInputToJson : public IDCInputsToJson
{
public:
    QByteArray createJson(DCContext::IDCInputModel* model) const override
    {
        QJsonObject obj = toObject(model);
        return toByteArray(obj);
    }
    QByteArray createJson(const QVector<DCContext::IDCInputModel*>& inputModels) const override
    {
        QJsonArray arr = toArray(inputModels);
        return toByteArray(arr);
    }
private:
    QJsonArray toArray(const QVector<DCContext::IDCInputModel*> &inputModels) const
    {
        QJsonArray arr;
        for (const auto& inputModel : inputModels)
            arr << toObject(inputModel);
        return arr;
    }
    QJsonObject toObject(const DCContext::IDCInputModel *model) const
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
