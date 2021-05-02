#include "assembledartstournamentmodelfromjson.h"

const IDartsTournament<QUuid, QString> *AssembleDartsTournamentModelFromJson::service(const QByteArray &json, LocalPlayerModelsContext *playerModelsService)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    // Extract player-indexes
    QVector<int> assignedPlayerIndexes;
    auto arr = jsonObject["PlayerIndexes"].toArray();
    for (auto jsonVal : arr) {
        auto index = jsonVal.toInt();
        assignedPlayerIndexes << index;
    }
    // Extract Darts tournament values
    auto title = jsonObject.value("title").toString();
    auto gameMode = jsonObject.value("gameMode").toInt();
    auto keyPoint = jsonObject.value("keyPoint").toInt();
    auto terminalKeyCode = jsonObject.value("terminalKeyCode").toInt();
    auto displayHint = jsonObject.value("displayHint").toInt();
    auto inputHint = jsonObject.value("inputHint").toInt();
    auto attempts = jsonObject.value("attempts").toInt();
    auto assignedPlayersIds = playerModelsService->assemblePlayerIds(assignedPlayerIndexes);
    auto model = buildModelFromParameters(title,gameMode,keyPoint,terminalKeyCode,
                                          displayHint,inputHint,attempts,
                                          assignedPlayersIds);
    return model;
}

const IDartsTournament<QUuid, QString> *AssembleDartsTournamentModelFromJson::buildModelFromParameters(const QString &title,
                                                                                                    const int& gameMode,
                                                                                                    const int& keyPoint,
                                                                                                    const int& terminalKeyCode,
                                                                                                    const int& displayHint,
                                                                                                    const int& inputHint,
                                                                                                    const int& attempts,
                                                                                                    const QVector<QUuid> &playerIds)
{
    auto model = DartsTournament::createInstance()
            ->setTitle(title)
            ->setKeyPoint(keyPoint)
            ->setGameMode(gameMode)
            ->setAttempts(attempts)
            ->setAssignedPlayerIdentities(playerIds)
            ->setTerminalKeyCode(terminalKeyCode)
            ->setDisplayHint(displayHint)
            ->setInputMode(inputHint)
            ->setId(QUuid::createUuid());
    return model;
}
