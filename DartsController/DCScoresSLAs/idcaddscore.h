#ifndef IDCADDSCORE_H
#define IDCADDSCORE_H

#include <quuid.h>
#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCInputServices/dcinput.h"
class IDCAddScore
{
public:
    virtual DCContext::DCScoreModel addPlayerScore(const DCInput &model, IDCScoresService *scoresService) const = 0;
};

#endif // IDARTSADDSCORE_H
