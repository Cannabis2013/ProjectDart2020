#ifndef ICOUNTINPUTMODELS_H
#define ICOUNTINPUTMODELS_H

#include <quuid.h>
#include "idartsinputdb.h"

class ICountInputModels
{
public:
    virtual int count(const QUuid& tournamentId,const IDartsInputDb* service) const = 0;
};

#endif // IINPUTMODELSCOUNTSERVICE_H
