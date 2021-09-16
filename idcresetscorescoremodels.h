#ifndef IDCRESETSCORESCOREMODELS_H
#define IDCRESETSCORESCOREMODELS_H

#include "idcmetadata.h"
#include "idcscoresservice.h"

class IDCResetScoreScoreModels
{
public:
    virtual void reset(IDCScoresService *scoresService, const IDCMetaData *metaService) const = 0;
};
#endif // IDCRESETSCORETUPLES_H
