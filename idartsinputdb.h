#ifndef IDARTSSCOREDB_H
#define IDARTSSCOREDB_H

#include <qvector.h>
#include "idartsscoreinput.h"
#include "imodelsdbcontext.h"
#include "ipersistence.h"

namespace DartsModelsContext {
    class IDartsInputDb :
            public IModelsDbContext<IPlayerInput>,
            public IPersistence
    {
    };
}


#endif // IDARTSSCOREDB_H
