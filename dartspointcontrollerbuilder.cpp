#include "dartspointcontrollerbuilder.h"

using namespace DartsBuilderContext;

DartsPointControllerBuilder* DartsPointControllerBuilder::createInstance()
{
    return new DartsPointControllerBuilder();
}

AbstractGameController *DartsPointControllerBuilder::buildDartsController(const QByteArray &json)
{
    auto entity = _buildEntityByJson->service(json);
    AbstractDartsPointController* controller = DefaultDartsPointController::createInstance(entity);
    emit sendController(controller,entity->displayHint());
    return controller;
}

DartsPointControllerBuilder *DartsPointControllerBuilder::setBuildEntityByJson(ControllerEntityBuilder *newBuildEntityByJson)
{
    _buildEntityByJson = newBuildEntityByJson;
    return this;
}
