#ifndef IDCGETPLAYERSCORE_H
#define IDCGETPLAYERSCORE_H

#include "idcscoresservice.h"

class IDCGetPlayerScore
{
public:
    virtual int playerScore(const int &index, IDCScoresService *scoresService) const = 0;
    virtual int playerScore(const QUuid &id, IDCScoresService *scoresService) const = 0;
};

#endif // IDCGETPLAYERSCORE_H
