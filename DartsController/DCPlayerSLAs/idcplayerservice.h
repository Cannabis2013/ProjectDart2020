#ifndef IDCPLAYERSERVICE_H
#define IDCPLAYERSERVICE_H

#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"

class IDCPlayerService
{
public:
    virtual QString currentPlayerName(const IDCIndexController *indexContext, IDCScoresService *scoresContext) const = 0;
    virtual QUuid currentPlayerId(const IDCIndexController *indexContext, IDCScoresService *scoresContext) const = 0;
};
#endif // IDCPLAYERSERVICE_H
