#ifndef DARTSPOINTSETHINT_H
#define DARTSPOINTSETHINT_H

#include "idartspointsethint.h"

namespace ModelsContext {
    class DartsPointSetHint : public IDartsPointSetHint
    {
    public:
        void setDartsPointHint(const IModel<QUuid> *inputModel, const int &hint,
                               IModelsDbContext *dbService) override;
    };
}

#endif // DARTSPOINTMODELSSERVICE_H
