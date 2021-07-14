#include "dartsscoresethint.h"

using namespace DartsModelsContext;


void DartsScoreSetHint::setDartsScoreHint(const PlayerInput *model, const int &hint, DbModelsService *dbService)
{
    auto nonConstModel = const_cast<PlayerInput*>(model);
    nonConstModel->setHint(hint);
    dbService->saveState();
}
