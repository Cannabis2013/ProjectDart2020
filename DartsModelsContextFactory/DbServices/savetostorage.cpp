#include "savetostorage.h"

bool SaveToStorage::save(const std::initializer_list<ServiceProvider> &list)
{
    auto result = true;
    QList<ServiceProvider> sPs(list);
    for (const auto & sP : sPs) {
        if(!save(sP.models,sP.builder,sP.converter,sP.ioDevice))
            result = false;
    }
    return result;
}

QJsonObject SaveToStorage::toJsonObject(const QByteArray &byteArray)
{
    auto document = QJsonDocument::fromJson(byteArray);
    return document.object();
}

QJsonArray SaveToStorage::toJsonArray(const Models &models, Converter *cvtr)
{
    QJsonArray arr;
    for (const auto &model : models)
        arr << cvtr->create(model);
    return arr;
}

bool SaveToStorage::save(const QVector<BaseModel *> &models, JsonBuilder *builder, Converter *converter, IODevice *ioDevice)
{
    auto bytearray = ioDevice->read();
    auto fileContentAsJson = toJsonObject(bytearray);
    auto json = builder->toJsonObject(fileContentAsJson,models,converter);
    return ioDevice->save(QJsonDocument(json).toJson());
}
