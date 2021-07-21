#include "dartsscoresethint.h"

using namespace ModelsContext;


void DartsScoreSetHint::setDartsScoreHint(const IModel<QUuid> *model, const int &hint,
                                          IDbService *dbService)
{
    auto inferedModel = dynamic_cast<const IPlayerInput*>(model);
    auto nonConstModel = const_cast<IPlayerInput*>(inferedModel);
    nonConstModel->setHint(hint);
    dbService->saveState();
}
