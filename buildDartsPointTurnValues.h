#ifndef BUILDDARTSPOINTTURNVALUES_H
#define BUILDDARTSPOINTTURNVALUES_H

#include "iternaryservice.h"
#include "dartspointturnvalues.h"
#include "idartssingleattemptindexservice.h"
#include "iplayerpointservice.h"
#include "idartslogisticsservice.h"
#include "idartssingleattemptindexes.h"
#include "idartscontrollerplayer.h"
#include "idartscontrollerpoint.h"

namespace DartsPointSingleAttemptContext{
    typedef IDartsSingleAttemptIndexService<IDartsSingleAttemptIndexes> DartsIndexService;
    class BuildDartsPointTurnValues : public
            ITernaryService<const DartsIndexService*,
                            const IPlayerPointService<IDartsControllerPlayer<QUuid,QString>,
                                                      IDartsControllerPoint<QUuid,QString,
                                                      QByteArray>>*,
                            const IDartsLogisticsService<QString>*,
                            DartsPointTurnValues*>
    {
    public:
        typedef IPlayerPointService<IDartsControllerPlayer<QUuid,QString>,
                                    IDartsControllerPoint<QUuid,QString,
        QByteArray>> PlayerPointService;
        DartsPointTurnValues* service(const DartsIndexService* indexService,
                                      const PlayerPointService* playerScoreService,
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
