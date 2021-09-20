#ifndef IDCTOURNAMENTID_H
#define IDCTOURNAMENTID_H

#include <quuid.h>

class IDCTournamentId
{
public:
    virtual QUuid id() const = 0;
};
#endif // IDCTOURNAMENTID_H
