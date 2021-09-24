#ifndef IDARTSINPUTVALIDATOR_H
#define IDARTSINPUTVALIDATOR_H

#include "IDCInputKeyCodes.h"

class IDartsInputValidator
{
public:
    virtual int validateInput(const int &currentScore,
                              const IDCInputKeyCodes *keyCodes,
                              const int &keyCode,
                              const int &point) const = 0;
};


#endif // IPOINTVALIDATOR_H
