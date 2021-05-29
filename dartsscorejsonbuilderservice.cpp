#include "dartsscorejsonbuilderservice.h"

using namespace DartsScoreMultiAttemptContext;

QByteArray DartsScoreJsonBuilderService::assembleJsonAddScoreValues(const QUuid &tournamentId, const int &roundIndex,
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

QByteArray DartsScoreJsonBuilderService::assembleJsonWinnerName(const QUuid& tournamentId,
                                                                const QUuid &winnerId) const
{
    QJsonObject jsonObject = {
        {"tournamentId",tournamentId.toString(QUuid::WithoutBraces)},
        {"winnerId",winnerId.toString(QUuid::WithoutBraces)}
    };
    auto json = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    return json;
}

QByteArray DartsScoreJsonBuilderService::buildJsonByDartsScoreModels(const QVector<const InputModelInterface *> &inputModels) const
{
    QJsonArray arr;
    for (const auto& inputModel : inputModels) {
        QJsonObject jsonObject;
        jsonObject["playerId"] = inputModel->playerId().toString(QUuid::WithoutBraces);
        jsonObject["playerName"] = inputModel->playerName();
        jsonObject["score"] = inputModel->score();
        jsonObject["accumulatedScore"] = inputModel->accumulatedScore();
        arr << jsonObject;
    }
    auto document = QJsonDocument(arr);
    auto json = document.toJson();
    return json;
}
