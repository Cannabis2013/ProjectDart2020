#ifndef DARTSPOINTSETHINT_H
#define DARTSPOINTSETHINT_H

#include "idartspointsethint.h"
#include <qvector.h>
#include "idartsinputdb.h"
#include "idartsinputsfilter.h"
#include "ipredicate.h"
#include "ibinaryservice.h"
#include "iternaryservice.h"
#include "idartscreateindexes.h"

namespace DartsModelsContext {
    class DartsPointSetHint : public IDartsPointSetHint
    {
    public:
        void setDartsPointHint(const IPlayerInput *inputModel, const int &hint,
                               IDartsInputDb *dbService) override;
    };
}

#endif // DARTSPOINTMODELSSERVICE_H
