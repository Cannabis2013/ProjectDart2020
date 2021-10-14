#ifndef DCINPUTSTATSAVGKEYS_H
#define DCINPUTSTATSAVGKEYS_H

#include "DartsController/DCInputStatsSLAs/idcinputavgjsonkeys.h"

class DCInputStatsAvgKeys : public IDCInputAvgJsonKeys
{
public:
    virtual QString average() const override
    {
        return "average";
    }
};
#endif // DCINPUTSTATSAVGKEYS_H
