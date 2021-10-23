#ifndef DCINDEXREDO_H
#define DCINDEXREDO_H
#include "DartsController/DCIndexSLAs/idcindexredo.h"
class DCIndexRedo : public IDCIndexRedo
{
public:
    virtual void redo(IDCIndexController *indexService, IDCScoresService *scoresService) const override
    {
        if(indexService->turnIndex() >= indexService->totalIndex())
            return;
        incrementTurnIndex(indexService);
        incrementAttemptIndex(indexService);
        if(indexService->attemptIndex() >= indexService->numberOfAttempts())
        {
            incrementSetIndex(indexService);
            indexService->setAttemptIndex(0);
        }
        if(indexService->setIndex() >= playersCount(scoresService)){
            incrementRoundIndex(indexService);
            indexService->setSetIndex(0);
        }
    }
private:
    int playersCount(IDCScoresService *scoresService) const
    {
        return scoresService->scoreModels().count();
    }
    void incrementTurnIndex(IDCIndexController *indexService) const
    {
        auto tIndex = indexService->turnIndex();
        indexService->setTurnIndex(++tIndex);
    }
    void incrementTotalTurnIndex(IDCIndexController *indexService) const
    {
        auto tIndex = indexService->totalIndex();
        indexService->setTotalIndex(++tIndex);
    }
    void incrementSetIndex(IDCIndexController *indexService) const
    {
        auto sIndex = indexService->setIndex();
        indexService->setSetIndex(++sIndex);
    }
    void incrementRoundIndex(IDCIndexController *indexService) const
    {
        auto rIndex = indexService->roundIndex();
        indexService->setRoundIndex(++rIndex);
    }
    void incrementAttemptIndex(IDCIndexController *indexService) const
    {
        auto aIndex = indexService->attemptIndex();
        indexService->setAttemptIndex(++aIndex);
    }
};
#endif // DCINDEXREDO_H
