#ifndef DARTSPLAYERMODELBUILDER_H
#define DARTSPLAYERMODELBUILDER_H

#include "idartsplayermodelbuilder.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "playermodel.h"

namespace DartsModelsContext {
    class DartsPlayerModelBuilder : public IDartsPlayerModelBuilder
    {
    public:
        virtual const Player *createPlayerModel(const Json &json) const override
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
