#include "dartstournamentjsonextractor.h"


QVector<const IModel<QUuid>*> DartsTournamentJsonExtractor::service(const QJsonArray &arr)
{
    using namespace DartsModelsContext;
    QVector<const IModel<QUuid>*> dartsTournaments;
    auto tournamentsCount = arr.count();
    for (int i = 0; i < tournamentsCount; ++i) {
        auto tournamentJSON = arr[i].toObject();
        auto stringID = tournamentJSON["Id"].toString();
        auto tournamentId = QUuid::fromString(stringID);
        auto title = tournamentJSON["Title"].toString();
        auto keyPoint = tournamentJSON["KeyPoint"].toInt();
        auto tableViewHint = tournamentJSON["TableViewHint"].toInt();
        auto inputMode = tournamentJSON["InputMode"].toInt();
        auto gameMode = tournamentJSON["GameMode"].toInt();
        auto attempts = tournamentJSON["Attempts"].toInt();
        auto terminalKeyCode = tournamentJSON["TerminalKeyCode"].toInt();
        auto winnerStringID = tournamentJSON["Winner"].toString();
        auto winnerId = QUuid::fromString(winnerStringID);
        auto playersJSONArray = tournamentJSON["assignedPlayerIds"].toArray();
        auto playersJsonCount = playersJSONArray.count();
        QVector<QUuid> assignedPlayerIds;
        for (int j = 0; j < playersJsonCount; ++j) {
            auto assignedPlayerJson = playersJSONArray[j].toObject();
            auto stringID = assignedPlayerJson["Id"].toString();
            auto playerId = QUuid::fromString(stringID);
            assignedPlayerIds << playerId;
        }
        auto tournamentModel = DartsTournament::createInstance()
                ->setId(tournamentId)
                ->setTitle(title)
                ->setKeyPoint(keyPoint)
                ->setDisplayHint(tableViewHint)
                ->setInputMode(inputMode)
                ->setGameMode(gameMode)
                ->setAttempts(attempts)
                ->setWinnerId(winnerId)
                ->setTerminalKeyCode(terminalKeyCode)
                ->setAssignedPlayerIdentities(assignedPlayerIds);
        dartsTournaments << tournamentModel;
    }
    return dartsTournaments;
}
