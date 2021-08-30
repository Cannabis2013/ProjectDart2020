#ifndef IDSCCALCCANDIDATE_H
#define IDSCCALCCANDIDATE_H

#include "idcscoresservice.h"

class IDSCCalcCandidate
{
public:
    virtual int scoreCandidate(const int &modelIndex, const int &scoreCandidate, IDCScoresService *scoresService) const = 0;
};
#endif // IDCWINNERSERVICE_H
