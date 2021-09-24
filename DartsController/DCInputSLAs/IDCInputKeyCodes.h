#ifndef IDCINPUTKEYCODES_H
#define IDCINPUTKEYCODES_H

class IDCInputKeyCodes
{
public:
    virtual int singleModifier() const = 0;
    virtual int doubleModifier() const = 0;
    virtual int trippleModifier() const = 0;
};

#endif // IDCINPUTKEYCODES_H
