#ifndef IDCSUBTRACTSCORE_H
#define IDCSUBTRACTSCORE_H

#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"

#include "DartsController/DCInputServices/dcinput.h"

class IDCSubtractScore
{
public:
    virtual DCContext::DCScoreModel subtractScore(const DCInput &model, IDCScoresService *scoresService) const = 0;
};
#endif // IDCSUBTRACTSCORE_H
