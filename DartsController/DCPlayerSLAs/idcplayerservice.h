#ifndef IDCPLAYERSERVICE_H
#define IDCPLAYERSERVICE_H

#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCIndexSLAs/idcindexservice.h"

class IDCPlayerService
{
public:
    virtual QString currentPlayerName(const IDCIndexService *indexContext, IDCScoresService *scoresContext) const = 0;
    virtual QUuid currentPlayerId(const IDCIndexService *indexContext, IDCScoresService *scoresContext) const = 0;
};
#endif // IDCPLAYERSERVICE_H
