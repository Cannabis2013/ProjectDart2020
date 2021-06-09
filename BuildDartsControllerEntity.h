#ifndef BUILDDARTSCONTROLLERENTITY_H
#define BUILDDARTSCONTROLLERENTITY_H

#include "iunaryservice.h"
#include "dartscontrollerentity.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsBuilderContext {
    class BuildDartsControllerEntity : public
            IUnaryService<const QByteArray&,const IDartsControllerEntity<QUuid,QString>*>
    {
    public:
        static BuildDartsControllerEntity* createInstance()
        {
            return new BuildDartsControllerEntity;
        }
        virtual OutputType service(InputType input) override
        {
            auto document = QJsonDocument::fromJson(input);
            auto jsonObject = document.object();
            auto entity = new DartsControllerEntity;
            entity->setTournamentId(QUuid(jsonObject.value("tournamentId").toString()));
            entity->setAttempt(jsonObject.value("attempt").toInt());
            entity->setKeyPoint(jsonObject.value("terminalKeyCode").toInt());
            entity->setTerminalKeyCode(jsonObject.value("terminalKeyCode").toInt());
            entity->setInputHint(jsonObject.value("inputHint").toInt());
            entity->setWinnerId(QUuid(jsonObject.value("winnerId").toString()));
            entity->setDisplayHint(jsonObject.value("displayHint").toInt());
            return entity;
        }
    };
}

#endif // BUILDDARTSCONTROLLERENTITY_H
