#ifndef CREATEJSONFROMPLAYERMODELS_H
#define CREATEJSONFROMPLAYERMODELS_H

#include <qvector.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <QJsonObject>
#include <quuid.h>
#include "ModelsContext/MCModelsSLAs/imodel.h"
#include "PlayerModelsContext/SLAs/iplayermodel.h"
#include "ModelsContext/MCJsonSLAs/icreatejsonfrommodels.h"

namespace PlayersContext {
    class CreateJsonFromPlayerModels : public ICreateJsonFromModels
    {
    public:
        virtual QByteArray toJson(const QVector<const IModel<QUuid>*>& models) const override
        {
            QJsonArray arr = createJsonArray(models);
            return createByteArray(arr);
        }
    private:
        QJsonArray createJsonArray(QVector<const IModel<QUuid>*> models) const
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
            obj["UserName"] = playerModel->playerName();
            obj["Mail"] = playerModel->email();
            return obj;
        }
        QByteArray createByteArray(const QJsonArray &arr) const
        {
            return QJsonDocument(arr).toJson();
        }
    };
}


#endif // PLAYERJSONASSEMBLER_H
