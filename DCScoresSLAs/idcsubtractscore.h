#ifndef IDCSUBTRACTSCORE_H
#define IDCSUBTRACTSCORE_H

#include "DCScoresServices/dcscoremodel.h"
#include "DCInputSLAs/idcinputmodel.h"
#include "DCScoresSLAs/idcscoresservice.h"

class IDCSubtractScore
{
public:
    virtual DCContext::DCScoreModel subtractScore(const DCContext::IDCInputModel *model, IDCScoresService *scoresService) const = 0;
};
#endif // IDCSUBTRACTSCORE_H
