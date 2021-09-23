#ifndef DCINDEXESBUILDER_H
#define DCINDEXESBUILDER_H

#include "dcindexes.h"
#include "DCIndexSLAs/idcindexservice.h"
#include "DCIndexSLAs/idcindexesbuilder.h"

class DCIndexesBuilder : public IDCIndexesBuilder
{
public:
    const DCContext::DCIndexes *createIndexes(const QByteArray &json) const override
    {
        auto document = QJsonDocument::fromJson(json);
        auto jsonObject = document.object();
        auto totalTurns = jsonObject.value("totalTurns").toInt();
        auto turnIndex = jsonObject.value("turnIndex").toInt();
        auto roundIndex = jsonObject.value("roundIndex").toInt();
        auto setIndex = jsonObject.value("setIndex").toInt();
        auto attemptIndex = jsonObject.value("attemptIndex").toInt();
        auto model = DCContext::DCIndexes::createInstance()
                ->setTotalTurns(totalTurns)
                ->setTurnIndex(turnIndex)
                ->setRoundIndex(roundIndex)
                ->setSetIndex(setIndex)
                ->setAttemptIndex(attemptIndex);
        return model;
    }
    const DCContext::DCIndexes *createIndexes(const IDCIndexService *indexService) const override
    {
        auto totalTurns = indexService->totalIndex();
        auto turnIndex = indexService->turnIndex();
        auto roundIndex = indexService->roundIndex();
        auto setIndex = indexService->setIndex();
        auto attemptIndex = indexService->attemptIndex();
        auto model = DCContext::DCIndexes::createInstance()
                ->setTotalTurns(totalTurns)
                ->setTurnIndex(turnIndex)
                ->setRoundIndex(roundIndex)
                ->setSetIndex(setIndex)
                ->setAttemptIndex(attemptIndex);
        return model;
    }
};

#endif // DARTSCONTROLLERINDEXESBUILDER_H
