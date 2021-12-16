#ifndef PLAJSONBUILDER_H
#define PLAJSONBUILDER_H
#include <qbytearray.h>
#include <qvector.h>
#include "PlayerModelsContext/DbSLAs/iplayer.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <quuid.h>
#include "PlayerModelsContext/DataSLAs/idatabuilder.h"
class PlaJsonBuilder : public IDataBuilder<IPlayer,QByteArray>
{
public:
    virtual Data create(const Models &models, Data &data) const override
    {
        auto obj = toJsonObject(data);
        auto arr = toJsonArray(models);
        obj["Players"] = arr;
        data = QJsonDocument(obj).toJson();
        return data;
    }
    virtual Data create(const Models &models) const override
    {
        auto arr = toJsonArray(models);
        return QJsonDocument(arr).toJson();
    }
private:
    QJsonArray toJsonArray(const Models &models) const
    {
        QJsonArray arr;
        for (auto i = models.begin(); i != models.end(); ++i)
            arr << toJsonObject(*i);
        return arr;
    }
    QJsonObject toJsonObject(Model *model) const
    {
        QJsonObject obj;
        obj["id"] = model->id().toString(QUuid::WithoutBraces);
        obj["name"] = model->name();
        obj["mail"] = model->mail();
        return obj;
    }
    QJsonObject toJsonObject(Data &data) const
    {
        auto document = QJsonDocument::fromJson(data);
        return document.object();
    }
};
#endif // PLAJSONBUILDER_H
