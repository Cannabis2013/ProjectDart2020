#include "dsindexesbuilder.h"

using namespace DSCContext;

const DSCContext::IDSCIndexes *DSCContext::DSIndexesBuilder::createIndexes(const QByteArray &json) const
{
    auto indexes = DMAIndexes::createInstance();
    auto jsonObject = QJsonDocument::fromJson(json).object();
    indexes->setTotalTurns(jsonObject.value("totalTurns").toInt());
    indexes->setTurnIndex(jsonObject.value("turnIndex").toInt());
    indexes->setRoundIndex(jsonObject.value("roundIndex").toInt());
    indexes->setSetIndex(jsonObject.value("setIndex").toInt());
    return indexes;
}

const DSCContext::IDSCIndexes *DSCContext::DSIndexesBuilder::createIndexes(const IDSIndexService *service) const
{
    auto indexes = DMAIndexes::createInstance();
    indexes->setTotalTurns(service->totalIndex());
    indexes->setTurnIndex(service->turnIndex());
    indexes->setRoundIndex(service->roundIndex());
    indexes->setSetIndex(service->setIndex());
    return indexes;
}
