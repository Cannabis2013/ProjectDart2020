#include "dartscreatejsonfromscores.h"

using namespace DartsModelsContext;

QByteArray DartsCreateJsonFromScores::createJson(const QVector<const IPlayerInput*> &models) const
{
    auto arr = createJsonArray(models);
    return createByteArray(arr);
}

QJsonArray DartsCreateJsonFromScores::createJsonArray(const QVector<const IPlayerInput *> &models) const
{
    QJsonArray arr;
    for (const auto& model : models)
        arr << createJsonObject(model);
    return arr;
}

QJsonObject DartsCreateJsonFromScores::createJsonObject(const IPlayerInput *model) const
{
    auto dartsScoreInput = dynamic_cast<const IDartsScoreInput*>(model);
    QJsonObject dartsScoreJsonObject;
    auto playerId = dartsScoreInput->playerId();
    dartsScoreJsonObject["playerId"] = playerId.toString(QUuid::WithoutBraces);
    dartsScoreJsonObject["score"] = dartsScoreInput->score();
    return dartsScoreJsonObject;
}

QByteArray DartsCreateJsonFromScores::createByteArray(const QJsonArray &arr) const
{
    auto document = QJsonDocument(arr);
    auto json = document.toJson();
    return json;
}

