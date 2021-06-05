#ifndef ASSEMBLEPLAYERMODELFROMJSON_H
#define ASSEMBLEPLAYERMODELFROMJSON_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "playermodel.h"
#include <quuid.h>

namespace DartsModelsContext {
    class AssemblePlayerModelFromJson :
            public IUnaryService<const QByteArray&,const IPlayerModel*>
    {
    public:
        const IPlayerModel* service(const QByteArray& json) override
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            auto name = jsonObject.value("playerName").toString();
            auto mail = jsonObject.value("playerMail").toString();
            auto model = PlayerModel::createInstance()
                    ->setUserName(name)
                    ->setEmail(mail)
                    ->setId(QUuid::createUuid());
            return model;
        }
    };
}

#endif // ASSEMBLEPLAYERMODELFROMJSON_H
