#ifndef CREATEJSONFROMPLAYERMODELS_H
#define CREATEJSONFROMPLAYERMODELS_H

#include <qjsondocument.h>
#include <qjsonarray.h>
#include <QJsonObject>
#include "PlayerModelsContext/DbSLAs/iplayerjsonbuilder.h"
#include "PlayerModelsContext/DbSLAs/iplayermodel.h"

class CreateJsonFromPlayerModels : public IPlayerJsonBuilder
{
public:
    virtual QByteArray toJson(const QVector<IModel<QUuid>*>& models) const override
    {
        QJsonArray arr = createJsonArray(models);
        return createByteArray(arr);
    }
private:
    QJsonArray createJsonArray(QVector<IModel<QUuid>*> models) const
    {
        QJsonArray arr;
        for (auto model : models)
            arr << createJsonObject(model);
        return arr;
    }
    QJsonObject createJsonObject(const IModel<QUuid> *model) const
    {
        auto playerModel = dynamic_cast<const IPlayerModel*>(model);
        QJsonObject obj;
        obj["Id"] = playerModel->id().toString();
        obj["playerName"] = playerModel->playerName();
        obj["playerMail"] = playerModel->email();
        return obj;
    }
    QByteArray createByteArray(const QJsonArray &arr) const
    {
        return QJsonDocument(arr).toJson();
    }
};
#endif // PLAYERJSONASSEMBLER_H
