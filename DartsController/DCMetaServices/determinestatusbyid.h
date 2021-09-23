#ifndef DETERMINESTATUSBYID_H
#define DETERMINESTATUSBYID_H

#include "DartsController/DCMetaSLAs/idartsdeterminestatusbyid.h"

class DetermineStatusById : public IDartsDetermineStatusById
{
public:
    virtual int status(const QUuid &id, const IDartsStatusCodes *statuscodes) const override
    {
        if(id == QUuid())
            return statuscodes->initialized();
        else
            return statuscodes->winnerFound();
    }
};
#endif // DETERMINECONTROLLERSTATEBYWINNERID_H
