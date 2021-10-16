#ifndef DSCINPUTTOJSON_H
#define DSCINPUTTOJSON_H
#include "DartsController/DCInputSLAs/idcsetinputjsonvalues.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
class DSCInputToJson : public IDCSetInputJsonValues
{
public:
    void setValues(QJsonObject &obj, IDCInput* model) const override
    {
        obj["score"] = model->score();
        obj["inputPlayerId"] = model->playerId().toString(QUuid::WithoutBraces);
        obj["inputPlayerName"] = model->playerName();
        obj["totalScore"] = model->remainingScore();
    }
    void setValues(QJsonArray &arr, const QVector<IDCInput*>& inputModels) const override
    {
        for (const auto& inputModel : inputModels)
        {
            QJsonObject obj;
            setValues(obj,inputModel);
            arr << obj;
        }
    }
};
#endif // DARTSMULTIATTEMPTJSONSERVICE_H
