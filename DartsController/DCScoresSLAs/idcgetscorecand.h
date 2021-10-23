#ifndef IDCGETSCORECAND_H
#define IDCGETSCORECAND_H

#include "DartsController/DCScoresSLAs/idcscoresservice.h"

class IDCGetScoreCand
{
public:
    virtual int calc(const int &modelIndex, const int &scoreCandidate, IDCScoresService *scoresService) const = 0;
};
#endif // IDCWINNERSERVICE_H
