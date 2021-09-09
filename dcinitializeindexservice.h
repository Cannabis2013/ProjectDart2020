#ifndef DCINITIALIZEINDEXSERVICE_H
#define DCINITIALIZEINDEXSERVICE_H

#include "idcinitializeindexes.h"

class DCInitializeIndexes : public IDCInitializeIndexes
{
public:
    virtual void initialize(const DCContext::IDCIndexes *indexes, IDCIndexService *service) const override
    {
        service->setRoundIndex(indexes->roundIndex());
        service->setSetIndex(indexes->setIndex());
        service->setAttemptIndex(indexes->attemptIndex());
        service->setTurnIndex(indexes->turnIndex());
        service->setTotalIndex(indexes->totalTurns());
    }
};

#endif // DCINITIALIZEINDEXSERVICE_H
