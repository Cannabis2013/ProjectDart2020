#ifndef DCINDEXREDO_H
#define DCINDEXREDO_H
#include "DCIndexSLAs/idcindexredo.h"
class DCIndexRedo : public IDCIndexRedo
{
public:
    virtual void redo(IDCIndexService *indexService, IDCScoresService *scoresService) const override
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
    void incrementTurnIndex(IDCIndexService *indexService) const
    {
        auto tIndex = indexService->turnIndex();
        indexService->setTurnIndex(++tIndex);
    }
    void incrementTotalTurnIndex(IDCIndexService *indexService) const
    {
        auto tIndex = indexService->totalIndex();
        indexService->setTotalIndex(++tIndex);
    }
    void incrementSetIndex(IDCIndexService *indexService) const
    {
        auto sIndex = indexService->setIndex();
        indexService->setSetIndex(++sIndex);
    }
    void incrementRoundIndex(IDCIndexService *indexService) const
    {
        auto rIndex = indexService->roundIndex();
        indexService->setRoundIndex(++rIndex);
    }
    void incrementAttemptIndex(IDCIndexService *indexService) const
    {
        auto aIndex = indexService->attemptIndex();
        indexService->setAttemptIndex(++aIndex);
    }
};
#endif // DCINDEXREDO_H
