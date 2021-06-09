#ifndef DARTSCONTROLLERINDEXESBUILDER_H
#define DARTSCONTROLLERINDEXESBUILDER_H

#include "idartscontrollerindexesbuilder.h"
#include "dartssingleattemptindexes.h"
#include "idartssingleattemptindexservice.h"
namespace DartsPointControllerContext {
    class DartsIndexesBuilderService : public
            IDartsControllerIndexesBuilder<
            IDartsSingleAttemptIndexes,
            IDartsSingleAttemptIndexService<IDartsSingleAttemptIndexes>,
            QByteArray>
    {
    public:


        // IDartsControllerIndexesModelBuilder interface
    public:
        const TurnIndexes *buildControllerIndexesByJson(const JsonFormat &json) const override
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            auto totalTurns = jsonObject.value("totalTurns").toInt();
            auto turnIndex = jsonObject.value("turnIndex").toInt();
            auto roundIndex = jsonObject.value("roundIndex").toInt();
            auto setIndex = jsonObject.value("setIndex").toInt();
            auto attemptIndex = jsonObject.value("attemptIndex").toInt();
            auto model = DartsSingleAttemptIndexes::createInstance()
                    ->setTotalTurns(totalTurns)
                    ->setTurnIndex(turnIndex)
                    ->setRoundIndex(roundIndex)
                    ->setSetIndex(setIndex)
                    ->setAttemptIndex(attemptIndex);
            return model;
        }
        const TurnIndexes *buildControllerIndexesByIndexService(const ControllerIndexService *indexService) const override
        {
            auto totalTurns = indexService->totalIndex();
            auto turnIndex = indexService->turnIndex();
            auto roundIndex = indexService->roundIndex();
            auto setIndex = indexService->setIndex();
            auto attemptIndex = indexService->attemptIndex();
            auto model = DartsSingleAttemptIndexes::createInstance()
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
