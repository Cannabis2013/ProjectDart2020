#include "dartscontrollerpointmodelsservice.h"

using namespace DartsPointSingleAttemptContext;

void DartsPointSingleAttemptContext::DartsControllerPointModelsService::addPlayerNameToModel(const DartsModelInterface *model, const QString &name) const
{
    auto nonConstModel = const_cast<PointModel*>(model);
    nonConstModel->setPlayerName(name);
}

void DartsPointSingleAttemptContext::DartsControllerPointModelsService::addAccumulatedScoreToModel(const DartsModelInterface *model, const int &score) const
{
    auto nonConstModel = const_cast<PointModel*>(model);
    nonConstModel->setAccumulatedScore(score);
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
