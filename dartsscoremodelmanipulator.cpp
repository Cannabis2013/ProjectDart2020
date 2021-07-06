#include "dartsscoremodelmanipulator.h"

using namespace DartsModelsContext;


void DartsScoreModelManipulator::setDartsScoreHint(const PlayerInput *model, const int &hint, DbModelsService *dbService)
{
    auto nonConstModel = const_cast<PlayerInput*>(model);
    nonConstModel->setHint(hint);
    dbService->saveState();
}
