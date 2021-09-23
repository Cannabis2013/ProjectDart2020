#ifndef IDCPLAYERSERVICE_H
#define IDCPLAYERSERVICE_H

#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCIndexSLAs/idcindexservice.h"

class IDCPlayerService
{
public:
    virtual QString currentPlayerName() const = 0;
    virtual QUuid currentPlayerId() const = 0;
};
#endif // IDCPLAYERSERVICE_H
