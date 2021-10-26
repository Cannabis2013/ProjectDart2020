#ifndef IDCUPDATESCOREMODELS_H
#define IDCUPDATESCOREMODELS_H

#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "DartsController/DCScoresSLAs/idcscoremodels.h"

class IDCUpdateScoreModels
{
public:
    virtual void update(const QVector<DCScoreModel> &tuples, IDCScoreModels *scoresService) const = 0;
};
#endif // IDCREPLACETUPLES_H
