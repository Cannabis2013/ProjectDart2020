#ifndef IGETDARTSTOURNAMENTFROMDB_H
#define IGETDARTSTOURNAMENTFROMDB_H

#include "igettournamentfromdb.h"
#include "ModelsContext/imodelsdbcontext.h"

class IGetDartsTournamentFromDb : public IGetTournamentFromDb<IModel<QUuid>,QUuid,IModelsDbContext>
{};

#endif // IGETDARTSTOURNAMENTDATA_H
