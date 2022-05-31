#include "savetostorage.h"

SaveToStorage::SaveToStorage(const QString &key, IFileDataIO *ioDevice, Converter *converter)
    :_ioDevice(ioDevice),_converter(converter),_jsonKey(key){}

bool SaveToStorage::save(const Models &models)
{
    auto bytearray = _ioDevice->read();
    auto fileContentAsJson = toJsonObject(bytearray);
    auto json = toJsonObject(fileContentAsJson,models);
    return _ioDevice->save(QJsonDocument(json).toJson());
}

QJsonObject SaveToStorage::toJsonObject(const QByteArray &byteArray)
{
    auto document = QJsonDocument::fromJson(byteArray);
    return document.object();
}

QJsonObject SaveToStorage::toJsonObject(const QJsonObject &json, const Models &models)
{
    auto returnedJson = json;
    QJsonArray arr;
    for (const auto &model : qAsConst(models))
        arr << _converter->convert(model);
    returnedJson[_jsonKey] = arr;
    return returnedJson;
}

