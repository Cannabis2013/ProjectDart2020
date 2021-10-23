#ifndef DCINDEXUNDO_H
#define DCINDEXUNDO_H

#include "DartsController/DCIndexSLAs/idcundoindex.h"
class DCIndexUndo : public IDCUndoIndex
{
public:
    virtual void undo(IDCIndexController *indexService, IDCScoresService *scoresService) const override
    {
        if(indexService->turnIndex() <= 0)
            return;
        decrementTurnIndex(indexService);
        decrementAttemptIndex(indexService);
        if(indexService->attemptIndex() < 0)
        {
            decrementSetIndex(indexService);
            indexService->setAttemptIndex(indexService->numberOfAttempts() - 1);
        }
        if(indexService->setIndex() < 0)
        {
            decrementRoundIndex(indexService);
            indexService->setSetIndex(lastPlayerIndex(scoresService));
        }
    }
private:
    int lastPlayerIndex(IDCScoresService *scoresService) const
    {
        return scoresService->scoreModels().count() -1;
    }
    void decrementTurnIndex(IDCIndexController *indexService) const
    {
        auto tIndex = indexService->turnIndex();
        indexService->setTurnIndex(--tIndex);
    }
    void decrementRoundIndex(IDCIndexController *indexService) const
    {
        auto rIndex = indexService->roundIndex();
        indexService->setRoundIndex(--rIndex);
    }
    void decrementSetIndex(IDCIndexController *indexService) const
    {
        auto sIndex = indexService->setIndex();
        indexService->setSetIndex(--sIndex);
    }
    void decrementAttemptIndex(IDCIndexController *indexService) const
    {
        auto aIndex = indexService->attemptIndex();
        indexService->setAttemptIndex(--aIndex);
    }
};

#endif // DCUNDOINDEX_H
