#ifndef DPCINPUTSTOJSON_H
#define DPCINPUTSTOJSON_H

#include "DartsController/DCInputSLAs/idcinputstojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
class DPCInputsToJson : public IDCInputsToJson
{
public:
    QJsonObject createJson(DCContext::IDCInputModel* model, const IDCInputJsonKeys *inputKeys) const override
    {
        return toObject(model,inputKeys);
    }
    QJsonArray createJson(const QVector<DCContext::IDCInputModel*>& inputModels, const IDCInputJsonKeys *inputKeys) const override
    {
        return toArray(inputModels,inputKeys);
    }
private:
    QJsonArray toArray(const QVector<DCContext::IDCInputModel*> &inputModels, const IDCInputJsonKeys *inputKeys) const
    {
        QJsonArray arr;
        for (const auto& inputModel : inputModels)
            arr << toObject(inputModel,inputKeys);
        return arr;
    }
    QJsonObject toObject(const DCContext::IDCInputModel *model, const IDCInputJsonKeys *inputKeys) const
    {
        QJsonObject obj;
        obj[inputKeys->tournamentId()] = model->tournamentId().toString(QUuid::WithoutBraces);
        obj[inputKeys->point()] = model->point();
        obj[inputKeys->modKeyCode()] = model->modKeyCode();
        obj[inputKeys->score()] = model->score();
        obj[inputKeys->playerId()] = model->playerId().toString(QUuid::WithoutBraces);
        obj[inputKeys->playerName()] = model->playerName();
        obj[inputKeys->totalScore()] = model->totalScore();
        return obj;
    }
};


#endif // DPCINPUTTOJSON_H
