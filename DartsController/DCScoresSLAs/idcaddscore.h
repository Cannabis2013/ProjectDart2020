#ifndef IDCADDSCORE_H
#define IDCADDSCORE_H

#include "DartsController/DCInputSLAs/idcinputmodel.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include <quuid.h>
class IDCAddScore
{
public:
    virtual DCContext::DCScoreModel addPlayerScore(const DCContext::IDCInputModel *model, IDCScoresService *scoresService) const = 0;
};

#endif // IDARTSADDSCORE_H
