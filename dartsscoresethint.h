#ifndef DARTSSCORESETHINT_H
#define DARTSSCORESETHINT_H

#include "idartsscoresethint.h"
#include "idbservice.h"
#include "ibinaryservice.h"
#include "ipredicate.h"
#include "iternaryservice.h"
#include "idartscreateindexes.h"
#include "idbservice.h"
#include "dartsscoreindexes.h"

namespace ModelsContext {
    class DartsScoreSetHint : public IDartsScoreSetHint<IDbService>
    {
    public:
        void setDartsScoreHint(const IModel<QUuid> *model, const int &hint,
                               IDbService* dbService) override;
    };
}


#endif // DARTSSCOREMODELSSERVICE_H
