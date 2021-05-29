#include "dartsscoreindexesbuilderservice.h"

using namespace DartsScoreMultiAttemptContext;

const DartsScoreIndexesBuilderService::TurnIndexes *DartsScoreMultiAttemptContext::DartsScoreIndexesBuilderService::buildControllerIndexesByJson(const JsonFormat &json) const
{
    auto indexes = DartsMultiAttemptIndexes::createInstance();
    auto jsonObject = QJsonDocument::fromJson(json).object();
    indexes->setTotalTurns(jsonObject.value("totalTurns").toInt());
    indexes->setTurnIndex(jsonObject.value("turnIndex").toInt());
    indexes->setRoundIndex(jsonObject.value("roundIndex").toInt());
    indexes->setSetIndex(jsonObject.value("setIndex").toInt());
    return indexes;
}

const DartsScoreIndexesBuilderService::TurnIndexes *DartsScoreMultiAttemptContext::DartsScoreIndexesBuilderService::buildControllerIndexesByIndexService(const ControllerIndexService *service) const
{
    auto indexes = DartsMultiAttemptIndexes::createInstance();
    indexes->setTotalTurns(service->totalIndex());
    indexes->setTurnIndex(service->turnIndex());
    indexes->setRoundIndex(service->roundIndex());
    indexes->setSetIndex(service->setIndex());
    return indexes;
}
