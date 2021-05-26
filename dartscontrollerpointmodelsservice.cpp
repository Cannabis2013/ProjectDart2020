#include "dartscontrollerpointmodelsservice.h"

using namespace DartsPointSingleAttemptContext;

const DartsControllerPointModelsService::DartsModelInterface *DartsPointSingleAttemptContext::DartsControllerPointModelsService::addPlayerNameToModel(const DartsModelInterface *model, const QString &name) const
{
    auto nonConstModel = const_cast<PointModel*>(model);
    nonConstModel->setPlayerName(name);
    return model;
}

const DartsControllerPointModelsService::DartsModelInterface *DartsPointSingleAttemptContext::DartsControllerPointModelsService::addPlayerScoreToModel(const DartsModelInterface *model, const int &score) const
{
    auto nonConstModel = const_cast<PointModel*>(model);
    nonConstModel->setAccumulatedScore(score);
    return model;
}
