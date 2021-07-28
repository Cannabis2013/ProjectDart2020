#ifndef DARTSSCORESETHINT_H
#define DARTSSCORESETHINT_H

#include "idartsscoresethint.h"
#include "imodelsdbcontext.h"
#include "ibinaryservice.h"
#include "ipredicate.h"
#include "iternaryservice.h"
#include "idartscreateindexes.h"
#include "imodelsdbcontext.h"
#include "dartsscoreindexes.h"

namespace ModelsContext {
    class DartsScoreSetHint : public IDartsScoreSetHint<IModelsDbContext>
    {
    public:
        void setDartsScoreHint(const IModel<QUuid> *model, const int &hint,
                               IModelsDbContext* dbService) override;
    };
}


#endif // DARTSSCOREMODELSSERVICE_H
