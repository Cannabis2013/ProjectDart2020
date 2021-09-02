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
            auto canUndo = indexService->canUndo();
            auto canRedo = indexService->canRedo();
            auto roundIndex = indexService->roundIndex();
            auto setIndex = indexService->setIndex();
            auto tuples = scoresService->tuples();
            auto playerName = tuples.at(setIndex).name;
            auto score = tuples.at(setIndex).totalScore;
            auto targetRow = createRowSuggestionByScore(logisticService,score);
            auto model = new DCContext::DCTurnValues;
            model->setCanUndo(canUndo);
            model->setCanRedo(canRedo);
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
    };
}

#endif // ASSEMBLEDARTSSCORETURNVALUES_H
