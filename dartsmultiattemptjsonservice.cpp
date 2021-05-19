#include "dartsmultiattemptjsonservice.h"

int DartsMultiAttemptJsonService::getScoretByJson(const QByteArray &json) const
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto inputValueModel = jsonObject.value("score").toInt();
    return inputValueModel;
}

QByteArray DartsMultiAttemptJsonService::assembleJsonFromParameters(const QString &playerName, const int &score) const
{
    QJsonObject obj = {
        {"playerName",playerName},
        {"score",score}
    };
    auto json = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    return json;
}

QByteArray DartsMultiAttemptJsonService::assembleJsonDartsScore(const QString &playerName, const int &score) const
{
    QJsonObject jsonObject;
    jsonObject["playerName"] = playerName;
    jsonObject["score"] = score;
    auto document = QJsonDocument(jsonObject);
    auto json = document.toJson();
    return json;
}

QByteArray DartsMultiAttemptJsonService::assembleJsonTurnValues(const bool &canUndo,
                                                                const bool &canRedo,
                                                                const int &roundIndex,
                                                                const QString &currentPlayerName,
                                                                const QString &targetRow) const
{
    QJsonObject jsonObject = {
        {"canUndo", canUndo},
        {"canRedo",canRedo},
        {"roundIndex",roundIndex},
        {"currentUserName",currentPlayerName},
        {"targetRow",targetRow}
    };
    auto json = QJsonDocument(jsonObject).toJson();
    return json;
}

QByteArray DartsMultiAttemptJsonService::assembleJsonAddScoreValues(const QUuid &tournamentId, const int &roundIndex,
                                                                    const int &setIndex,const QUuid &winnerId,
                                                                    const QUuid &playerId,const int& score) const
{
    QJsonObject obj;
    obj["tournamentId"] = tournamentId.toString(QUuid::WithoutBraces);
    obj["roundIndex"] = roundIndex;
    obj["setIndex"] = setIndex;
    obj["winnerId"] = winnerId.toString(QUuid::WithoutBraces);
    obj["playerId"] = playerId.toString(QUuid::WithoutBraces);
    obj["score"] = score;
    auto json = QJsonDocument(obj).toJson();
    return json;
}

QByteArray DartsMultiAttemptJsonService::assembleJsonWinnerName(const QUuid& tournamentId,
                                                                const QUuid &winnerId) const
{
    QJsonObject jsonObject = {
        {"tournamentId",tournamentId.toString(QUuid::WithoutBraces)},
        {"winnerId",winnerId.toString(QUuid::WithoutBraces)}
    };
    auto json = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    return json;
}


QByteArray DartsMultiAttemptJsonService::assembleJsonDartsMultiAttemptScores(const IPlayerScoreService *scoreService) const
{
    auto count = scoreService->playersCount();
    QJsonArray playerScoreEntities;
    for (int i = 0; i < count; ++i) {
        QJsonObject obj;
        auto playerName = scoreService->playerNameByIndex(i);
        auto score = scoreService->playerScore(i);
        obj["playerName"] = playerName;
        obj["score"] = score;
        playerScoreEntities.append(obj);
    };
    auto document = QJsonDocument(playerScoreEntities);
    auto json = document.toJson(QJsonDocument::Compact);
    return json;
}
