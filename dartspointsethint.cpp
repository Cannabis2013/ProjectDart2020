#include "dartspointsethint.h"

using namespace ModelsContext;

void ModelsContext::DartsPointSetHint::setDartsPointHint(const IModel<QUuid> *inputModel,
                                                                    const int &hint,
                                                                    IModelsDbContext *dbService)
{
    auto inferedModel = dynamic_cast<const IPlayerInput*>(inputModel);
    auto nonConstModel = const_cast<IPlayerInput*>(inferedModel);
    nonConstModel->setHint(hint);
    dbService->saveState();
}
