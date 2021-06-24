#include "dartsscorejsonbuilderservice.h"

using namespace DartsScoreControllerContext;

QByteArray DartsScoreJsonBuilderService::createJsonByDartsScore(const ModelInterface *model) const
{
    QJsonObject obj;
    obj["tournamentId"] = model->tournamentId().toString(QUuid::WithoutBraces);
    obj["score"] = model->score();
    obj["playerId"] = model->playerId().toString(QUuid::WithoutBraces);
    obj["playerName"] = model->playerName();
    auto json = QJsonDocument(obj).toJson();
    return json;
}

QByteArray DartsScoreJsonBuilderService::createJsonByIds(const QUuid& tournamentId,
                                                         const QUuid &winnerId) const
{
    QJsonObject jsonObject = {
        {"tournamentId",tournamentId.toString(QUuid::WithoutBraces)},
        {"winnerId",winnerId.toString(QUuid::WithoutBraces)}
    };
    auto json = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    return json;
}

QByteArray DartsScoreJsonBuilderService::createJsonByDartsScoreModels(const QVector<const ModelInterface *> &inputModels) const
{
    QJsonArray arr;
    for (const auto& inputModel : inputModels) {
        QJsonObject jsonObject;
        jsonObject["playerId"] = inputModel->playerId().toString(QUuid::WithoutBraces);
        jsonObject["playerName"] = inputModel->playerName();
        jsonObject["score"] = inputModel->score();
        jsonObject["totalScore"] = inputModel->totalScore();
        arr << jsonObject;
    }
    auto document = QJsonDocument(arr);
    auto json = document.toJson();
    return json;
}
