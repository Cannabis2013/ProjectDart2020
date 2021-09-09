#ifndef IDCUPDATETUPLES_H
#define IDCUPDATETUPLES_H

#include "dcscoremodel.h"
#include "idcscoresservice.h"

class IDCUpdateTuples
{
public:
    virtual void update(const QVector<DCContext::DCScoreModel> &tuples, IDCScoresService *scoresService) const = 0;
};
#endif // IDCREPLACETUPLES_H
