#ifndef IDCSUBTRACTSCORE_H
#define IDCSUBTRACTSCORE_H

#include <dcscoremodel.h>
#include "idcmodel.h"
#include <idcscoresservice.h>

class IDCSubtractScore
{
public:
    virtual DCContext::DCScoreModel subtractScore(const DCContext::IDCModel *model, IDCScoresService *scoresService) const = 0;
};
#endif // IDCSUBTRACTSCORE_H
