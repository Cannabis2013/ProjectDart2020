#include "dartscontrollerpointmodelsservice.h"

using namespace DCContext;

void DCContext::DartsControllerPointModelsService::addAccumulatedScoreToModel(const DartsModelInterface *model, const int &score) const
{
    auto nonConstModel = const_cast<IDCInputModel*>(model);
    nonConstModel->setTotalScore(score);
}

void DartsControllerPointModelsService::addPlayerIdToModel(const DartsModelInterface *model, const IdFormat &id) const
{
    auto nonConstModel = const_cast<IDCInputModel*>(model);
    nonConstModel->setPlayerId(id);
}
