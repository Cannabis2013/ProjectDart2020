#ifndef DCRESETINDEXES_H
#define DCRESETINDEXES_H
#include "DCIndexSLA/idcresetindexes.h"
class DCResetIndexes : public IDCResetIndexes
{
public:
    virtual void reset(IDCIndexService *indexService) const override
    {
        indexService->setTotalIndex(0);
        indexService->setTurnIndex(0);
        indexService->setRoundIndex(1);
        indexService->setSetIndex(0);
        indexService->setAttemptIndex(0);
    }
};
#endif // DCRESETINDEXES_H
