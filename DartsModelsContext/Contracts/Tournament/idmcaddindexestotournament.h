#ifndef IDMCADDINDEXESTOTOURNAMENT_H
#define IDMCADDINDEXESTOTOURNAMENT_H

#include "idartstournamentindexes.h"
#include <qbytearray.h>

class IDCMAddIndexesToTournament
{
public:
    virtual void add(const QByteArray &json, IDartsTournamentIndexes *tournament) const = 0;
};
#endif // IDMCADDINDEXESTOTOURNAMENT_H
