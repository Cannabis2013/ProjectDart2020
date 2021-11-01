#ifndef IDCCALCSCORE_H
#define IDCCALCSCORE_H

#include "DartsController/DCInputServices/dcinput.h"

#include "idcscoremodels.h"

#include <DartsController/DCIndexServices/dcindex.h>
class IDCCalcScore
{
public:
    virtual int calculate(const DCInput &input) const = 0;
    virtual int calculate(const DCIndex &index, const int &scoreCandidate, IDCScoreModels *scoresService) const = 0;
};

#endif // IDCCALCSCORE_H
