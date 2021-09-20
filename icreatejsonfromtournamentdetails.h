#ifndef ICREATEJSONFROMTOURNAMENTDETAILS_H
#define ICREATEJSONFROMTOURNAMENTDETAILS_H

#include "ModelsContext/imodel.h"
#include <quuid.h>
#include <qbytearray.h>
class ICreateJsonFromTournamentDetails
{
public:
    virtual QByteArray createFromAssignedPlayerDetails(const IModel<QUuid> *model) const = 0;
    virtual QByteArray createFromWinnerDetails(const IModel<QUuid> *model) const = 0;
};

#endif // ICREATEJSONFROMTOURNAMENTDATA_H
