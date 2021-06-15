#include "dartscontrollerpointmodelsservice.h"

using namespace DartsPointControllerContext;

void DartsPointControllerContext::DartsControllerPointModelsService::addPlayerNameToModel(const DartsModelInterface *model, const QString &name) const
{
    auto nonConstModel = const_cast<PointModel*>(model);
    nonConstModel->setPlayerName(name);
}

void DartsPointControllerContext::DartsControllerPointModelsService::addAccumulatedScoreToModel(const DartsModelInterface *model, const int &score) const
{
    auto nonConstModel = const_cast<PointModel*>(model);
    nonConstModel->setTotalScore(score);
}

void DartsControllerPointModelsService::addTournamentIdToModel(const DartsModelInterface *model, const IdFormat &id) const
{
    auto nonConstModel = const_cast<PointModel*>(model);
    nonConstModel->setTournamentId(id);
}

void DartsControllerPointModelsService::addPlayerIdToModel(const DartsModelInterface *model, const IdFormat &id) const
{
    auto nonConstModel = const_cast<PointModel*>(model);
    nonConstModel->setPlayerId(id);
}
