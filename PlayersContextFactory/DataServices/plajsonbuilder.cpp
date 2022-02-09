#include "plajsonbuilder.h"
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qbytearray.h>
PlaJsonBuilder::ByteArray PlaJsonBuilder::create(const Models &models, ByteArray &data) const
{
    auto obj = toJsonObject(data);
    auto arr = toJsonArray(models);
    obj["Players"] = arr;
    data = QJsonDocument(obj).toJson();
    return data;
}

PlaJsonBuilder::ByteArray PlaJsonBuilder::create(const Models &models) const
{
    auto arr = toJsonArray(models);
    return QJsonDocument(arr).toJson();
}

QJsonArray PlaJsonBuilder::toJsonArray(const Models &models) const
{
    QJsonArray arr;
    for (auto i = models.begin(); i != models.end(); ++i)
        arr << toJsonObject(*i);
    return arr;
}

QJsonObject PlaJsonBuilder::toJsonObject(Model *model) const
{
    if(model == nullptr)
        throw new std::invalid_argument("Model is null");
    QJsonObject obj;
    obj["id"] = model->id().toString(QUuid::WithoutBraces);
    obj["name"] = model->name();
    obj["mail"] = model->mail();
    return obj;
}

QJsonObject PlaJsonBuilder::toJsonObject(ByteArray &data) const
{
    auto document = QJsonDocument::fromJson(data);
    return document.object();
}


PlaJsonBuilder::ByteArray PlaJsonBuilder::create(Model *model) const
{
    try {
        auto json = toJsonObject(model);
        return QJsonDocument(json).toJson();
    }  catch (std::invalid_argument *e) {
        qDebug() << e->what();
        return QByteArray();
    }
}
