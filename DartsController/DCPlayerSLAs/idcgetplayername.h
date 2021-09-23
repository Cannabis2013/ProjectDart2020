#ifndef IDCGETPLAYERNAME_H
#define IDCGETPLAYERNAME_H
#include "DartsController/DCScoresSLAs/idcscoresservice.h"
class IDCGetPlayerName
{
public:
    virtual QString playerName(const QUuid &id,IDCScoresService *scoresService) const = 0;
};
#endif // DCGETPLAYERNAME_H
