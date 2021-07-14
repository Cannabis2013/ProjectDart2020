#include "dartscreatejsonfromscoreindexes.h"

QByteArray DartsCreateJsonFromScoreIndexes::createJson(const IDartsScoreIndexes *indexes) const
{
    QJsonObject jsonObject;
    jsonObject["totalTurns"] = indexes->totalTurns();
    jsonObject["turnIndex"]  = indexes->turnIndex();
    jsonObject["roundIndex"] = indexes->roundIndex();
    jsonObject["setIndex"] = indexes->setIndex();
    auto json = QJsonDocument(jsonObject).toJson();
    return json;
}
