#ifndef DSCVALUESBUILDER_H
#define DSCVALUESBUILDER_H

#include <icreatedcturnvalues.h>
#include "dcturnvalues.h"

namespace DSCContext{
    class DSCValuesBuilder : public ICreateDCTurnValues
    {
    public:
        const DCContext::DCTurnValues* createTurnValues(const IDCIndexService* indexService,
                                                        IDCScoresService* scoresService,
                                                        const IDartsInputSuggestion* logisticService) const override
        {
            auto roundIndex = indexService->roundIndex();
            auto setIndex = indexService->setIndex();
            auto tuples = scoresService->scoreModels();
            auto playerName = tuples.at(setIndex).name;
            auto score = tuples.at(setIndex).totalScore;
            auto targetRow = createRowSuggestionByScore(logisticService,score);
            auto model = new DCContext::DCTurnValues;
            model->setCanUndo(canUndo(indexService));
            model->setCanRedo(canRedo(indexService));
            model->setTargetRow(targetRow);
            model->setRoundIndex(roundIndex);
            model->setSetIndex(setIndex);
            model->setPlayerName(playerName);
            return model;
        }
    private:
        QString createRowSuggestionByScore(const IDartsInputSuggestion* logisticService,
                                           const int& score) const
        {
            if(logisticService == nullptr)
                return "Logistic controller not injected";
            auto targetRow = logisticService->suggestTargetRow(score,1);
            return targetRow;
        }
        bool canUndo(const IDCIndexService *indexService) const
        {
            return indexService->turnIndex() > 0;
        }
        bool canRedo(const IDCIndexService *indexService) const
        {
            return indexService->turnIndex() < indexService->totalIndex();
        }
    };
}

#endif // ASSEMBLEDARTSSCORETURNVALUES_H
