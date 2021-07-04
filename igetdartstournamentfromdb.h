#ifndef IGETDARTSTOURNAMENTFROMDB_H
#define IGETDARTSTOURNAMENTFROMDB_H

#include "igettournamentfromdb.h"
#include "idartstournamentdb.h"

class IGetDartsTournamentFromDb : public IGetTournamentFromDb<ITournament,QUuid,IDartsTournamentDb>
{};

#endif // IGETDARTSTOURNAMENTDATA_H
