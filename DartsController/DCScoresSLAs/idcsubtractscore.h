#ifndef IDCSUBTRACTSCORE_H
#define IDCSUBTRACTSCORE_H

#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "DartsController/DCInputSLAs/idcinputmodel.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"

class IDCSubtractScore
{
public:
    virtual DCContext::DCScoreModel subtractScore(const DCContext::IDCInputModel *model, IDCScoresService *scoresService) const = 0;
};
#endif // IDCSUBTRACTSCORE_H
