#include "dartspointsethint.h"

using namespace DartsModelsContext;

void DartsModelsContext::DartsPointSetHint::setDartsPointHint(const IPlayerInput *inputModel,
                                                                    const int &hint,
                                                                    IDartsInputDb *dbService)
{
    auto nonConstModel = const_cast<IPlayerInput*>(inputModel);
    nonConstModel->setHint(hint);
    dbService->saveState();
}
