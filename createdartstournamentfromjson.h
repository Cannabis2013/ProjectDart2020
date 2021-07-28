#ifndef CREATEDARTSTOURNAMENTFROMJSON_H
#define CREATEDARTSTOURNAMENTFROMJSON_H

#include "icreatemodelfromstring.h"
#include "dartstournament.h"

namespace ModelsContext {
    class CreateDartsTournamentFromJson : public ICreateModelFromString<AbstractDartsTournament,QByteArray>
    {
    public:
        const AbstractDartsTournament *create(const QByteArray &json) override
        {
            auto jsonObject = createJsonObject(json);
            auto tournamentModel = createModelFromJsonObject(jsonObject);
            return tournamentModel;
        }
    private:
        QJsonObject createJsonObject(const QByteArray &json)
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            return jsonObject;
        }
        const AbstractDartsTournament *createModelFromJsonObject(const QJsonObject &jsonObject)
        {
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
            dartsTournamentModel->setWinnerName(jsonObject.value("winnerName").toString(""));
            dartsTournamentModel->setId(QUuid::createUuid());
            return dartsTournamentModel;
        }
    };
}

#endif // DARTSTOURNAMENTBUILDER_H
