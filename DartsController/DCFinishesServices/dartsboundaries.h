#ifndef DARTSBOUNDARIES_H
#define DARTSBOUNDARIES_H

#include "DartsController/DCFinishesSLAs/idartsboundaries.h"

class DartsBoundaries : public IDartsBoundaries
{
public:
    virtual int trippleMaxValue() const override
    {
        return _trippleMaxValue;
    }
    virtual int doubleMaxValue() const override
    {
        return _doubleMaxValue;
    }
    virtual int singleMaxValue() const override
    {
        return _singleMaxValue;
    }
private:
    const int _singleMaxValue = 20;
    const int _doubleMaxValue = 40;
    const int _trippleMaxValue = 60;
};
#endif // DARTSBOUNDARIES_H
