#ifndef DPCINPUTSTOJSON_H
#define DPCINPUTSTOJSON_H

#include "DartsController/DCInputSLAs/idcinputjsoncontext.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
class DPCInputsToJson : public IDCInputJsonContext
{
public:
    void setValues(QJsonObject &obj, DCContext::IDCInputModel* model) const override
    {
        obj["point"] = model->point();
        obj["modKeyCode"] = model->modKeyCode();
        obj["score"] = model->score();
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


#endif // DPCINPUTTOJSON_H
