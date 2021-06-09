#include "dartsscorebuilderservice.h"

using namespace DartsBuilderContext;

DartsScoreBuilderService *DartsBuilderContext::DartsScoreBuilderService::createInstance()
{
    return new DartsScoreBuilderService;
}


AbstractGameController *DartsScoreBuilderService::buildDartsController(const QByteArray &json)
{
    auto entity = _buildEntityByJson->service(json);
    AbstractDartsScoreController* controller = _buildMultiAttemptScoreController->buildSingleAttemptPointController(entity);
    emit sendController(controller,entity->displayHint());
    return controller;
}


DartsScoreBuilderService *DartsScoreBuilderService::setBuildMultiAttemptScoreController(BuildMultiAttemptScoreController *service)
{
    _buildMultiAttemptScoreController = service;
    return this;
}

DartsScoreBuilderService *DartsScoreBuilderService::setBuildEntityByJson(ControllerEntityBuilder *newBuildEntityByJson)
{
    _buildEntityByJson = newBuildEntityByJson;
    return this;
}
