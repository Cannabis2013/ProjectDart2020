#include "dartspointcontrollerbuilder.h"

using namespace DartsBuilderContext;

DartsPointControllerBuilder* DartsPointControllerBuilder::createInstance()
{
    return new DartsPointControllerBuilder();
}

AbstractGameController *DartsPointControllerBuilder::buildDartsController(const QByteArray &json)
{
    auto entity = _createDCMetaInfo->service(json);
    AbstractDartsPointController* controller = DefaultDPController::createInstance(entity);
    emit sendController(controller,entity->displayHint());
    return controller;
}

DartsPointControllerBuilder *DartsPointControllerBuilder::setDCMetaInfoCreator(ICreateDCMetaInfo *newBuildEntityByJson)
{
    _createDCMetaInfo = newBuildEntityByJson;
    return this;
}
