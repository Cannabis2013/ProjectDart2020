#include "dartsinputstojson.h"
#include <QJsonDocument>
#include <qbytearray.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "InputModelsSLAs/idartsinput.h"
#include "DbSLAs/imodelconverter.h"
DartsInputsToJson::ByteArray DartsInputsToJson::toJson(const Models &models, Converter *cvtr) const
{
    QJsonArray arr;
    for (const auto &model : qAsConst(models))
        arr << cvtr->create(model);
    return toByteArray(arr);
}

QByteArray DartsInputsToJson::toByteArray(const QJsonArray &arr) const
{
    auto document = QJsonDocument(arr);
    return document.toJson();
}
