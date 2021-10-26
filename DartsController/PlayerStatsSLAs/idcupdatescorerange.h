#ifndef IDCUPDATESCORERANGE_H
#define IDCUPDATESCORERANGE_H
#include "DartsController/PlayerStatsServices/dcplayerstatsmanager.h"
class IDCUpdateScoreRange
{
public:
    virtual void update(DCInput &input, IDCPlayerStats *playerStatsContext) const = 0;
};
#endif // IDCDETSCORERANGE_H
