#ifndef PLAYERJSONBUILDER_H
#define PLAYERJSONBUILDER_H
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <QJsonObject>
#include "PlayerModelsContext/DbSLAs/iplayerjsonbuilder.h"
#include "PlayerModelsContext/DbSLAs/iplayermodel.h"
class PlayerJsonBuilder : public IPlayerJsonBuilder<IModel<QUuid>,QByteArray>
{
public:
    virtual QByteArray create(const QVector<BaseModel*>& models) const override
    {
        QJsonArray arr = toJsonArray(models);
        return toByteArray(arr);
    }
    virtual DataFormat create(const QVector<BaseModel*> &models, QByteArray &byteArray) const override
    {
        auto json = QJsonDocument::fromJson(byteArray).object();
        json["players"] = toJsonArray(models);
        byteArray = QJsonDocument(json).toJson();
        return byteArray;
    }
private:
    QJsonArray toJsonArray(QVector<BaseModel*> models) const
    {
        QJsonArray arr;
        for (auto model : models)
            arr << toJsonObject(model);
        return arr;
    }
    QJsonObject toJsonObject(const BaseModel *model) const
    {
        auto playerModel = dynamic_cast<const IPlayerModel*>(model);
        QJsonObject obj;
        obj["Id"] = playerModel->id().toString();
        obj["playerName"] = playerModel->name();
        obj["playerMail"] = playerModel->email();
        return obj;
    }
    QByteArray toByteArray(const QJsonArray &arr) const
    {
        return QJsonDocument(arr).toJson();
    }
};
#endif // PLAYERJSONASSEMBLER_H
