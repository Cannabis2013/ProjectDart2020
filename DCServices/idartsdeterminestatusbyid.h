#ifndef IDARTSDETERMINESTATUSBYID_H
#define IDARTSDETERMINESTATUSBYID_H

#include <quuid.h>
#include "DCServices/idartsstatuscodes.h"
class IDartsDetermineStatusById
{
public:
    virtual int status(const QUuid &id, const IDartsStatusCodes *statuscodes) const = 0;
};
#endif // IDARTSDETERMINESTATUSFROMID_H
