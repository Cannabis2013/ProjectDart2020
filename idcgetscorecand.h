#ifndef IDCGETSCORECAND_H
#define IDCGETSCORECAND_H

#include "idcscoresservice.h"

class IDCGetScoreCand
{
public:
    virtual int scoreCandidate(const int &modelIndex, const int &scoreCandidate, IDCScoresService *scoresService) const = 0;
};
#endif // IDCWINNERSERVICE_H
