#ifndef CONVERTDARTSMODELS_H
#define CONVERTDARTSMODELS_H
#include <quuid.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "DbSLAs/imodelconverter.h"
#include "DbSLAs/idbjsonbuilder.h"
#include "ModelSLAs/imodel.h"
class ConvertDartsModels : public IDbJsonBuilder<IModel<QUuid>>
{
    typedef IModel<QUuid> BaseModel;
    typedef QVector<BaseModel*> Models;
    QJsonObject toJsonObject(const Json &json, const Models &models, Converter *cvtr)
    {
        auto returnedJson = json;
        QJsonArray arr;
        for (const auto &model : models)
            arr << cvtr->create(model);
        returnedJson["DartsTournamentModels"] = arr;
        return returnedJson;
    }
};
#endif // CONVERTMODELS_H
