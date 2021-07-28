#ifndef PLAYERMODELBUILDER_H
#define PLAYERMODELBUILDER_H

#include "icreateplayerfromjson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "playermodel.h"

namespace PlayersContext {
    class CreatePlayerFromJson : public ICreatePlayerFromJson
    {
    public:
        virtual const IPlayerModel *createPlayerModel(const QByteArray &json) const override
        {
            auto obj = createObject(json);
            auto playerModel = new PlayerModel;
            playerModel->setUserName(obj.value("playerName").toString());
            playerModel->setEmail(obj.value("playerMail").toString());
            playerModel->setId(QUuid::createUuid());
            return playerModel;
        }
    private:
        QJsonObject createObject(const QByteArray &json) const
        {
            auto document = QJsonDocument::fromJson(json);
            auto obj = document.object();
            return obj;
        }
    };
}

#endif // DARTSPLAYERMODELBUILDER_H
