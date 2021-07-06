#ifndef DARTSPOINTMODELSSERVICE_H
#define DARTSPOINTMODELSSERVICE_H

#include "idartspointmodelmanipulator.h"
#include <qvector.h>
#include "idartsinputdb.h"
#include "idartsinputsfilter.h"
#include "ipredicate.h"
#include "ibinaryservice.h"
#include "iternaryservice.h"
#include "icreatedartsindexes.h"

namespace DartsModelsContext {
    class DartsPointModelsService : public IDartsPointModelManipulator
    {
    public:
        void setDartsPointHint(const IPlayerInput *inputModel, const int &hint,
                               IDartsInputDb *dbService) override;
    };
}

#endif // DARTSPOINTMODELSSERVICE_H
