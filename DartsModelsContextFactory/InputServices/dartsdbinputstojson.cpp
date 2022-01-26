#include "dartsdbinputstojson.h"
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "DbSLAs/imodelconverter.h"
QJsonObject DartsDbInputsToJson::toJsonObject(const Json &json, const Models &models, Converter *cvtr)
{
    auto returnedJson = json;
    QJsonArray arr;
    for (const auto &model : qAsConst(models))
        arr << cvtr->create(model);
    returnedJson["DartsInputModels"] = arr;
    return returnedJson;
}
