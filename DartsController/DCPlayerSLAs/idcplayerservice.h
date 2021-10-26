#ifndef IDCPLAYERSERVICE_H
#define IDCPLAYERSERVICE_H

#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"

class IDCPlayerService
{
public:
    virtual QString currentPlayerName(IDCIndexController *indexContoller, IDCScoreModels *scoresContext) const = 0;
    virtual QUuid currentPlayerId(IDCIndexController *indexContoller, IDCScoreModels *scoresContext) const = 0;
};
#endif // IDCPLAYERSERVICE_H
