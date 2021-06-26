#ifndef BUILDDARTSPOINTTURNVALUES_H
#define BUILDDARTSPOINTTURNVALUES_H

#include "ibuilddartspointturnvalues.h"
#include "dartspointturnvalues.h"
#include "idartspointindexservice.h"
#include "iplayerpointservice.h"
#include "idartsinputsuggestion.h"
#include "idartspointcontrollerindexes.h"
#include "idartscontrollerplayer.h"
#include "idartscontrollerpoint.h"

namespace DartsPointControllerContext{
    typedef IDartsPointControllerIndexes<QByteArray> DartsIndexes;
    typedef IDartsPointIndexService<DartsIndexes> DartsIndexService;
    class BuildDartsPointTurnValues : public IBuildDartsPointTurnValues
    {
    public:
        typedef IPlayerPointService<IDartsControllerPlayer<QUuid,QString,QByteArray>,
                                    IDartsControllerPoint<QUuid,QString,
        QByteArray>> PlayerPointService;
        DartsPointTurnValues* createTurnValues(const DartsIndexService* indexService,
                                      const PlayerPointService* playerScoreService,
                                      const IDartsInputSuggestion<QString>* logisticService) const override
        {
            auto model = new DartsPointTurnValues;
            auto playerScore = playerScoreService->playerScore(indexService->setIndex());
            model->setCanUndo(indexService->canUndo());
            model->setCanRedo(indexService->canRedo());
            model->setRoundIndex(indexService->roundIndex());
            model->setSetIndex(indexService->setIndex());
            model->setAttemptIndex(indexService->attemptIndex());
            model->setTargetRow(buildTargetRow(playerScore,model->getAttemptIndex(),logisticService));
            model->setPlayerName(playerScoreService->playerName(model->getSetIndex()));
            return model;
        }
    private:
        QString buildTargetRow(const int& remainingScore,
                               const int& attemptIndex,
                               const IDartsInputSuggestion<QString>* logisticService) const
        {
            if(logisticService == nullptr)
                return "Logistic service not injected";
            auto targetRow = logisticService->suggestTargetRow(remainingScore,attemptIndex);
            return targetRow;
        }
    };
}

#endif // BUILDDARTSPOINTTURNVALUES_H
