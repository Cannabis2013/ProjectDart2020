#ifndef DARTSSCOREMODELMANIPULATOR_H
#define DARTSSCOREMODELMANIPULATOR_H

#include "idartsscoremodelmanipulator.h"
#include "idartsinputdb.h"
#include "ibinaryservice.h"
#include "ipredicate.h"
#include "iternaryservice.h"
#include "icreatedartsindexes.h"
#include "idartsinputdb.h"
#include "dartsscoreindexes.h"

namespace DartsModelsContext {
    class DartsScoreModelManipulator : public IDartsScoreModelManipulator<IDartsInputDb>
    {
    public:
        void setDartsScoreHint(const PlayerInput *model, const int &hint, DbModelsService* dbService) override;
    };
}


#endif // DARTSSCOREMODELSSERVICE_H
