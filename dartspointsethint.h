#ifndef DARTSPOINTSETHINT_H
#define DARTSPOINTSETHINT_H

#include "idartspointsethint.h"

namespace DartsModelsContext {
    class DartsPointSetHint : public IDartsPointSetHint
    {
    public:
        void setDartsPointHint(const IPlayerInput *inputModel, const int &hint,
                               IDartsInputDb *dbService) override;
    };
}

#endif // DARTSPOINTMODELSSERVICE_H
