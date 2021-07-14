#ifndef DARTSTOURNAMENTBUILDER_H
#define DARTSTOURNAMENTBUILDER_H

#include "idartstournamentbuilder.h"
#include "dartstournament.h"

namespace DartsModelsContext {
    class DartsTournamentBuilder : public IDartsTournamentBuilder<IDartsTournament,QByteArray>
    {
    public:
        const ModelInterface *create(const JsonFormat &json) override
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            auto dartsTournamentModel = DartsTournament::createInstance();
            dartsTournamentModel->setTitle(jsonObject.value("title").toString());
            dartsTournamentModel->setGameMode(jsonObject.value("gameMode").toInt());
            dartsTournamentModel->setKeyPoint(jsonObject.value("keyPoint").toInt());
            dartsTournamentModel->setAttempts(jsonObject.value("attempts").toInt());
            dartsTournamentModel->setTerminalKeyCode(jsonObject.value("terminalKeyCode").toInt());
            dartsTournamentModel->setDisplayHint(jsonObject.value("displayHint").toInt());
            dartsTournamentModel->setInputMode(jsonObject.value("inputHint").toInt());
            dartsTournamentModel->setStatus(jsonObject.value("status").toInt());
            dartsTournamentModel->setWinnerId(QUuid(jsonObject.value("winnerId").toString("")));
            dartsTournamentModel->setId(QUuid::createUuid());
            return dartsTournamentModel;
        }
    };
}

#endif // DARTSTOURNAMENTBUILDER_H
