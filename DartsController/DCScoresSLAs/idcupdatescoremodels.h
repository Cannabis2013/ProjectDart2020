#ifndef IDCUPDATESCOREMODELS_H
#define IDCUPDATESCOREMODELS_H

#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"

class IDCUpdateScoreModels
{
public:
    virtual void update(const QVector<DCScoreModel> &tuples, IDCScoresService *scoresService) const = 0;
};
#endif // IDCREPLACETUPLES_H
