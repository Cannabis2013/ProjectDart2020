#ifndef DARTSCONTROLLERINDEXESBUILDER_H
#define DARTSCONTROLLERINDEXESBUILDER_H

#include "dcindexes.h"
#include "idartspointindexservice.h"
#include <idpcindexesbuilder.h>
namespace DPCContext {
    class DPIndexesBuilder : public IDPCIndexesBuilder
    {
    public:
        const DCIndexes *createIndexes(const QByteArray &json) const override
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            auto totalTurns = jsonObject.value("totalTurns").toInt();
            auto turnIndex = jsonObject.value("turnIndex").toInt();
            auto roundIndex = jsonObject.value("roundIndex").toInt();
            auto setIndex = jsonObject.value("setIndex").toInt();
            auto attemptIndex = jsonObject.value("attemptIndex").toInt();
            auto model = DCIndexes::createInstance()
                    ->setTotalTurns(totalTurns)
                    ->setTurnIndex(turnIndex)
                    ->setRoundIndex(roundIndex)
                    ->setSetIndex(setIndex)
                    ->setAttemptIndex(attemptIndex);
            return model;
        }
        const DCIndexes *createIndexes(const IDartsPointIndexService *indexService) const override
        {
            auto totalTurns = indexService->totalIndex();
            auto turnIndex = indexService->turnIndex();
            auto roundIndex = indexService->roundIndex();
            auto setIndex = indexService->setIndex();
            auto attemptIndex = indexService->attemptIndex();
            auto model = DCIndexes::createInstance()
                    ->setTotalTurns(totalTurns)
                    ->setTurnIndex(turnIndex)
                    ->setRoundIndex(roundIndex)
                    ->setSetIndex(setIndex)
                    ->setAttemptIndex(attemptIndex);
            return model;
        }
    };
}

#endif // DARTSCONTROLLERINDEXESBUILDER_H
