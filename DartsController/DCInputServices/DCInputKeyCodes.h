#ifndef DCINPUTKEYCODES_H
#define DCINPUTKEYCODES_H

#include <DartsController/DCInputSLAs/IDCInputKeyCodes.h>


class DCInputKeyCodes : public IDCInputKeyCodes
{
public:
    virtual int singleModifier() const override
    {
        return SingleModifer;
    }
    virtual int doubleModifier() const override
    {
        return DoubleModifier;
    }
    virtual int trippleModifier() const override
    {
        return TrippleModifier;
    }
private:
    enum KeyMappings{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C
    };
};

#endif // DCINPUTKEYCODES_H
