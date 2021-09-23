#ifndef DARTSPOINTSETHINT_H
#define DARTSPOINTSETHINT_H
#include "DartsController/DCInputSLAs/idartsinputsethint.h"
class DartsPointSetHint : public IDartsInputSetHint
{
public:
    void setHint(const IModel<QUuid> *inputModel, const int &hint,
                           IModelsDbContext *dbService) override
    {
        auto inferedModel = dynamic_cast<const IPlayerInput*>(inputModel);
        auto nonConstModel = const_cast<IPlayerInput*>(inferedModel);
        nonConstModel->setHint(hint);
        dbService->saveState();
    }
};

#endif // DARTSPOINTMODELSSERVICE_H
