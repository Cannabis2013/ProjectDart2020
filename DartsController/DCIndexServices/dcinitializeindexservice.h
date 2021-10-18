#ifndef DCINITIALIZEINDEXSERVICE_H
#define DCINITIALIZEINDEXSERVICE_H

#include "DartsController/DCIndexSLAs/idcinitializeindexes.h"

class DCInitializeIndexes : public IDCInitializeIndexes
{
public:
    virtual void initialize(const DCIndexes &indexes, IDCIndexService *service) const override
    {
        service->setRoundIndex(indexes.roundIndex);
        service->setSetIndex(indexes.setIndex);
        service->setAttemptIndex(indexes.attemptIndex);
        service->setTurnIndex(indexes.turnIndex);
        service->setTotalIndex(indexes.totalTurns);
    }
};

#endif // DCINITIALIZEINDEXSERVICE_H
