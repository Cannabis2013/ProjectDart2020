#include "dartspointinputstojson.h"
using namespace DartsPointControllerContext;

DartsPointInputsToJson::JsonFormat DartsPointInputsToJson::toJson(const QVector<const InputModel *> &inputs) const
{
    auto jsonArray = toJsonArray(inputs);
    auto json = toJsonByteArray(jsonArray);
    return json;
}

QByteArray DartsPointInputsToJson::toJsonByteArray(const QJsonArray &arr) const
{
    auto document = QJsonDocument(arr);
    auto jsonByteArray = document.toJson();
    return jsonByteArray;
}

QJsonArray DartsPointInputsToJson::toJsonArray(const InputModels &inputs) const
{
    QJsonArray arr;
    for (const auto &input : inputs)
        arr << toJsonobject(input);
    return arr;
}

QJsonObject DartsPointControllerContext::DartsPointInputsToJson::toJsonobject(const InputModel *inputModel) const
{
    auto document = QJsonDocument::fromJson(inputModel->toJson());
    auto jsonobject = document.object();
    return jsonobject;
}
