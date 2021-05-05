#include "dartstournamentjsonextractor.h"


QVector<const IModel<QUuid>*> DartsTournamentJsonExtractor::service(const QJsonArray &arr)
{
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
        auto playersJSONArray = tournamentJSON["Players"].toArray();
        auto playersJSONCount = playersJSONArray.count();
        QVector<QUuid> assignedPlayerIds;
        for (int j = 0; j < playersJSONCount; ++j) {
            auto assignedPlayerJSON = playersJSONArray[j].toObject();
            auto stringID = assignedPlayerJSON["ID"].toString();
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
