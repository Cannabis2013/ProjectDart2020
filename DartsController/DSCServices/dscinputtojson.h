#ifndef DSCINPUTTOJSON_H
#define DSCINPUTTOJSON_H
#include "DartsController/DCInputSLAs/idcinputjsoncontext.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
class DSCInputToJson : public IDCInputJsonContext
{
public:
    void setValues(QJsonObject &obj, DCContext::IDCInputModel* model) const override
    {
        obj["score"] = model->score();
        obj["inputPlayerId"] = model->playerId().toString(QUuid::WithoutBraces);
        obj["inputPlayerName"] = model->playerName();
        obj["totalScore"] = model->remainingScore();
    }
    void setValues(QJsonArray &arr, const QVector<DCContext::IDCInputModel*>& inputModels) const override
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
