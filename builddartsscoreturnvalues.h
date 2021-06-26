#ifndef BUILDDARTSSCORETURNVALUES_H
#define BUILDDARTSSCORETURNVALUES_H

#include "ibuilddartsscorecontrollervalues.h"

namespace DartsScoreControllerContext{
    class buildDartsScoreTurnValues : public IBuildDartsScoreControllerValues
    {
    public:
        typedef IDartsControllerScore<QUuid,QString,QByteArray> ControllerScore;
        typedef IDartsScoreIndexService<IDartsScoreControllerIndexes<QByteArray>> IndexService;
        const DartsScoreTurnValues* createTurnValues(const IndexService* indexService,
                                            const IPlayerScoreService<IDartsPlayer<QUuid,QString>,ControllerScore>* playerScoreService,
                                            const IDartsInputSuggestion<QString>* logisticService) const override
        {
            auto canUndo = indexService->canUndo();
            auto canRedo = indexService->canRedo();
            auto roundIndex = indexService->roundIndex();
            auto setIndex = indexService->setIndex();
            auto playerName = playerScoreService->playerNameByIndex(setIndex);
            auto score = playerScoreService->playerScoreByIndex(setIndex);
            auto targetRow = createRowSuggestionByScore(logisticService,score);
            auto model = new DartsScoreTurnValues();
            model->setCanUndo(canUndo);
            model->setCanRedo(canRedo);
            model->setTargetRow(targetRow);
            model->setRoundIndex(roundIndex);
            model->setSetIndex(setIndex);
            model->setScore(score);
            model->setPlayerName(playerName);
            return model;
        }
    private:
        QString createRowSuggestionByScore(const IDartsInputSuggestion<QString>* logisticService,
                               const int& score) const
        {
            if(logisticService == nullptr)
                return "Logistic controller not injected";
            auto targetRow = logisticService->suggestTargetRow(score,1);
            return targetRow;
        }
    };
}

#endif // ASSEMBLEDARTSSCORETURNVALUES_H
