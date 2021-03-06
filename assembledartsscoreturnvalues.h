#ifndef ASSEMBLEDARTSSCORETURNVALUES_H
#define ASSEMBLEDARTSSCORETURNVALUES_H

#include "iternaryservice.h"
#include "dartsscoreturnvalues.h"
#include "idartsmultiattemptindexservice.h"
#include "iplayerscoreservice.h"
#include "dartsscore.h"
#include "idartslogisticsservice.h"
#include "idartsmultiattemptindexes.h"

namespace DartsScoreMultiAttemptContext{
    class AssembleDartsScoreTurnValues : public
            ITernaryService<const IDartsMultiAttemptIndexService<IDartsMultiAttemptIndexes>*,
                           const IPlayerScoreService<DartsScore>*,
                           const IDartsLogisticsService<QString>*,
                           const DartsScoreTurnValues*>
    {
    public:
        typedef IDartsMultiAttemptIndexService<IDartsMultiAttemptIndexes> IndexService;
        const DartsScoreTurnValues* service(const IndexService* indexService,
                                            const IPlayerScoreService<DartsScore>* playerScoreService,
                                            const IDartsLogisticsService<QString>* logisticService) override
        {
            auto canUndo = indexService->canUndo();
            auto canRedo = indexService->canRedo();
            auto roundIndex = indexService->roundIndex();
            auto setIndex = indexService->setIndex();
            auto currentUserName = playerScoreService->playerNameByIndex(setIndex);
            auto score = playerScoreService->playerScore(setIndex);
            auto targetRow = buildTargetRow(logisticService,score);

            auto model = new DartsScoreTurnValues();
            model->setCanUndo(canUndo);
            model->setCanRedo(canRedo);
            model->setTargetRow(targetRow);
            model->setRoundIndex(roundIndex);
            model->setSetIndex(setIndex);
            model->setCurrentUserName(currentUserName);
            model->setScore(score);
            return model;
        }
    private:
        QString buildTargetRow(const IDartsLogisticsService<QString>* logisticService,
                               const int& score)
        {
            if(logisticService == nullptr)
                return "Logistic controller not injected";
            auto targetRow = logisticService->suggestTargetRow(score,1);
            return targetRow;
        }
    };
}

#endif // ASSEMBLEDARTSSCORETURNVALUES_H
