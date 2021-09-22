#ifndef DPCINPUTSTOJSON_H
#define DPCINPUTSTOJSON_H

#include "idcinputstojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
class DPCInputsToJson : public IDCInputsToJson
{
public:
    QByteArray createJson(DCContext::IDCInputModel* model) const override
    {
        return toByteArray(toObject(model));
    }
    QByteArray createJson(const QVector<DCContext::IDCInputModel*>& inputModels) const override
    {
        return toByteArray(toArray(inputModels));
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
        obj["point"] = model->point();
        obj["modKeyCode"] = model->modKeyCode();
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


#endif // DPCINPUTTOJSON_H
