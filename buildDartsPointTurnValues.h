#ifndef BUILDDARTSPOINTTURNVALUES_H
#define BUILDDARTSPOINTTURNVALUES_H

#include "iternaryservice.h"
#include "dartspointturnvalues.h"
#include "idartssingleattemptindexservice.h"
#include "iplayerpointservice.h"
#include "idartslogisticsservice.h"
#include "idartssingleattemptindexes.h"

namespace DartsPointSingleAttemptContext{
    typedef IDartsSingleAttemptIndexService<IDartsSingleAttemptIndexes> DartsIndexService;
    class BuildDartsPointTurnValues : public
            ITernaryService<const DartsIndexService*,
                            const IPlayerPointService*,
                            const IDartsLogisticsService<QString>*,
                            DartsPointTurnValues*>
    {
    public:
        DartsPointTurnValues* service(const DartsIndexService* indexService,
                                      const IPlayerPointService* playerScoreService,
                                      const IDartsLogisticsService<QString>* logisticService) override
        {
            auto model = new DartsPointTurnValues;
            model->setCanUndo(indexService->canUndo());
            model->setCanRedo(indexService->canRedo());
            model->setRoundIndex(indexService->roundIndex());
            model->setSetIndex(indexService->setIndex());
            model->setAttemptIndex(indexService->attemptIndex());
            model->setTargetRow(buildTargetRow(model->getScore(),model->getAttemptIndex(),logisticService));
            model->setPlayerName(playerScoreService->playerNameByIndex(model->getSetIndex()));
            return model;
        }
    private:
        QString buildTargetRow(const int& remainingScore,
                               const int& attemptIndex,
                               const IDartsLogisticsService<QString>* logisticService)
        {
            if(logisticService == nullptr)
                return "Logistic service not injected";
            auto targetRow = logisticService->suggestTargetRow(remainingScore,attemptIndex);
            return targetRow;
        }
    };
}

#endif // BUILDDARTSPOINTTURNVALUES_H
