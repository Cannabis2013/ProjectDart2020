#ifndef IDCRESETSCORESCOREMODELS_H
#define IDCRESETSCORESCOREMODELS_H

#include "idcinitialscore.h"
#include "idcscoresservice.h"

class IDCResetScoreScoreModels
{
public:
    virtual void reset(IDCScoresService *scoresService, const IDCInitialScore *metaService) const = 0;
};
#endif // IDCRESETSCORETUPLES_H
