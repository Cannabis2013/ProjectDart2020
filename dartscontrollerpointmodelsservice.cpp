#include "dartscontrollerpointmodelsservice.h"

using namespace DartsPointControllerContext;

void DartsPointControllerContext::DartsControllerPointModelsService::addAccumulatedScoreToModel(const DartsModelInterface *model, const int &score) const
{
    auto nonConstModel = const_cast<PointModel*>(model);
    nonConstModel->setTotalScore(score);
}

void DartsControllerPointModelsService::addPlayerIdToModel(const DartsModelInterface *model, const IdFormat &id) const
{
    auto nonConstModel = const_cast<PointModel*>(model);
    nonConstModel->setPlayerId(id);
}
