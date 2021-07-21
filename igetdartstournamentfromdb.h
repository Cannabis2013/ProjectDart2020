#ifndef IGETDARTSTOURNAMENTFROMDB_H
#define IGETDARTSTOURNAMENTFROMDB_H

#include "igettournamentfromdb.h"
#include "idbservice.h"

class IGetDartsTournamentFromDb : public IGetTournamentFromDb<IModel<QUuid>,QUuid,IDbService>
{};

#endif // IGETDARTSTOURNAMENTDATA_H
