#ifndef BUILDDARTSPOINTTURNVALUES_H
#define BUILDDARTSPOINTTURNVALUES_H

#include "ibuilddartspointturnvalues.h"
#include "dartspointturnvalues.h"
#include "idartspointindexservice.h"
#include "iplayerpointservice.h"
#include "idartslogisticsservice.h"
#include "idartspointcontrollerindexes.h"
#include "idartscontrollerplayer.h"
#include "idartscontrollerpoint.h"

namespace DartsPointControllerContext{
    typedef IDartsPointIndexService<IDartsPointControllerIndexes> DartsIndexService;
    class BuildDartsPointTurnValues : public IBuildDartsPointTurnValues
    {
    public:
        typedef IPlayerPointService<IDartsControllerPlayer<QUuid,QString>,
                                    IDartsControllerPoint<QUuid,QString,
        QByteArray>> PlayerPointService;
        DartsPointTurnValues* buildTurnValues(const DartsIndexService* indexService,
                                      const PlayerPointService* playerScoreService,
                                      const IDartsLogisticsService<QString>* logisticService) const override
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
                               const IDartsLogisticsService<QString>* logisticService) const
        {
            if(logisticService == nullptr)
                return "Logistic service not injected";
            auto targetRow = logisticService->suggestTargetRow(remainingScore,attemptIndex);
            return targetRow;
        }
    };
}

#endif // BUILDDARTSPOINTTURNVALUES_H
