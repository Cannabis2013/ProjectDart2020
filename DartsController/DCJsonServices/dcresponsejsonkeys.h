#ifndef DCRESPONSEJSONKEYS_H
#define DCRESPONSEJSONKEYS_H

#include <DartsController/DCJsonSLAs/idcresponsejsonkeys.h>

class DCResponseJsonKeys : public IDCResponseJsonKeys
{
public:
    virtual QString inputKey() const override
    {
        return "input";
    }
    virtual QString indexesKey() const override
    {
        return "indexes";
    }
    virtual QString turnValuesKey() const override
    {
        return "turnValues";
    }
    virtual QString winnerValuesKey() const override
    {

    }
};
#endif // DCRESPONSEJSONKEYS_H
