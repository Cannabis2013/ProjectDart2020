#ifndef DARTSDEFAULTATTEMPTS_H
#define DARTSDEFAULTATTEMPTS_H

#include "idartsattemptsservice.h"

class DartsDefaultAttempts : public IDartsAttemptsService
{
public:
    virtual int attempts() const override
    {
        return 3;
    }
};
#endif // DARTSDEFAULTATTEMPTS_H
