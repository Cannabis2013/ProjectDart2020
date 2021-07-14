#ifndef DARTSSCORESETHINT_H
#define DARTSSCORESETHINT_H

#include "idartsscoresethint.h"
#include "idartsinputdb.h"
#include "ibinaryservice.h"
#include "ipredicate.h"
#include "iternaryservice.h"
#include "idartscreateindexes.h"
#include "idartsinputdb.h"
#include "dartsscoreindexes.h"

namespace DartsModelsContext {
    class DartsScoreSetHint : public IDartsScoreSetHint<IDartsInputDb>
    {
    public:
        void setDartsScoreHint(const PlayerInput *model, const int &hint, DbModelsService* dbService) override;
    };
}


#endif // DARTSSCOREMODELSSERVICE_H
