#ifndef IDARTSSCOREDB_H
#define IDARTSSCOREDB_H

#include <qvector.h>
#include "iplayerinput.h"
#include "imodelsdbcontext.h"
#include "ipersistence.h"

class IDartsInputDb :
        public IModelsDbContext<IPlayerInput>,
        public IPersistence
{
};


#endif // IDARTSSCOREDB_H
