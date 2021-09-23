#ifndef IDCADDSCORE_H
#define IDCADDSCORE_H

#include "DCInputSLAs/idcinputmodel.h"
#include "DCScoresSLAs/idcscoresservice.h"
#include <quuid.h>
class IDCAddScore
{
public:
    virtual DCContext::DCScoreModel addPlayerScore(const DCContext::IDCInputModel *model, IDCScoresService *scoresService) const = 0;
};

#endif // IDARTSADDSCORE_H
