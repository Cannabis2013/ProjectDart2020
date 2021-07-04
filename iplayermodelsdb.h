#ifndef IMODELDBCONTEXT_H
#define IMODELDBCONTEXT_H

#include <qvector.h>
#include <quuid.h>
#include "iplayermodel.h"
#include "ipersistence.h"
#include "imodelsdbcontext.h"

class IPlayerModelsDb :
        public IModelsDbContext<DartsModelsContext::IPlayerModel>,
        public IPersistence
{};

#endif // IMODELDBCONTEXT_H
