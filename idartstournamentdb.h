#ifndef IDARTSTOURNAMENTDB_H
#define IDARTSTOURNAMENTDB_H

#include <qvector.h>
#include "imodelsdbcontext.h"
#include "itournament.h"
#include "ipersistence.h"

class IDartsTournamentDb :
        public IModelsDbContext<ITournament>,
        public IPersistence
{};

#endif // IDARTSTOURNAMENTDB_H
