#ifndef DMCSETINPUTHINT_H
#define DMCSETINPUTHINT_H
#include "DartsModelsContext/DMCInputSLAs/idartsinputsethint.h"

class DMCSetInputHint : public IDartsInputSetHint
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
