#ifndef IDCUPDATESCOREMODELS_H
#define IDCUPDATESCOREMODELS_H

#include "dcscoremodel.h"
#include "idcscoresservice.h"

class IDCUpdateScoreModels
{
public:
    virtual void update(const QVector<DCContext::DCScoreModel> &tuples, IDCScoresService *scoresService) const = 0;
};
#endif // IDCREPLACETUPLES_H
