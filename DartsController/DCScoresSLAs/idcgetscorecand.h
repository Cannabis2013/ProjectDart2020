#ifndef IDCGETSCORECAND_H
#define IDCGETSCORECAND_H
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCIndexServices/dcindex.h"
class IDCGetScoreCand
{
public:
    virtual int calc(const DCIndex &index, const int &scoreCandidate, IDCScoreModels *scoresService) const = 0;
};
#endif // IDCWINNERSERVICE_H
