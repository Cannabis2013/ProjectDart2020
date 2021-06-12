#include "dartspointbuilderservice.h"

using namespace DartsBuilderContext;

DartsPointBuilderService* DartsPointBuilderService::createInstance()
{
    return new DartsPointBuilderService();
}

AbstractGameController *DartsPointBuilderService::buildDartsController(const QByteArray &json)
{
    auto entity = _buildEntityByJson->service(json);
    AbstractDartsPointController* controller = _buildControllerService->buildController(entity);
    emit sendController(controller,entity->displayHint());
    return controller;
}

DartsPointBuilderService *DartsPointBuilderService::setBuildSingleAttemptPointController(BuildPointController *service)
{
    _buildControllerService = service;
    return this;
}

DartsPointBuilderService *DartsPointBuilderService::setBuildEntityByJson(ControllerEntityBuilder *newBuildEntityByJson)
{
    _buildEntityByJson = newBuildEntityByJson;
    return this;
}
