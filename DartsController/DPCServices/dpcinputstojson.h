#ifndef DPCINPUTSTOJSON_H
#define DPCINPUTSTOJSON_H

#include "DartsController/DCInputSLAs/idcinputstojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
class DPCInputsToJson : public IDCInputsToJson
{
public:
    void setJsonValues(QJsonObject &obj, DCContext::IDCInputModel* model, const IDCInputJsonKeys *inputKeys) const override
    {
        obj[inputKeys->tournamentId()] = model->tournamentId().toString(QUuid::WithoutBraces);
        obj[inputKeys->point()] = model->point();
        obj[inputKeys->modKeyCode()] = model->modKeyCode();
        obj[inputKeys->score()] = model->score();
        obj[inputKeys->playerId()] = model->playerId().toString(QUuid::WithoutBraces);
        obj[inputKeys->playerName()] = model->playerName();
        obj[inputKeys->totalScore()] = model->totalScore();
    }
    void setJsonValues(QJsonArray &arr, const QVector<DCContext::IDCInputModel*>& inputModels, const IDCInputJsonKeys *inputKeys) const override
    {
        for (const auto& inputModel : inputModels)
        {
            QJsonObject obj;
            setJsonValues(obj,inputModel,inputKeys);
            arr << obj;
        }
    }
};


#endif // DPCINPUTTOJSON_H
