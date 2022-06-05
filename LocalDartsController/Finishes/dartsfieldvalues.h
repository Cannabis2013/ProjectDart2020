#ifndef DARTSFIELDVALUES_H
#define DARTSFIELDVALUES_H

#include <DartsController/Finishes/idartsfieldvalues.h>

class DartsFieldValues : public IDartsFieldValues
{
public:
    virtual int bullsEye() const override
    {
        return _bullsEye;
    }
    virtual int bull() const override
    {
        return _bull;
    }
private:
    const int _bull = 25;
    const int _bullsEye =  50;
};
#endif // DARTSFIELDVALUES_H
