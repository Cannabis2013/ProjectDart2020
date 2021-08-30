#include "dartscontrollerpointmodelsservice.h"

using namespace DPCContext;

void DPCContext::DartsControllerPointModelsService::addAccumulatedScoreToModel(const DartsModelInterface *model, const int &score) const
{
    auto nonConstModel = const_cast<IDPCModel*>(model);
    nonConstModel->setTotalScore(score);
}

void DartsControllerPointModelsService::addPlayerIdToModel(const DartsModelInterface *model, const IdFormat &id) const
{
    auto nonConstModel = const_cast<IDPCModel*>(model);
    nonConstModel->setPlayerId(id);
}
